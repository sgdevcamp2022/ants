using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Pathfinding;
public class SlimeBrain : MonoBehaviour
{

    Sequence AttackNode;
    Sequence PatrolNode;

    IAstarAI astarAI;

    public Coroutine evaluateCoroutine;
    public EnemyAttack enemyAttack;


    AIPath aIPath;

    public bool IsWaiting;
    public bool isEnd;
    public bool isAttacked;

    private void Awake()
    {
        isAttacked = false;
        aIPath = GetComponent<AIPath>();
        astarAI = GetComponent<IAstarAI>();
        Debug.Log(astarAI);
    }

    public void ResetBrain()
    {
        StopAllCoroutines();
        astarAI.destination = transform.position;
        IsWaiting = false;
    }

    void Start()
    {
        ConstructBehaviourTree();
        evaluateCoroutine = StartCoroutine(StartEvaluate());
    }

    void Update()
    {
        if (isEnd)
        {
            isEnd = false;
            evaluateCoroutine = StartCoroutine(StartEvaluate());
        }
        
    }

    public void StartEvaluateCoroutine()
    {
        aIPath.enabled = true;
        evaluateCoroutine = StartCoroutine(StartEvaluate());
    }

    public void StopEvaluateCoroutine()
    {
        aIPath.enabled = false;
        StopCoroutine(evaluateCoroutine);
    }

    IEnumerator StartEvaluate()
    {
        // topNode의 기능을 현재 StartEvaluate에서 작업진행

    if(isAttacked == true)
        { 
            AttackNode.Evaluate(); 
        }
        else
        {
            PatrolNode.Evaluate();
        }

        yield return null;
    }


    private void ConstructBehaviourTree()
    {
        EndNode Eed = new EndNode(this);
        EndAttack endAttack = new EndAttack(this);


        PatrolNode patrol = new PatrolNode(astarAI, this.transform.position);
        AttackNode attack = new AttackNode(this);

        DoNothing doNothing2f_Patrol = new DoNothing(4f, "patrol", this);
        DoNothing doNothing2f_Attack = new DoNothing(0.5f, "attack", this);

        AttackNode = new Sequence(new List<Node> { doNothing2f_Attack, attack, endAttack, Eed });
        PatrolNode = new Sequence(new List<Node> { doNothing2f_Patrol, patrol, Eed });




    }


    public void StartWaitCoroutine(float delayTime, string upperNode)//Wait코루틴 시작 함수
    {
        //Debug.Log(top);

        StartCoroutine(DoNothing(delayTime, upperNode));
    }


    IEnumerator DoNothing(float delayTime, string upperNode)//Wait코루틴
    {
       // Debug.Log(top);
        while (delayTime > 0)
        {
            delayTime -= Time.deltaTime;
            yield return null;
        }
        //Debug.Log(top);
        switch (upperNode)
        {
            case "patrol":
                PatrolNode.Evaluate();
                break;
            case "attack":
                AttackNode.Evaluate();
                break;

        }

    }







}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Pathfinding;
public class Brain : MonoBehaviour
{

    Sequence AttackNode;
    Sequence PatrolNode;

    IAstarAI astarAI;

    public Coroutine evaluateCoroutine;
    public EnemyAttack enemyAttack;

    [SerializeField] bool Slime, EliteSlime;

    AIPath aIPath;

    [HideInInspector]
    public bool IsWaiting, isEnd, isAttacked;

    private void Awake()
    {
        isAttacked = false;
        enemyAttack = GetComponent<EnemyAttack>();
        aIPath = GetComponent<AIPath>();
        astarAI = GetComponent<IAstarAI>();
    }

    public void ResetBrain()
    {
        StopAllCoroutines();
        astarAI.destination = transform.position;
        IsWaiting = false;
    }

    void Start()
    {
        setConstructBehaviourTree();
        evaluateCoroutine = StartCoroutine(StartEvaluate());
    }

    void setConstructBehaviourTree()
    {
        if (Slime)
        {
            ConstructBehaviourTree_Slime();
        }
        else if(EliteSlime)
        {
            ConstructBehaviourTree_EliteSlime();
        }
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
        if (Slime)
        {
            if (isAttacked == true)
            {
                AttackNode.Evaluate();
            }
            else
            {
                PatrolNode.Evaluate();
            }
            yield return null;
        }
        else if (EliteSlime)
        {
            PatrolNode.Evaluate();
            yield return null;
        }

    }


    private void ConstructBehaviourTree_Slime()
    {
        EndNode Eed = new EndNode(this);
        EndAttack endAttack = new EndAttack(this);


        PatrolNode patrol = new PatrolNode(astarAI, this.transform.position);
        AttackNode attack = new AttackNode(this);

        DoNothing doNothing2f_Patrol = new DoNothing(4f, "patrol",true, this);
        DoNothing doNothing2f_Attack = new DoNothing(1f, "attack",false, this);

        AttackNode = new Sequence(new List<Node> { doNothing2f_Attack, attack, endAttack, Eed });
        PatrolNode = new Sequence(new List<Node> { doNothing2f_Patrol, patrol, Eed });
    }

    private void ConstructBehaviourTree_EliteSlime()
    {
        EndNode Eed = new EndNode(this);
        EndAttack endAttack = new EndAttack(this);


        PatrolNode patrol = new PatrolNode(astarAI, this.transform.position);
        AttackNode attack = new AttackNode(this);

        DoNothing doNothing2f_Patrol = new DoNothing(1f, "patrol", true, this);
        DoNothing doNothing2f_Attack = new DoNothing(1f, "attack", false, this);


        PatrolNode = new Sequence(new List<Node> { doNothing2f_Patrol, patrol, Eed });
    }






    public void StartWaitCoroutine(float delayTime, string upperNode, bool random)//Wait코루틴 시작 함수
    {
        StartCoroutine(DoNothing(delayTime, upperNode, random));
    }
    IEnumerator DoNothing(float delayTime, string upperNode, bool random)//Wait코루틴
    {
        if (random)
        {
            delayTime = delayTime + Random.Range(-0.5f, 1.0f);
        }
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

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Pathfinding;
public class Brain : MonoBehaviour
{

    Sequence AttackNode;
    Sequence PatrolNode;
    Sequence ChaseNode;

    Invertor invertor;

    IAstarAI astarAI;

    public GameObject player;

    public Coroutine evaluateCoroutine;
    public EnemyAttack enemyAttack;

    [SerializeField] bool Slime, EliteSlime, Zombie, Ghost, EliteGhost;

    AIPath aIPath;

    [HideInInspector]
    public bool IsWaiting, isEnd, isAttacked, inRecognize;
    public bool nearPlayer;


    private void Awake()
    {
        player = GameObject.FindWithTag("Player");
        isAttacked = false;
        enemyAttack = GetComponent<EnemyAttack>();
        aIPath = GetComponent<AIPath>();
        astarAI = GetComponent<IAstarAI>();
    }

    public void ResetBrain()
    {
        StopAllCoroutines();
        if(Zombie != true)
        {
            astarAI.destination = transform.position;
        }
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
        else if(Zombie)
        {
            ConstructBehaviourTree_Zombile();
        }
        else if (Ghost)
        {
            ConstructBehaviourTree_Ghost();
        }
        else if (EliteGhost)
        {
            ConstructBehaviourTree_EliteGhost();
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
            if (isAttacked == true)
            {
                AttackNode.Evaluate();
            }
            else
            {
                PatrolNode.Evaluate();
            }
        }
        else if (Zombie)
        {
            if (isAttacked == true || inRecognize == true)
            {
                ChaseNode.Evaluate();
            }
            else
            {
                PatrolNode.Evaluate();
            }
        }
        else if (Ghost)
        {
            if (isAttacked == true || nearPlayer)
            {
                AttackNode.Evaluate();
            }
            else
            {
                PatrolNode.Evaluate();
            }
        }
        else if (EliteGhost)
        {
            if (isAttacked == true || nearPlayer)
            {
                AttackNode.Evaluate();
            }
            else
            {
                PatrolNode.Evaluate();
            }
        }
    }


    private void ConstructBehaviourTree_Slime()
    {
        EndNode Eed = new EndNode(this);
        EndAttack endAttack = new EndAttack(this);


        PatrolNode patrol = new PatrolNode(astarAI, this.transform.position, -2, 2, -2, 2);
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


        PatrolNode patrol = new PatrolNode(astarAI, this.transform.position, -4, 4, -4, 4);
        ChasePlayer chase = new ChasePlayer(astarAI, this);
        AttackNode attack = new AttackNode(this);

        DoNothing doNothing2f_Patrol = new DoNothing(1f, "patrol", true, this);
        DoNothing doNothing2f_Attack = new DoNothing(0.5f, "attack", false, this);

        AttackNode = new Sequence(new List<Node> { doNothing2f_Attack, chase, attack, Eed });
        PatrolNode = new Sequence(new List<Node> { doNothing2f_Patrol, patrol, Eed });
    }
    private void ConstructBehaviourTree_Zombile()
    {
        EndNode Eed = new EndNode(this);
        EndAttack endAttack = new EndAttack(this);
        CheckNear checkNear = new CheckNear(this);
        PatrolNode patrol = new PatrolNode(astarAI, this.transform.position, -4, 4, -4, 4);
        ChasePlayer chase = new ChasePlayer(astarAI, this);
        //AttackNode attack = new AttackNode(this);
        meleeAttackNode meleeAttack = new meleeAttackNode(this);

        DoNothing doNothing_Patrol = new DoNothing(3f, "patrol", true, this);
        DoNothing doNothing_Attack = new DoNothing(1f, "attack", false, this);
        DoNothing doNothing_Chase = new DoNothing(0.5f, "chase", false, this);


        AttackNode = new Sequence(new List<Node> { doNothing_Attack, checkNear, meleeAttack, Eed });
        ChaseNode = new Sequence(new List<Node> { doNothing_Chase, chase, AttackNode, checkNear, Eed });
        PatrolNode = new Sequence(new List<Node> { doNothing_Patrol, patrol, Eed });
    }

    private void ConstructBehaviourTree_Ghost()
    {
        EndNode Eed = new EndNode(this);
        EndAttack endAttack = new EndAttack(this);

        CheckNear checkNear = new CheckNear(this);
        PatrolNode patrol = new PatrolNode(astarAI, this.transform.position, -4, 4, -4, 4);


        RangeAttackNode attack = new RangeAttackNode(this);
        DoNothing doNothing2f_Patrol = new DoNothing(2f, "patrol", true, this);
        DoNothing doNothing2f_Attack = new DoNothing(1f, "attack", false, this);

        AttackNode = new Sequence(new List<Node> { doNothing2f_Attack, patrol,checkNear, attack, Eed });
        PatrolNode = new Sequence(new List<Node> { doNothing2f_Patrol, patrol, Eed });
    }
    private void ConstructBehaviourTree_EliteGhost()
    {
        EndNode Eed = new EndNode(this);
        EndAttack endAttack = new EndAttack(this);

        CheckNear checkNear = new CheckNear(this);
        PatrolNode patrol = new PatrolNode(astarAI, this.transform.position, -4, 4, -4, 4);
        PointAttackNode attack = new PointAttackNode(this);


        DoNothing doNothing2f_Patrol = new DoNothing(2f, "patrol", true, this);
        DoNothing doNothing2f_Attack = new DoNothing(1f, "attack", false, this);

        AttackNode = new Sequence(new List<Node> { doNothing2f_Attack, patrol, checkNear, attack, Eed });

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
            case "chase":
                ChaseNode.Evaluate();
                break;
        }
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class PonTreeAi : MonoBehaviour
{
    GameObject player;
    [SerializeField] GameObject pon;
    [SerializeField] GameObject ponPivot;
    [SerializeField] GameObject FindPivot1;
    [SerializeField] GameObject FindPivot2;
    public Animator animator;
    float duration = 0.46511627906976744186046511627907f;
    public float step = 1f;
    public float delayTime = 10f;
    public float dirCheckNum;

    public bool isWaitEnd = false;
    public bool isTimerOn = false;

    public Sequence topNode;
    public Coroutine evaluateCoroutine;


    void Start()
    {
        animator = pon.GetComponent<Animator>();
        player = GameObject.FindWithTag("Player");
       ConstructBehaviourTree();
       evaluateCoroutine = StartCoroutine(StartEvaluate());
     
    }

    void Update()
    {
        moveDir();

    }

    public void StartEvaluateCoroutine()
    {
        evaluateCoroutine = StartCoroutine(StartEvaluate());
    }

    public void StopEvaluateCoroutine()
    {
        StopCoroutine(evaluateCoroutine);
    }

    IEnumerator StartEvaluate()
    {
        while (!isTimerOn)
        {
            yield return null;
            topNode.Evaluate();
        }
    }

    private void ConstructBehaviourTree()
    {
        FindMoveNode findMoveNode = new FindMoveNode(pon, player, FindPivot1, this);
        FindMoveNode2 findMoveNode2 = new FindMoveNode2(pon, player, FindPivot2, this);


        PonSetDirNode ponSetDirNode = new PonSetDirNode(pon, player, ponPivot, FindPivot1, FindPivot2);
        WaitNode waitNode = new WaitNode(delayTime, this);
        MoveNode moveNode = new MoveNode(pon, ponPivot, duration, this);


        Selector findPlayerSelector = new Selector(new List<Node> { findMoveNode, findMoveNode2 });
        Selector moveSelector = new Selector(new List<Node> { findPlayerSelector, moveNode });

        topNode = new Sequence(new List<Node> {  ponSetDirNode, waitNode, moveSelector });

    }

 
    public void StartWaitCoroutine(WaitNode waitNode)//Wait코루틴 시작 함수
    {
        StartCoroutine(Wait( waitNode));
    }


    IEnumerator Wait(WaitNode waitNode)//Wait코루틴
    {

        delayTime = 0.93023255813953488372093023255814f* 3f;
        while(delayTime > 0)
        {
            transform.gameObject.tag = "PonCanKilled";
            //Debug.Log("기다리는중");

            delayTime -= Time.deltaTime;
            yield return null;
        }

        StartEvaluateCoroutine();
    }

    public void StartLerpCoroutine(MoveNode moveNode)
    {
        //StartCoroutine(Lerp(moveNode));
        StartCoroutine(moveCoroutine(ponPivot.transform.position));
    }



    public void StartLerpCoroutine2(FindMoveNode findMoveNode)
    {
        //StartCoroutine(Lerp(moveNode));
        StartCoroutine(moveCoroutine(FindPivot1.transform.position));
    }

    public void StartLerpCoroutine3(FindMoveNode2 findMoveNode2)
    {
        //StartCoroutine(Lerp(moveNode));
        StartCoroutine(moveCoroutine(FindPivot2.transform.position));
    }

    IEnumerator moveCoroutine(Vector2 endPos)
    {
        float startTime = Time.time;
        Vector2 startPos = transform.localPosition;


        while (Time.time - startTime <= duration)
        {
            pon.gameObject.tag = "PonCanKill";
            transform.localPosition = Vector2.Lerp(startPos, endPos, (Time.time - startTime) / duration);
            yield return null;
        }

        transform.localPosition = endPos;


    }






        public void SetDir(GameObject pon, GameObject player)
    {
        if (Mathf.Abs(player.transform.position.x - pon.transform.position.x) > Mathf.Abs(player.transform.position.y - pon.transform.position.y))
        {
            if ((player.transform.position.x - pon.transform.position.x) > 0)
            {
                ponPivot.transform.localPosition = new Vector3(1.1f, 0, 0);
                FindPivot1.transform.localPosition = new Vector3(1.1f, 1.1f, 0);
                FindPivot2.transform.localPosition = new Vector3(1.1f, -1.1f, 0);
                dirCheckNum = 0;

            }
            if ((player.transform.position.x - pon.transform.position.x) <= 0)
            {
                ponPivot.transform.localPosition = new Vector3(-1.1f, 0, 0);
                FindPivot1.transform.localPosition = new Vector3(-1.1f, 1.1f, 0);
                FindPivot2.transform.localPosition = new Vector3(-1.1f, -1.1f, 0);
                dirCheckNum = 0;

            }
        }
        if (Mathf.Abs(player.transform.position.x - pon.transform.position.x) <= Mathf.Abs(player.transform.position.y - pon.transform.position.y))
        {
            if ((player.transform.position.y - pon.transform.position.y) > 0)
            {
                ponPivot.transform.localPosition = new Vector3(0, 1.1f, 0);
                FindPivot1.transform.localPosition = new Vector3(1.1f, 1.1f, 0);
                FindPivot2.transform.localPosition = new Vector3(-1.1f, 1.1f, 0);
                dirCheckNum = 0;

            }
            if ((player.transform.position.y - pon.transform.position.y) <= 0)
            {
                ponPivot.transform.localPosition = new Vector3(0, -1.1f, 0);
                FindPivot1.transform.localPosition = new Vector3(1.1f, -1.1f, 0);
                FindPivot2.transform.localPosition = new Vector3(-1.1f, -1.1f, 0);
                dirCheckNum = 0;

            }
        }


    }
    public void moveDir()
    {
        if (ponPivot.transform.localPosition.x > 0.5f   && pon.tag == "PonCanKilled")
        {

            animator.SetFloat("Ver", -0.5f);
            animator.SetFloat("Hor", 2);
            animator.SetFloat("Rgh", 0);
        }
        if (ponPivot.transform.localPosition.x > 0.5f  && pon.tag == "PonCanKill")
        {

            animator.SetFloat("Ver", -0.5f);
            animator.SetFloat("Hor", -2);
            animator.SetFloat("Rgh", 1);
        }



        if (ponPivot.transform.localPosition.x < -0.5f && pon.tag == "PonCanKilled")
        {

            animator.SetFloat("Ver", 1);
            animator.SetFloat("Hor", 2);
            animator.SetFloat("Lft", 0);
        }
        if (ponPivot.transform.localPosition.x < -0.5f && pon.tag == "PonCanKill")
        {

            animator.SetFloat("Ver", 1);
            animator.SetFloat("Hor", -2);
            animator.SetFloat("Lft", 1);
        }



        if (ponPivot.transform.localPosition.y > 0.5f && pon.tag == "PonCanKilled")
        {

            animator.SetFloat("Ver", -1);
            animator.SetFloat("Hor", 2);
            animator.SetFloat("Back", 0);
        }
        if (ponPivot.transform.localPosition.y > 0.5f && pon.tag == "PonCanKill")
        {

            animator.SetFloat("Ver", -1);
            animator.SetFloat("Hor", -2);
            animator.SetFloat("Back", 1);
        }




        if (ponPivot.transform.localPosition.y < -0.5f && pon.tag == "PonCanKilled")
        {

            animator.SetFloat("Ver", 0.5f);
            animator.SetFloat("Hor", 2);
            animator.SetFloat("Fwd", 0);
        }
        if (ponPivot.transform.localPosition.y < -0.5f && pon.tag == "PonCanKill")
        {

            animator.SetFloat("Ver", 0.5f);
            animator.SetFloat("Hor", -2);
            animator.SetFloat("Fwd", 1);
        }


    }


}

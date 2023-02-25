using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PonSetDirNode : Node
{
    private PonTreeAi ai;
    private GameObject pon;
    private GameObject player;
    private GameObject ponPivot;
    private GameObject FindPivot1;
    private GameObject FindPivot2;



    public PonSetDirNode(GameObject pon, GameObject player, GameObject ponPivot, GameObject FindPivot1, GameObject FindPivot2)
    {
        this.pon = pon;
        this.player = player;
        this.ponPivot = ponPivot;
        this.FindPivot1 = FindPivot1;
        this.FindPivot2 = FindPivot2;
    }

    public override NodeState Evaluate()
    {
        if (Mathf.Abs(ponPivot.transform.localPosition.x) > 1)
        {
            return NodeState.SUCCESS;
        }
        if (Mathf.Abs(ponPivot.transform.localPosition.y) > 1)
        {
            return NodeState.SUCCESS;
        }
        if (Mathf.Abs(player.transform.position.x - pon.transform.position.x) > Mathf.Abs(player.transform.position.y - pon.transform.position.y))
        {
            if ((player.transform.position.x - pon.transform.position.x) > 0)
            {
                ponPivot.transform.localPosition = new Vector3(1.1f, 0, 0);
                FindPivot1.transform.localPosition = new Vector3(1.1f, 1.1f, 0);
                FindPivot2.transform.localPosition = new Vector3(1.1f, -1.1f, 0);
                Debug.Log("좌표를 설정합니다");
                return NodeState.SUCCESS;

            }
            if ((player.transform.position.x - pon.transform.position.x) <= 0)
            {
                ponPivot.transform.localPosition = new Vector3(-1.1f, 0, 0);
                FindPivot1.transform.localPosition = new Vector3(-1.1f, 1.1f, 0);
                FindPivot2.transform.localPosition = new Vector3(-1.1f, -1.1f, 0);
                Debug.Log("좌표를 설정합니다");
                return NodeState.SUCCESS;

            }
        }
        else if (Mathf.Abs(player.transform.position.x - pon.transform.position.x) <= Mathf.Abs(player.transform.position.y - pon.transform.position.y))
        {
            if ((player.transform.position.y - pon.transform.position.y) > 0)
            {
                ponPivot.transform.localPosition = new Vector3(0, 1.1f, 0);
                FindPivot1.transform.localPosition = new Vector3(1.1f, 1.1f, 0);
                FindPivot2.transform.localPosition = new Vector3(-1.1f, 1.1f, 0);
                //Debug.Log("좌표를 설정합니다");
                return NodeState.SUCCESS;

            }
            if ((player.transform.position.y - pon.transform.position.y) <= 0)
            {
                ponPivot.transform.localPosition = new Vector3(0, -1.1f, 0);
                FindPivot1.transform.localPosition = new Vector3(1.1f, -1.1f, 0);
                FindPivot2.transform.localPosition = new Vector3(-1.1f, -1.1f, 0);
                //Debug.Log("좌표를 설정합니다");
                return NodeState.SUCCESS;

            }
        }

        else
        {
            Debug.Log("setdir fal");
            return NodeState.FAILURE;
        }
        Debug.Log("setdir fal");
        return NodeState.FAILURE;
    }

    
}

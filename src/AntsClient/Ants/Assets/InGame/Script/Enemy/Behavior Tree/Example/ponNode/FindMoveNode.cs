using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FindMoveNode : Node
{
    private GameObject pon;
    private GameObject player;
    private GameObject findPivot1;
    private PonTreeAi ai;




    public FindMoveNode(GameObject pon, GameObject player, GameObject findPivot1, PonTreeAi ai)
    {
        this.pon = pon;
        this.player = player;
        this.findPivot1 = findPivot1;
        this.ai = ai;
    }




    public override NodeState Evaluate()
    {

        if (Mathf.Abs(player.transform.position.x - findPivot1.transform.position.x) < 0.5f && Mathf.Abs(player.transform.position.y - findPivot1.transform.position.y) < 0.5f)
        {
            ai.StartLerpCoroutine2(this);

            return NodeState.SUCCESS;
        }
        else
            return NodeState.FAILURE;
    }


}

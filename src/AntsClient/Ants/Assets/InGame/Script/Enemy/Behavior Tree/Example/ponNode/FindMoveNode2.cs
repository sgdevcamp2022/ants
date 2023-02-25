using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FindMoveNode2 : Node
{
    private GameObject pon;
    private GameObject player;
    private GameObject findPivot2;
    private PonTreeAi ai;




    public FindMoveNode2(GameObject pon, GameObject player, GameObject findPivot2, PonTreeAi ai)
    {
        this.pon = pon;
        this.player = player;
        this.findPivot2 = findPivot2;
        this.ai = ai;
    }




    public override NodeState Evaluate()
    {
        if (Mathf.Abs(player.transform.position.x - findPivot2.transform.position.x) < 0.5f && Mathf.Abs(player.transform.position.y - findPivot2.transform.position.y) < 0.5f)
        {
            ai.StartLerpCoroutine3(this);
            return NodeState.SUCCESS;
        }
        else
            return NodeState.FAILURE;
    }


}

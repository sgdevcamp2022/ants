using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyNode : Node
{
    private GameObject pon;
    private PonTreeAi ai;

    public DestroyNode(PonTreeAi ai, GameObject pon)
    {
        this.ai = ai;
        this.pon = pon;
    }

    public override NodeState Evaluate()
    {
        Debug.Log("destroynode");


        return NodeState.SUCCESS;


    }
}

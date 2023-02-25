using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaitNode : Node
{
    public float delayTime = 3f;
    private float count;
    private PonTreeAi ai;
    
    // Start is called before the first frame update

    public WaitNode(float delayTime, PonTreeAi ai)
    {
        this.delayTime = delayTime;
        this.ai = ai;
    }



    public override NodeState Evaluate()
    {
        return NodeState.FAILURE;
        /*
        ai.StopEvaluateCoroutine();
        ai.StartWaitCoroutine();

        if (IsWaiting)
        {
            IsWaiting = true;
            return NodeState.SUCCESS;
        }
        else
        {
            IsWaiting = true;
            return NodeState.FAILURE;
        }
        */

    }
}


    
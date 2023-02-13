using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DoNothing : Node
{
    private float delayTime;
    private SlimeBrain ai;
    private string upper;

    public DoNothing(float delayTime, string upperNode , SlimeBrain brain)
    {
        this.delayTime = delayTime;
        this.ai = brain;
        upper = upperNode;
    }

    public override NodeState Evaluate()
    {
        if (ai.IsWaiting)
        {
            Debug.Log("기다림 끝");
            ai.IsWaiting = false;
            return NodeState.SUCCESS;
        }
        else
        {
            Debug.Log("기다리기");
            ai.IsWaiting = true;
            ai.StartWaitCoroutine(delayTime, upper);
            return NodeState.FAILURE;
        }
    }

}

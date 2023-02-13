using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DoNothing : Node
{
    private float delayTime;
    private Brain ai;
    private string upper;
    private bool isRandom;
    public DoNothing(float delayTime, string upperNode ,bool random, Brain brain)
    {
        this.delayTime = delayTime;
        this.ai = brain;
        upper = upperNode;
        isRandom = random;
    }

    public override NodeState Evaluate()
    {
        if (ai.IsWaiting)
        {

            ai.IsWaiting = false;
            return NodeState.SUCCESS;
        }
        else
        {

            ai.IsWaiting = true;
            ai.StartWaitCoroutine(delayTime, upper, isRandom);
            return NodeState.FAILURE;
        }
    }

}

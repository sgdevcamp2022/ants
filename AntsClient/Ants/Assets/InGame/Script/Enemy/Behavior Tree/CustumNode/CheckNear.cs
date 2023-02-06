using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckNear : Node
{
    private Brain ai;

    // Start is called before the first frame update
    public CheckNear(Brain brain)
    {
        ai = brain;
    }
    public override NodeState Evaluate()
    {
        if (ai.nearPlayer)
        {
            return NodeState.SUCCESS;
        }
        else
        {
            ai.isEnd = true;
            return NodeState.FAILURE;
        }

    }
}

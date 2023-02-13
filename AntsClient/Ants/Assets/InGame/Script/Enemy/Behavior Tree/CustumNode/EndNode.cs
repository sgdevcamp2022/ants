using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EndNode : Node
{

    private Brain ai;

    // Start is called before the first frame update
    public EndNode(Brain brain)
    {
        ai = brain;
    }
    public override NodeState Evaluate()
    {
        ai.isEnd = true;
        return NodeState.SUCCESS;
    }
}

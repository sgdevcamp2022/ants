using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RecognizeNode : Node
{
    private Brain ai;

    // Start is called before the first frame update
    public RecognizeNode(Brain brain)
    {
        ai = brain;
    }
    public override NodeState Evaluate()
    {
        return NodeState.SUCCESS;
    }
}

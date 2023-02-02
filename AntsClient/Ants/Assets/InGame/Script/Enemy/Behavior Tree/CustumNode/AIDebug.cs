using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AIDebug : Node
{
    private string message;
    private SlimeBrain ai;

    // Start is called before the first frame update
    public AIDebug(SlimeBrain brain, string debug)
    {
        message = debug;
        ai = brain;
    }
    public override NodeState Evaluate()
    {
        Debug.Log(message);
        return NodeState.SUCCESS;
    }
}

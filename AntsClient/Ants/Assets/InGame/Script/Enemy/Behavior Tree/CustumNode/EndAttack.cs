using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EndAttack : Node
{

    private SlimeBrain ai;

    // Start is called before the first frame update
    public EndAttack(SlimeBrain brain)
    {
        ai = brain;
    }
    public override NodeState Evaluate()
    {
        ai.isAttacked = false;
        return NodeState.SUCCESS;
    }
}

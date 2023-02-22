using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EndAttack : Node
{

    private Brain ai;

    // Start is called before the first frame update
    public EndAttack(Brain brain)
    {
        ai = brain;
    }
    public override NodeState Evaluate()
    {
        ai.isAttacked = false;
        return NodeState.SUCCESS;
    }
}

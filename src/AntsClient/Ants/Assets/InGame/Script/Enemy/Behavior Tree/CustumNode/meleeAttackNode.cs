using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Pathfinding;
public class meleeAttackNode : Node
{
    private Brain ai;

    // Start is called before the first frame update
    public meleeAttackNode(Brain brain)
    {
        ai = brain;
    }
    public override NodeState Evaluate()
    {
        ai.enemyAttack.meleeAttack();
        return NodeState.SUCCESS;
    }
}

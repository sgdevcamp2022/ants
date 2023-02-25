using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Pathfinding;
public class PointAttackNode : Node
{
    private Brain ai;

    // Start is called before the first frame update
    public PointAttackNode(Brain brain)
    {
        ai = brain;
    }
    public override NodeState Evaluate()
    {
        ai.enemyAttack.PointAttack();
        return NodeState.SUCCESS;
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Pathfinding;
public class AttackNode : Node
{
    private Brain ai;

    // Start is called before the first frame update
    public AttackNode(Brain brain)
    {
        ai = brain;
    }
    public override NodeState Evaluate()
    {
        ai.enemyAttack.Attack();
        return NodeState.SUCCESS;
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Pathfinding;
public class AttackNode : Node
{
    private SlimeBrain ai;

    // Start is called before the first frame update
    public AttackNode(SlimeBrain brain)
    {
        ai = brain;
    }
    public override NodeState Evaluate()
    {
        Debug.Log("공격");
        ai.enemyAttack.Attack();
        return NodeState.SUCCESS;
    }
}

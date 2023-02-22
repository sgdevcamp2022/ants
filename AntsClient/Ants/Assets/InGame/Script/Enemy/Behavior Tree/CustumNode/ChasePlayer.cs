using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Pathfinding;
public class ChasePlayer : Node
{
    Vector2 playerPosition;
    IAstarAI patrolAi;
    Brain brain;

    // Start is called before the first frame update
    public ChasePlayer(IAstarAI patrol, Brain ai)
    {
        patrolAi = patrol;
        brain = ai;
    }
    public override NodeState Evaluate()
    {
        if (!brain.nearPlayer)
        {
            playerPosition = brain.player.transform.position;

            patrolAi.destination = playerPosition;
        }

        return NodeState.SUCCESS;
    }
}

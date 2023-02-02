using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Pathfinding;
public class PatrolNode : Node
{
    Vector2 originPosition;
    Vector2 patrolPosition;
    IAstarAI patrolAi;

    // Start is called before the first frame update
    public PatrolNode(IAstarAI patrol, Vector2 origin)
    {
        patrolAi = patrol;
        originPosition = origin;
    }
    public override NodeState Evaluate()
    {
        Debug.Log("패트롤시작");
        float x = Random.Range(-2f, 2f);
        float y = Random.Range(-2f, 2f);
        patrolPosition = new Vector2(originPosition.x + x, originPosition.y + y);

        patrolAi.destination = patrolPosition;
        return NodeState.SUCCESS;
    }
}

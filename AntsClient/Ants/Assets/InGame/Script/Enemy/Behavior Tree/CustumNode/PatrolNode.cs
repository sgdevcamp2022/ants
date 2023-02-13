using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Pathfinding;
public class PatrolNode : Node
{
    Vector2 originPosition;
    Vector2 patrolPosition;
    IAstarAI patrolAi;

    float x_Min;
    float x_Max;
    float y_Min;
    float y_Max;


    // Start is called before the first frame update
    public PatrolNode(IAstarAI patrol, Vector2 origin, float xMin, float xMax, float yMin, float yMax)
    {
        patrolAi = patrol;
        originPosition = origin;
        x_Min = xMin;
        x_Max = xMax;
        y_Min = yMin;
        y_Max = yMax;
    }
    public override NodeState Evaluate()
    {
        float x = Random.Range(x_Min, x_Max);
        float y = Random.Range(y_Min, y_Max);
        patrolPosition = new Vector2(originPosition.x + x, originPosition.y + y);

        patrolAi.destination = patrolPosition;
        return NodeState.SUCCESS;
    }
}

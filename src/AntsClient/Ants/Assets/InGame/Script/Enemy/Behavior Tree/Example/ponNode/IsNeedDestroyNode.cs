using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsNeedDestroyNode : Node
{
    private GameObject pon;

    public IsNeedDestroyNode(GameObject pon)
    {
        this.pon = pon;
    }

    public override NodeState Evaluate()
    {

        if (pon.transform.position.x > 5.2 || pon.transform.position.x < -4.2 || pon.transform.position.y > 4.2 || pon.transform.position.y < -5.2)
        {
            Debug.Log("폰을 삭제합니다");
            return NodeState.FAILURE;
        }

        else
        {
            //Debug.Log("폰이 삭제될 상황이 아닙니다");
            return NodeState.SUCCESS;
        }


    }
}


using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AnimationHandler_Slime : MonoBehaviour
{
    Animator ani;
    private void Awake()
    {
        ani = GetComponent<Animator>();
    }


}

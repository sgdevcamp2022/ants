using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScreenSize : MonoBehaviour
{
    public void SetSize()
    {
#if UNITY_EDITOR
        Debug.Log("size!");
#else
        Screen.SetResolution(1920,1080,false);
#endif
    }
}

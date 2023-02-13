using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScreenSize : MonoBehaviour
{

    public void OnWindowMode()
    {
        Screen.SetResolution(1920,1080,false);
    }

    public void OffWindowMode()
    {
        Screen.SetResolution(1920, 1080, true);
    }
}

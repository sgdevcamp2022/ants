using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SetScreenSize : MonoBehaviour
{

    private void Start()
    {
        OffWindowMode();
    }
    public void OffWindowMode()
    {
        Screen.SetResolution(1920, 1080, true);
    }
}

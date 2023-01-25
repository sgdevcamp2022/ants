using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.UI;
using TMPro;
//using System.Runtime.InteropServices;

public class NumberCheck : MonoBehaviour
{

    //public GameObject Login;
    public TMP_InputField number;
    public GameObject text;
    public TextMeshProUGUI textMeshPro;

    string fakeNum = "1234";

    public void OnClickCheck()
    {
       
        if (fakeNum == number.text)
        {
            textMeshPro.SetText("Right Number");
            text.SetActive(true);
           // Debug.Log(number.text);
            
        }
        else
        {
            textMeshPro.SetText("different");
            text.SetActive(true);
            //Debug.Log(number.text);
            
        }



    }
}



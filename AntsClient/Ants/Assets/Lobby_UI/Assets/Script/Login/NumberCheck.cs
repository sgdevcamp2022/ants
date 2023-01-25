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
    public InputField number;
    public GameObject text;
    public TextMeshProUGUI textMeshPro;

    string fakeNum = "1234";
    public void OnClickCheck()
    {
        
        if (fakeNum == number.text)
        {
            text.SetActive(true);
        }
        else
        {
            textMeshPro.text = "different";
            text.SetActive(true);
            //number.text = "";
            //number.ActivateInputField();
            //OnClickCheck();>>오류 어떻게 OnClcik함수로 갈 수 있지?
            //받은 값으로 OnclickCheck()함수 실행 되어야함
        }



    }
}



using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using System.Xml.Serialization;

public class PwConfirm : MonoBehaviour
{
    //pw에 입력된 값과 confirm에 입력된 값이 같다면 same 글씨 뜨게하기
    public TMP_InputField pw;
    public TMP_InputField pwConfirm;
    public GameObject text;
    public TextMeshProUGUI textMeshPro;

   public void PwSame()
    {
        if(pw.text == pwConfirm.text)
        {
            textMeshPro.SetText("Same");
            text.SetActive(true);
        }
        else
        {
            textMeshPro.SetText("different");
            text.SetActive(true);
        }
    }

}

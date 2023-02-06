using GraphQlClient.Core;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using TMPro;
using UnityEngine;
using UnityEngine.Networking;

public class SendBtn : MonoBehaviour
{
    public TMP_InputField emailField;
    public GraphApi api;
    public string Token;

    public TMP_InputField numberField;
    public GameObject text;
    public TextMeshProUGUI textMeshPro;
    public async void sendEmail()
    {
        GraphApi.Query email = api.GetQueryByName("sendEmail", GraphApi.Query.Type.Mutation);

        email.SetArgs(new { email = $"{emailField.text}" });
        UnityWebRequest request = await api.Post(email);
        string data = request.downloadHandler.text;
        JObject obj = JObject.Parse(data);//파싱

        Token = obj["data"]["sendEmail"].ToString();
        Debug.Log("1" + Token);
        //이미 가입된 이메일이면 뭐라고 오는지?
    }
    public async void NumberCheck()
    {
        Debug.Log("2" + Token);
        GraphApi.Query number = api.GetQueryByName("checkEmail", GraphApi.Query.Type.Mutation);
        number.SetArgs(new { eToken = $"{numberField.text}",hashedToken=$"{Token}"});
        UnityWebRequest request = await api.Post(number);
        string data = request.downloadHandler.text;
        JObject obj = JObject.Parse(data);//파싱
        Debug.Log(data);

      
        if (obj["data"]["checkEmail"].ToString()=="true")
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


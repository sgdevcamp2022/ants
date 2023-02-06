using GraphQlClient.Core;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using TMPro;
using UnityEngine;
using UnityEngine.Networking;

public class EnterBtn : MonoBehaviour
{
    public TMP_InputField idField;
    public TMP_InputField pwField;
    public GameObject lobby;
    public GameObject falseText;
    public GameObject login;
    public GraphApi api;
    public async void Login()
    {
        GraphApi.Query loginUser = api.GetQueryByName("login", GraphApi.Query.Type.Mutation);

        loginUser.SetArgs(new { email = $"{idField.text}", psword = $"{pwField.text}" });
        UnityWebRequest request = await api.Post(loginUser);
        string data = request.downloadHandler.text;
        JObject obj = JObject.Parse(data);//파싱
        
        if (obj["errors"]!=null)
        {
            falseText.SetActive(true);
            Debug.Log(data);

        }
        else if(obj["data"]["login"].ToString()!=null)
        {
            lobby.SetActive(true);
            login.SetActive(false);
            //토큰을 로비한테 보내주면되겠네?
            Debug.Log(obj["data"]["login"].ToString());

        }
    }


}
 


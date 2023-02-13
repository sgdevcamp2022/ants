using GraphQlClient.Core;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using TMPro;
using UnityEngine;
using UnityEngine.Networking;

public class NicknameCheck : MonoBehaviour
{
    public TMP_InputField nicknameField;
    public GameObject nicknameText;
    public GraphApi api;
    public TextMeshProUGUI existText;
    public async void Nickname()
    {
        GraphApi.Query nicknameUser = api.GetQueryByName("checkNick", GraphApi.Query.Type.Mutation);

        nicknameUser.SetArgs(new { nick = $"{nicknameField.text}" });
        UnityWebRequest request = await api.Post(nicknameUser);
        string data = request.downloadHandler.text;
        JObject obj = JObject.Parse(data);//파싱

        if (obj["data"]["checkNick"].ToString() == "true")
        {
            existText.SetText("Possible");
            nicknameText.SetActive(true);
            // Debug.Log(number.text);

        }
        else
        {
            existText.SetText("Impossible");
            nicknameText.SetActive(true);
            //Debug.Log(number.text);
        }

    }
}

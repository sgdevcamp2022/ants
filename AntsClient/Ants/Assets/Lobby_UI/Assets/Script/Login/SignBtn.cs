using GraphQlClient.Core;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using TMPro;
using UnityEngine;
using UnityEngine.Networking;

public class SignBtn : MonoBehaviour
{
    //email & pw & (confirm에 찍힌 pw, 아래 same이라는 글씨 뜨면 눌려지게..) &닉네임 &오늘의 날짜 보내주기

    public TextMeshProUGUI numberText;
    public TextMeshProUGUI confirmText;
    public TextMeshProUGUI nicknameText;
    public GraphApi api;

    public TMP_InputField emailField;
    public TMP_InputField passwordField;
    public TMP_InputField nicknameField;
    public GameObject noSign;
    public GameObject loginMode;
    public GameObject newMemberMode;
    public async void createUser()
    {

        if (numberText.text == "Right Number" && confirmText.text == "Same" && nicknameText.text == "Possible")
        {
            Debug.Log("입력은 다 됐음");
            GraphApi.Query create = api.GetQueryByName("createUser", GraphApi.Query.Type.Mutation);
            create.SetArgs(new { email = $"{emailField.text}", psword = $"{passwordField.text}", nickname = $"{nicknameField.text}" });
            UnityWebRequest request = await api.Post(create);
            string data = request.downloadHandler.text;
            JObject obj = JObject.Parse(data);//파싱

            //Debug.Log(data);

            if (obj["data"]["createUser"].ToString() != null)
            {
                newMemberMode.SetActive(false);
                loginMode.SetActive(true);
            }

        }
        else
            noSign.SetActive(true);
    }
}

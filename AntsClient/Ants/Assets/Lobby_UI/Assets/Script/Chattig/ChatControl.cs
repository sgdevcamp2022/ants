using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class ChatControl : MonoBehaviour
{
    public GameObject chatPrefab;
    public Transform parentContent;
    public TMP_InputField inputField;
    public string id = "me"; 
    //상대가 보낸 메세지가 있다면 id가 상대 아이디인 프리팹이 생성되어야함.
    private void Update()
    {
        if(Input.GetKeyDown(KeyCode.Return) && inputField.isFocused == false)
        {
            inputField.ActivateInputField();
        }
    }
    public void OnEditEventMethod()
    {
        if (Input.GetKeyDown(KeyCode.Return))
        {
            UpdateChat();
        }
    }
    public void UpdateChat()
    {
        if (inputField.text.Equals("")) return;
        GameObject chat = Instantiate(chatPrefab,parentContent);

        if (id.Equals("me"))
        {
            chat.GetComponent<TextMeshProUGUI>().color = Color.blue;
        }
        //else me가 아닌 상대 아이디이면 하얀색으로 나옴
        chat.GetComponent<TextMeshProUGUI>().text = $"{id} : {inputField.text}";
        inputField.text = "";

    }

}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SetTestID : MonoBehaviour
{
    public InputField UserIDInput;
    public NetworkManager_packet networkManager_Packet;

    private void Update()
    {
        if (UserIDInput.text != null && Input.GetKeyDown(KeyCode.Return))
        {
            DatabaseManager.UserID = UserIDInput.text;
            networkManager_Packet.EnterRoom((int.Parse)(DatabaseManager.UserID));
        }
    }

}



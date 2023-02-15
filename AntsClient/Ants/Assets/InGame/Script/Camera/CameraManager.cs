using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
public class CameraManager : MonoBehaviour
{
    public float cameraSpeed = 5.0f;
    public PhotonView photonView;
    public GameObject player;

    private void Update()
    {
        if(player != null )
        {
            Vector3 dir = player.transform.position - this.transform.position;
            Vector3 moveVector = new Vector3(dir.x * cameraSpeed * Time.deltaTime, dir.y * cameraSpeed * Time.deltaTime, 0.0f);
            this.transform.Translate(moveVector);
        }
        else
        {
            player = GameObject.FindWithTag("Player");

        }


    }
}

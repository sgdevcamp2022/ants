using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using UnityEngine.UI;
public class GameManager : MonoBehaviour
{
    public GameObject PlayerPrefab;
    public GameObject FovPrefab;
    public GameObject SceneCamera;
    public GameObject setPlace;
    private void Awake()
    {

        PhotonNetwork.IsMessageQueueRunning = false;
        SpawnPlayer();
        Invoke("chek", 1);
    }
    public void SpawnPlayer()
    {
        GameObject myFov =  PhotonNetwork.Instantiate(FovPrefab.name, new Vector2(0, 0), Quaternion.identity);

        GameObject myChar = PhotonNetwork.Instantiate(PlayerPrefab.name, setPlace.transform.position, Quaternion.identity);


    }



    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

        
    }

    void chek()
    {


        PhotonNetwork.IsMessageQueueRunning = true;
    }
}

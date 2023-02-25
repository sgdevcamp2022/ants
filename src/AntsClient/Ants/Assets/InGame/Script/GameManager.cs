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
    public GameObject setPlace1;
    public GameObject setPlace2;
    public GameObject setPlace3;
    public GameObject setPlace4;

    public GameObject Ui;
    private void Awake()
    {
        PhotonNetwork.IsMessageQueueRunning = false;
        SpawnPlayer(setPlace1);
        Ui.SetActive(false);

        Black.SetActive(true);


        Invoke("chek", 1);
    }
    public void SpawnPlayer(GameObject setPlace)
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

    public GameObject Black;
    void chek()
    {

        Ui.SetActive(true);
        Black.SetActive(false);
        
        PhotonNetwork.IsMessageQueueRunning = true;
    }
}

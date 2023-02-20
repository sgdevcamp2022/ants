using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AdcNomalAttack_PVP : MonoBehaviour
{
    public GameObject player;
    public GameObject player2;
    public GameObject bullet;
    public Transform pos;
    public float _cooltime = 1;
    public float _curtime = 0;
    public NetworkManager_packet networkManager_Packet;

    // Update is called once per frame
    void Update()
    {
        Vector2 len = Camera.main.ScreenToWorldPoint(Input.mousePosition) - transform.position;
        Vector2 ab = len.normalized;
        _curtime -= Time.deltaTime;
        if (_curtime <= 0)
        {
            if (Input.GetMouseButton(0))
            {
                networkManager_Packet.Attack(ab.x, ab.y);
                _curtime = _cooltime;

            }
           
        }
        if(DatabaseManager.isShoot == true)
        {
            DatabaseManager.isShoot = false;
            float z = Mathf.Atan2(DatabaseManager.ShootY, DatabaseManager.ShootX) * Mathf.Rad2Deg;
            transform.rotation = Quaternion.Euler(0, 0, z);
            GameObject _bullet = Instantiate(bullet, this.transform.position, transform.rotation);
        }

        if (DatabaseManager.isShoot2 == true)
        {
            DatabaseManager.isShoot2 = false;
            float z = Mathf.Atan2(DatabaseManager.ShootY2, DatabaseManager.ShootX2) * Mathf.Rad2Deg;
            player2.transform.rotation = Quaternion.Euler(0, 0, z);
            GameObject _bullet = Instantiate(bullet, player2.transform.position, player2.transform.rotation);
        }
    }
    
    public void getAttack(float x, float y)
    {

    }

}

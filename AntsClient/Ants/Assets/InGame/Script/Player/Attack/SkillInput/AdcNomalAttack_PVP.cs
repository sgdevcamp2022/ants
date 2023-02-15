using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AdcNomalAttack_PVP : MonoBehaviour
{
    public GameObject bullet;
    public Transform pos;
    public float _cooltime = 1;
    public float _curtime = 0;
    

    // Update is called once per frame
    void Update()
    {
        Vector2 len = Camera.main.ScreenToWorldPoint(Input.mousePosition) - transform.position;
        float z = Mathf.Atan2(len.y, len.x) * Mathf.Rad2Deg;
        transform.rotation = Quaternion.Euler(0, 0, z);
        _curtime -= Time.deltaTime;
        if (_curtime <= 0)
        {
            if (Input.GetMouseButton(0))
            {
                Instantiate(bullet, this.transform.position, transform.rotation);
                _curtime = _cooltime;
            }
           
        }
        
    }
    
 
}

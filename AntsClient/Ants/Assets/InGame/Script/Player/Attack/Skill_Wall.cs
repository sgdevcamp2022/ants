using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Skill_Wall : MonoBehaviour
{
    public GameObject bullet;
    public Transform pos;
    public float _cooltime = 1;
    public float _curtime = 0;

    // Update is called once per frame
    void Update()
    {

        _curtime -= Time.deltaTime;
        if (_curtime <= 0)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                Vector3 mousePosition = Input.mousePosition;
                Vector3 target = Camera.main.ScreenToWorldPoint(mousePosition);

                Instantiate(bullet, new Vector3(target.x, target.y,0) , Quaternion.identity);

                _curtime = _cooltime;
            }

        }

    }
}

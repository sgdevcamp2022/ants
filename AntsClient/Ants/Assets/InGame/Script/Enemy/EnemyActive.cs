using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyActive : MonoBehaviour
{
    public GameObject Enemy;

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.tag == "Active")
        {
           
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if(collision.tag == "Active")
        {
            Enemy.SetActive(false);
        }
    }

}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyAttack : MonoBehaviour
{
    public bool inRange;
    public Health PlayerHealth;
    // Start is called before the first frame update

    public void Attack()
    {
        if (inRange)
        {
            PlayerHealth.Hit(10);
        }
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Player")
        {
            inRange = true;
            PlayerHealth = collision.GetComponent<Health>();
        }

    }
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.tag == "Player")
        {
            inRange = false;
        }
    }

}

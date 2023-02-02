using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Health : MonoBehaviour
{
    [SerializeField] float HP;
    EnemyStun enemyStun;
    public Animator ani;
    private void Start()
    {
        enemyStun = GetComponent<EnemyStun>();
        ani = GetComponent<Animator>();
    }
    private void Update()
    {
        if (HP <= 0)
        {
            Destroy(this.gameObject);
        }
    }
    public void Hit(float damage)
    {
        HP -= damage;
        ani.SetBool("hit", true);
        if(this.tag == "Enemy")
        {
            enemyStun.Stun();
        }

    }
    public void endHitAnimation()
    {
        ani.SetBool("hit", false);
    }
}

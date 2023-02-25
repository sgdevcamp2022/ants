using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet_Continuing_Cap : MonoBehaviour
{
    [SerializeField] float holdingTime;
    [SerializeField] float damage;
    [SerializeField] float attackCycle;
    [SerializeField] float stunTime;
    [SerializeField] public float speed;
    CapsuleCollider2D capsuleCollider2D;


    // Start is called before the first frame update
    void Start()
    {
        capsuleCollider2D = GetComponent<CapsuleCollider2D>();
        Invoke("DestroyBullet", holdingTime);
        InvokeRepeating("CheckIsAttack", attackCycle, attackCycle);
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(Vector2.right * speed * Time.deltaTime);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Enemy" && this.transform.tag == "P_Bullet" )
        {
            Health health = collision.GetComponent<Health>();
            health.Hit(damage, stunTime);
        }
        if (collision.tag == "Player" && this.transform.tag == "E_Bullet")
        {
            Health health = collision.GetComponent<Health>();
            health.Hit(damage, stunTime);
        }
    }


    void CheckIsAttack()
    {
        if (capsuleCollider2D.enabled == true)
        {
            capsuleCollider2D.enabled = false;
        }
        else
        {
            capsuleCollider2D.enabled = true;
        }
    }
    private void DestroyBullet()
    {
        Destroy(gameObject);
    }

}

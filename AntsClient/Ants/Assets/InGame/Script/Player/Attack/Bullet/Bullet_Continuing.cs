using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet_Continuing : MonoBehaviour
{
    [SerializeField] float holdingTime;
    [SerializeField] float damage;
    [SerializeField] float attackCycle;
    [SerializeField] public float speed;
    CircleCollider2D circleCollider;
    // Start is called before the first frame update
    void Start()
    {
        circleCollider = GetComponent<CircleCollider2D>();
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
        if (collision.tag == "Enemy" )
        {
            Health enemyHealth = collision.GetComponent<Health>();
            enemyHealth.Hit(damage);
        }
    }


    void CheckIsAttack()
    {
        if (circleCollider.enabled == true)
        {
            circleCollider.enabled = false;
        }
        else
        {
            circleCollider.enabled = true;
        }
    }
    private void DestroyBullet()
    {
        Destroy(gameObject);
    }

}

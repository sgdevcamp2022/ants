using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet_Continuing_Box : MonoBehaviour
{
    [SerializeField] float holdingTime;
    [SerializeField] float damage;
    [SerializeField] float attackCycle;
    [SerializeField] public float speed;
    BoxCollider2D boxCollider;
    // Start is called before the first frame update
    void Start()
    {
        boxCollider = GetComponent<BoxCollider2D>();
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
            health.Hit(damage);
        }
        if (collision.tag == "Player" && this.transform.tag == "E_Bullet")
        {
            Health health = collision.GetComponent<Health>();
            health.Hit(damage);
        }
    }


    void CheckIsAttack()
    {
        if (boxCollider.enabled == true)
        {
            boxCollider.enabled = false;
        }
        else
        {
            boxCollider.enabled = true;
        }
    }
    private void DestroyBullet()
    {
        Destroy(gameObject);
    }

}

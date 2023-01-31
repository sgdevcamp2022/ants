using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    [SerializeField] float damage;
    [SerializeField] bool collisionDestroy;
    public float speed;
    // Start is called before the first frame update
    void Start()
    {
        Invoke("DestroyBullet", 2);
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(Vector2.right * speed * Time.deltaTime);
    }

    private void DestroyBullet()
    {
        Destroy(gameObject);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.tag == "Obstracle")
        {
            if (collisionDestroy)
            {
                Destroy(gameObject);
            }

        }
        if (collision.tag == "Enemy")
        {
            if (collisionDestroy)
            {
                Health enemyHealth = collision.GetComponent<Health>();
                enemyHealth.Hit(damage);
                Destroy(gameObject);
            }
            else
            {
                Health enemyHealth = collision.GetComponent<Health>();
                enemyHealth.Hit(damage);
                Destroy(gameObject);
            }
        }
    }

}

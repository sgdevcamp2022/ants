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
        if (collision.tag == "Enemy" && this.transform.tag == "P_Bullet")
        {
            Health health = collision.GetComponent<Health>();
            health.Hit(damage);
            Destroy(gameObject);
        }
        if (collision.tag == "Player" && this.transform.tag == "E_Bullet")
        {
            Health health = collision.GetComponent<Health>();
            health.Hit(damage);
            Destroy(gameObject);
        }
    }

}

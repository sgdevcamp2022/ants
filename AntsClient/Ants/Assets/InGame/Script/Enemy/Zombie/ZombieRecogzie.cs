using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ZombieRecogzie : MonoBehaviour
{
    Brain brain;
    CircleCollider2D circleCollider;
    // Start is called before the first frame update
    void Start()
    {
        circleCollider = GetComponent<CircleCollider2D>();
           brain = GetComponentInParent<Brain>();
    }

    // Update is called once per frame
    void Update()
    {

    }
    private void OnTriggerStay2D(Collider2D collision)
    {
        if (collision.tag == "Enemy" && (brain.isAttacked || brain.nearPlayer))
        {
            Debug.Log("1");
            Brain _brain = collision.GetComponent<Brain>();
            _brain.isAttacked = true;
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {

    }
}

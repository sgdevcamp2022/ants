using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Health : MonoBehaviour
{
    [SerializeField] float HP;
    public Animator ani;
    private void Start()
    {
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
    }
    public void endHitAnimation()
    {
        ani.SetBool("hit", false);
    }
}

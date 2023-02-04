using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyAttack : MonoBehaviour
{

    public GameObject AttackPrefab;
    public float x;
    public float y;
    // Start is called before the first frame update

    public void Attack()
    {
        GameObject attack = Instantiate(AttackPrefab, new Vector3 (transform.position.x + x, transform.position.y + y, 2), transform.rotation);
        attack.transform.parent = this.transform;
    }


}

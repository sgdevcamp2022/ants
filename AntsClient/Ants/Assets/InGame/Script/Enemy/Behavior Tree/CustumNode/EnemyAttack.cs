using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyAttack : MonoBehaviour
{
    Brain brain;
    public GameObject AttackPrefab;
    public float x;
    public float y;
    // Start is called before the first frame update
    private void Start()
    {
        brain = GetComponent<Brain>();
    }

    public void Attack()
    {
        GameObject attack = Instantiate(AttackPrefab, new Vector3 (transform.position.x + x, transform.position.y + y, 2), transform.rotation);
        attack.transform.parent = this.transform;
    }
    public void meleeAttack()
    {

        float angle = Mathf.Atan2(brain.player.transform.position.y - transform.position.y, brain.player.transform.position.x - transform.position.x) * Mathf.Rad2Deg;
        GameObject attack = Instantiate(AttackPrefab, brain.player.transform.position, Quaternion.AngleAxis(angle - 20, Vector3.forward));
        attack.transform.parent = this.transform;
    }

}

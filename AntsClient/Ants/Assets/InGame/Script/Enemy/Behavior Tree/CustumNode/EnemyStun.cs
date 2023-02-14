using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyStun : MonoBehaviour
{

    Brain brain;
    [SerializeField] bool isStun;

    public void Start()
    {
        brain = GetComponent<Brain>();

    }

    public void Stun(float time)
    {
        StopAllCoroutines();
        brain.isAttacked = true;
        brain.ResetBrain();
        StartCoroutine(WaitStun(time));
    }

    IEnumerator WaitStun(float time)
    {
        yield return new WaitForSecondsRealtime(time);
        brain.StartEvaluateCoroutine();
    }
}

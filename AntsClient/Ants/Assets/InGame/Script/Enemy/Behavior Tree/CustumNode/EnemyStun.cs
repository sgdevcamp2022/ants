using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyStun : MonoBehaviour
{

    Brain brain;

    public void Start()
    {
        brain = GetComponent<Brain>();

    }

    public void Stun()
    {
        StopAllCoroutines();
        brain.isAttacked = true;
        brain.ResetBrain();
        brain.StopEvaluateCoroutine();
        StartCoroutine(WaitStun());
    }

    IEnumerator WaitStun()
    {
        yield return new WaitForSecondsRealtime(0.5f);
        brain.StartEvaluateCoroutine();
    }
}

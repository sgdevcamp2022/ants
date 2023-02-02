using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyStun : MonoBehaviour
{

    SlimeBrain slimeBrain;

    public void Start()
    {
        slimeBrain = GetComponent<SlimeBrain>();

    }

    public void Stun()
    {
        StopAllCoroutines();
        slimeBrain.isAttacked = true;
        slimeBrain.ResetBrain();
        slimeBrain.StopEvaluateCoroutine();
        StartCoroutine(WaitStun());
    }

    IEnumerator WaitStun()
    {
        yield return new WaitForSecondsRealtime(0.5f);
        slimeBrain.StartEvaluateCoroutine();
    }
}

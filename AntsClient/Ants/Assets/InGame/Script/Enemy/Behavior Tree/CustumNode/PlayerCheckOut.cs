using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCheckOut : MonoBehaviour
{
    public Brain Enemy;
    // Start is called before the first frame update

    
    private void Start()
    {
        
        Enemy = GetComponentInParent<Brain>();
    }
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.tag == "Player")
        {
            Enemy.inRecognize = false;
            Enemy.ResetBrain();
            Enemy.StartEvaluateCoroutine();
        }
    }
}

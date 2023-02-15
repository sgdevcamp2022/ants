using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReceivingSet : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        InvokeRepeating("DisCheck", 0.1f,0.1f);
    }
    void DisCheck()
    {
        DatabaseManager.X = this.transform.position.x;
        DatabaseManager.Y = this.transform.position.y;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}

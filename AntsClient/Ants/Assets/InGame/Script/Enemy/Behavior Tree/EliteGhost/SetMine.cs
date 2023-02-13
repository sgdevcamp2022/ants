using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SetMine : MonoBehaviour
{
    public GameObject mine;
    [SerializeField] float time;
    // Start is called before the first frame update
    void Start()
    {
        
        Invoke("AppearMine", time);
    }

    void AppearMine()
    {
        GameObject attack = Instantiate(mine, transform.position, transform.rotation);
    }
}

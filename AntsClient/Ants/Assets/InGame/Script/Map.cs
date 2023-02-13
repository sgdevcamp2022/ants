using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Map : MonoBehaviour
{

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.tag == "Active")
        {
            int numOfChild = this.transform.childCount;
            for (int i = 0; i < numOfChild; i++)
                transform.GetChild(i).gameObject.SetActive(true);
        }
    }
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.tag == "Active")
        {
            int numOfChild = this.transform.childCount;
            for (int i = 0; i < numOfChild; i++)
                transform.GetChild(i).gameObject.SetActive(false);
        }
    }
}

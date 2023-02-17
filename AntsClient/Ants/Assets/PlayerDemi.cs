using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerDemi : MonoBehaviour
{
    // Update is called once per frame
    void Update()
    {

        if (Input.GetAxisRaw("Horizontal") > 0)
        {
            if (Input.GetAxisRaw("Vertical") > 0)
            {
                DatabaseManager.dir = 5;
            }
            else if (Input.GetAxisRaw("Vertical") < 0)
            {
                DatabaseManager.dir = 7;
            }
            else if ((Input.GetAxisRaw("Vertical") == 0))
            {
                DatabaseManager.dir = 2;
            }
        }
        else if (Input.GetAxisRaw("Horizontal") < 0)
        {
            if (Input.GetAxisRaw("Vertical") > 0)
            {
                DatabaseManager.dir = 4;
            }
            else if (Input.GetAxisRaw("Vertical") < 0)
            {
                DatabaseManager.dir = 6;
            }
            else if ((Input.GetAxisRaw("Vertical") == 0))
            {
                DatabaseManager.dir = 3;
            }
        }
        else if ((Input.GetAxisRaw("Vertical") > 0))
        {
            DatabaseManager.dir = 0;
        }
        else if ((Input.GetAxisRaw("Vertical") < 0))
        {
            DatabaseManager.dir = 1;
        }
        else
        {
            DatabaseManager.dir = 8;
        }
    }
}

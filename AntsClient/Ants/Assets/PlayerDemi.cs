using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerDemi : MonoBehaviour
{
    public string dirr;
    // Update is called once per frame
    void Update()
    {
        dirr = DatabaseManager.dir;

        if (Input.GetAxisRaw("Horizontal") > 0)
        {
            if (Input.GetAxisRaw("Vertical") > 0)
            {
                DatabaseManager.dir = "NE";
            }
            else if (Input.GetAxisRaw("Vertical") < 0)
            {
                DatabaseManager.dir = "SE";
            }
            else if ((Input.GetAxisRaw("Vertical") == 0))
            {
                DatabaseManager.dir = "E";
            }
        }
        else if (Input.GetAxisRaw("Horizontal") < 0)
        {
            if (Input.GetAxisRaw("Vertical") > 0)
            {
                DatabaseManager.dir = "NW";
            }
            else if (Input.GetAxisRaw("Vertical") < 0)
            {
                DatabaseManager.dir = "SW";
            }
            else if ((Input.GetAxisRaw("Vertical") == 0))
            {
                DatabaseManager.dir = "W";
            }
        }
        else if ((Input.GetAxisRaw("Vertical") > 0))
        {
            DatabaseManager.dir = "N";
        }
        else if ((Input.GetAxisRaw("Vertical") < 0))
        {
            DatabaseManager.dir = "S";
        }
        else
        {
            DatabaseManager.dir = "";
        }

    }
}

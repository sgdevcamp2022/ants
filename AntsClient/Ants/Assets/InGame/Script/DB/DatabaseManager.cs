using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DatabaseManager : MonoBehaviour
{
    public static float nowStemina;
    public static float fullStemina;

    public static string playerState;
    public static string nickName;

    public static bool isAction;
    public static bool isRestOneSec;
    
    public static float X;
    public static float Y;
    public static int dir;
    public static int exdir;

    public static int changeDir;

    public static bool isDirChange;
    private void Update()
    {
        if(dir != exdir && isDirChange == false)
        {
            isDirChange = true;
        }

    }

    static public DatabaseManager instance;
    private void Awake()
    {
        dir = 8;
        changeDir = 8;

        isDirChange = false;
        nickName = "PalmTurtle";

        if (instance != null)
        {
            Destroy(this.gameObject);
        }
        else
        {
            DontDestroyOnLoad(this.gameObject);
            instance = this;
        }

    }
}

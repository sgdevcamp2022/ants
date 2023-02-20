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
    

    // player 1
    public static float X;
    public static float Y;
    public static int dir;
    public static int exdir;

    public static int changeDir;

    public static bool isDirChange;
    public static bool isShoot;
    public static float ShootX;
    public static float ShootY;


    public static bool isHit;


    public static string UserID;

    //player 2
    public static float X2;
    public static float Y2;
    public static int dir2;
    public static int exdir2;

    public static int changeDir2;

    public static bool isDirChange2;
    public static bool isShoot2;
    public static float ShootX2;
    public static float ShootY2;

    public static bool isHit2;


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
        isHit = false;
        isHit2 = false;
        
        isShoot = false;
        isShoot2 = false;

        dir = 8;
        dir2 = 8;

        changeDir = 8;
        changeDir2 = 8;

        isDirChange = false;
        isDirChange2 = false;


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

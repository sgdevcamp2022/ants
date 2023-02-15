using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DatabaseManager : MonoBehaviour
{
    public static float nowStemina;
    public static float fullStemina;

    public static string playerState;

    public static bool isAction;
    public static bool isRestOneSec;
    
    public static float X;
    public static float Y;
    public static string dir;
    static public DatabaseManager instance;
    private void Awake()
    {
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

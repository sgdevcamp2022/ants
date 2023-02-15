using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DG.Tweening;
public class test : MonoBehaviour
{
    [SerializeField] float time;
    [SerializeField] float distance;
    string dir;
    // Start is called before the first frame update
    void Start()
    {
        //InvokeRepeating("dirc", time, time);
        InvokeRepeating("DIR", time, time);
    }
    void DIR()
    {

        this.transform.DOMove(new Vector2(DatabaseManager.X, DatabaseManager.Y), time).SetEase(Ease.Linear);
    }
    void dirc()
    {
        dir = DatabaseManager.dir;
        switch (dir)
        {
            case "E": // 오른쪽
                this.transform.DOMove(new Vector2(transform.position.x + distance, transform.position.y), time);
                break;
            case "W":
                this.transform.DOMove(new Vector2(transform.position.x - distance, transform.position.y), time);
                break;
            case "N":
                this.transform.DOMove(new Vector2(transform.position.x, transform.position.y + distance), time);
                break;
            case "S":
                this.transform.DOMove(new Vector2(transform.position.x, transform.position.y - distance), time);
                break;
            case "NE":
                this.transform.DOMove(new Vector2(transform.position.x + distance, transform.position.y + distance), time);
                break;
            case "SW":
                this.transform.DOMove(new Vector2(transform.position.x - distance, transform.position.y - distance), time);
                break;
            case "SE":
                this.transform.DOMove(new Vector2(transform.position.x + distance, transform.position.y - distance), time);
                break;
            case "NW":
                this.transform.DOMove(new Vector2(transform.position.x - distance, transform.position.y + distance), time);
                break;
        }
    }
    // Update is called once per frame
    void Update()
    {




        //this.transform.position = new Vector2(DatabaseManager.X, DatabaseManager.Y);
    }
}

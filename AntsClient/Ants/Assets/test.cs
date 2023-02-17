using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DG.Tweening;
public class test : MonoBehaviour
{
    [SerializeField] float time;
    [SerializeField] float distance;

    // Start is called before the first frame update
    void Start()
    {

    }

    void DIR()
    {
        if (DatabaseManager.changeDir == 0)
        {
            this.transform.DOMove(new Vector2(transform.position.x, transform.position.y + distance), time).SetEase(Ease.Linear);
        }
        else if (DatabaseManager.changeDir == 1)
        {
            this.transform.DOMove(new Vector2(transform.position.x, transform.position.y - distance), time).SetEase(Ease.Linear);
        }
        else if (DatabaseManager.changeDir == 2)
        {
            this.transform.DOMove(new Vector2(transform.position.x + distance, transform.position.y), time).SetEase(Ease.Linear);
        }
        else if (DatabaseManager.changeDir == 3)
        {
            this.transform.DOMove(new Vector2(transform.position.x - distance, transform.position.y), time).SetEase(Ease.Linear);
        }
        else if (DatabaseManager.changeDir == 4)
        {
            this.transform.DOMove(new Vector2(transform.position.x - distance, transform.position.y + distance), time).SetEase(Ease.Linear);
        }
        else if (DatabaseManager.changeDir == 5)
        {
            this.transform.DOMove(new Vector2(transform.position.x + distance, transform.position.y + distance), time).SetEase(Ease.Linear);
        }
        else if (DatabaseManager.changeDir == 6)
        {
            this.transform.DOMove(new Vector2(transform.position.x - distance, transform.position.y - distance), time).SetEase(Ease.Linear);
        }
        else if (DatabaseManager.changeDir == 7)
        {
            this.transform.DOMove(new Vector2(transform.position.x + distance, transform.position.y - distance), time).SetEase(Ease.Linear);
        }
        else if (DatabaseManager.changeDir == 8)
        {
            transform.DOPause();
            this.transform.DOMove(new Vector2(DatabaseManager.X, DatabaseManager.Y), time).SetEase(Ease.Linear);
        }
    }


    // Update is called once per frame
    void Update()
    {
        //DIR();
    }
}

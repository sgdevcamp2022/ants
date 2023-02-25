using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
namespace MoreMountains.CorgiEngine
{
    public class Stemina : MonoBehaviour
    {
        public Image stemniabar;

        // Start is called before the first frame update
        void Start()
        {
            DatabaseManager.nowStemina = 1000;
            DatabaseManager.fullStemina = 1000;
            recoveryAmount = 50;
        }

        // Update is called once per frame

        public float recoveryAmount = 50;
        bool oneTime = false;
        void restCheck()
        {
            if (DatabaseManager.isAction == true && oneTime == false)
            {
                oneTime = true;
                DatabaseManager.isRestOneSec = false;
                StartCoroutine(oneSecChecker());
            }
        }

        IEnumerator oneSecChecker()
        {
            yield return new WaitForSecondsRealtime(1f);
            DatabaseManager.isRestOneSec = true;
            oneTime = false;
        }
        void Update()
        {
            restCheck();
            if (DatabaseManager.nowStemina < DatabaseManager.fullStemina)
            {
                if (DatabaseManager.isAction == false)
                {
                    if (DatabaseManager.isRestOneSec == false)
                    {
                        DatabaseManager.nowStemina = DatabaseManager.nowStemina + Time.deltaTime * recoveryAmount;
                    }
                    else if (DatabaseManager.isRestOneSec == true)
                    {
                        DatabaseManager.nowStemina = DatabaseManager.nowStemina + Time.deltaTime * recoveryAmount * 4;
                    }
                }
            }
            stemniabar.fillAmount = DatabaseManager.nowStemina / DatabaseManager.fullStemina;
        }
    }
}

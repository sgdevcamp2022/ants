using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;
public class SkillCoolTimeUI : MonoBehaviour
{
    // Q  스킬 관련 변수
    bool QisCoolTime = false;
    float Qcooldown = 3f;
    float QdelayTime = 30;
    public Image QSkill;

    //E스킬 관련 변수
    bool EisCoolTime = false;
    float Ecooldown = 5f;
    float EdelayTime = 50;
    public Image ESkill;

    void Start()
    {

    }


    // Update is called once per frame
    void Update()
    {
        if (QisCoolTime == true)
        {
            QSkill.fillAmount += 1 / Qcooldown * Time.deltaTime;
        }

        if (Input.GetKeyDown(KeyCode.Q))
        {
            if (QisCoolTime == false)
            {
                QSkill.fillAmount = 0;
                QisCoolTime = true;
                StartCoroutine(QCoolTime());
            }
        }

        if (EisCoolTime == true)
        {
            ESkill.fillAmount += 1 / Ecooldown * Time.deltaTime;
        }

        if (Input.GetKeyDown(KeyCode.E))
        {
            if (EisCoolTime == false)
            {
                ESkill.fillAmount = 0;
                EisCoolTime = true;
                StartCoroutine(ECoolTime());
            }
        }

    }

    IEnumerator QCoolTime()
    {
        yield return new WaitForSeconds(3f);
        QisCoolTime = false;
    }


    IEnumerator ECoolTime()
    {
        yield return new WaitForSeconds(5f);
        EisCoolTime = false;
    }
}


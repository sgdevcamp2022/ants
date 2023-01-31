using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;
public class SkillCoolTimeUI : MonoBehaviour
{
    bool isCoolTime = false;
    float cooldown = 3f;
    float delayTime = 30;
    public Image image;
    //public GameObject skillATT;

    // Start is called before the first frame update
    void Start()
    {

    }
    IEnumerator Wait()
    {
        image.fillAmount = 0;
        while (delayTime > 0)
        {
            image.fillAmount += (0.033333333333333333333333333f);
            delayTime -= 1;
            yield return new WaitForSeconds(0.01f);
        }
        delayTime = 30;
    }

    // Update is called once per frame
    void Update()
    {
        if (isCoolTime == true)
        {
            image.fillAmount += 1 / cooldown * Time.deltaTime;
        }

        if (Input.GetKeyDown(KeyCode.Q))
        {
            if (isCoolTime == false)
            {
                image.fillAmount = 0;
                isCoolTime = true;
                StartCoroutine(CoolTime());
            }
        }



    }


    IEnumerator CoolTime()
    {
        yield return new WaitForSeconds(3f);

        isCoolTime = false;
    }
}


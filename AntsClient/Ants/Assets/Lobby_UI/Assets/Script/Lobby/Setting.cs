using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;


public class Setting : MonoBehaviour
{
    public Text nickname;
    public TextMeshProUGUI level;
    public Slider exp;
    public Text cash;
    private void Start()
    {
        
        nickname.text = DatabaseManager.nickname;
        level.text = $"LV.{DatabaseManager.level}";
        exp.value = (DatabaseManager.exp)/100;
        cash.text = $"{DatabaseManager.cash}";
    }

    
}

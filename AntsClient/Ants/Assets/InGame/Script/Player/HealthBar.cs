using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
namespace MoreMountains.CorgiEngine
{
    public class HealthBar : MonoBehaviour
    {
        public Image healthBar;
        public Health health;

        public float fullHealth;
        public float nowHealth;

        private void Start()
        {
            fullHealth = health.HP;
        }
        void Update()
        {
            nowHealth = health.HP;
            healthBar.fillAmount = nowHealth / fullHealth;

        }
    }
}

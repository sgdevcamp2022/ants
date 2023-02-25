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
        bool once;
        private void Awake()
        {
            once = true;
        }
        private void Start()
        {
            

        }
        void Update()
        {
            if(health != null)
            {
                if (once)
                {
                    once = false;
                    fullHealth = health.HP;
                }

                nowHealth = health.HP;
                healthBar.fillAmount = nowHealth / fullHealth;
            }
            else
            {
                health = GameObject.FindWithTag("Player").GetComponent<Health>();
            }


        }
    }
}

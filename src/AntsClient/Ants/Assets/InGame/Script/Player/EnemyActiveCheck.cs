using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Pathfinding;
using Pathfinding.RVO;
public class EnemyActiveCheck : MonoBehaviour
{

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.tag == "Enemy")
        {

            SpriteRenderer spriteRenderer = collision.GetComponent<SpriteRenderer>();
            Animator animator = collision.GetComponent<Animator>();
            Health health = collision.GetComponent<Health>();
            RVOController rVOController = collision.GetComponent<RVOController>();
            SimpleSmoothModifier smoothModifier = collision.GetComponent<SimpleSmoothModifier>();
            AIDestinationSetter aIDestinationSetter = collision.GetComponent<AIDestinationSetter>();
            EnemyAttack enemyAttack = collision.GetComponent<EnemyAttack>();
            Brain brain = collision.GetComponent<Brain>();
            AIPath aIPath = collision.GetComponent<AIPath>();

            spriteRenderer.enabled = true;
            animator.enabled = true;
            health.enabled = true;
            rVOController.enabled = true;
            smoothModifier.enabled = true;
            aIDestinationSetter.enabled = true;
            enemyAttack.enabled = true;
            brain.enabled = true;
            aIPath.enabled = true;

        }
    }
    private void OnTriggerExit2D(Collider2D collision)
    {
        if(collision.tag == "Enemy")
        {

            SpriteRenderer spriteRenderer = collision.GetComponent<SpriteRenderer>();
            Animator animator = collision.GetComponent<Animator>();
            Health health = collision.GetComponent<Health>();
            RVOController rVOController = collision.GetComponent<RVOController>();
            SimpleSmoothModifier smoothModifier = collision.GetComponent<SimpleSmoothModifier>();
            AIDestinationSetter aIDestinationSetter = collision.GetComponent<AIDestinationSetter>();
            EnemyAttack enemyAttack = collision.GetComponent<EnemyAttack>();
            Brain brain = collision.GetComponent<Brain>();
            AIPath aIPath = collision.GetComponent<AIPath>();

            spriteRenderer.enabled = false;
            animator.enabled = false;
            health.enabled = false;
            rVOController.enabled = false;
            smoothModifier.enabled = false;
            aIDestinationSetter.enabled = false;
            enemyAttack.enabled = false;
            brain.enabled = false;
            aIPath.enabled = false;

        }
    }
}

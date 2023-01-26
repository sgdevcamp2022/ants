using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerManager : MonoBehaviour
{
    [SerializeField] private float walkSpeed;
    [SerializeField] private float runSpeed;

    private Animator animator;

    // 플레이어의 현재 상태를 나타내는 변수, Stay, walk, Move로 나누어진다.

    float xInput;
    float yInput;

    public float angle;
    public GameObject target;
    Vector2 mouse;
    private void Start()
    {
        animator = GetComponent<Animator>();

    }
    private void Awake()
    {
        DatabaseManager.playerState = "Stay";
    }


    void Update()
    {
        xInput = Input.GetAxisRaw("Horizontal");
        yInput = Input.GetAxisRaw("Vertical");

        PlayerMovement();
        PlayerState();
        PlayerAnimator();


        //스테미나가 음수가 되지 않도록 제한함.
        if(DatabaseManager.nowStemina < 0)
        {
            DatabaseManager.nowStemina = 0;
        }
    }
    void PlayerAnimator()
    {
        mouse = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        angle = Mathf.Atan2(mouse.y - target.transform.position.y, mouse.x - target.transform.position.x) * Mathf.Rad2Deg;

        if(angle > -45 && angle < 45)
        {
            animator.SetFloat("Angle", 0.7f);
        }
        else if(angle >= 45 && angle < 135)
        {
            animator.SetFloat("Angle", 1f);
        }
        else if (angle >= -135 && angle <= -45)
        {
            animator.SetFloat("Angle", 0f);
        }
        else
        {
            animator.SetFloat("Angle", 0.4f);
        }

        if (DatabaseManager.playerState == "Stay")
        {
            animator.SetBool("isWalk", false);
        }
        else
        {
            animator.SetBool("isWalk", true);
        }
    }
    void PlayerState()
    {

        if(DatabaseManager.nowStemina == 0 && DatabaseManager.playerState == "Run")
        {
            DatabaseManager.playerState = "Walk";
        }

        if (Input.GetKeyDown(KeyCode.LeftShift) && DatabaseManager.nowStemina > 0)
        {
            if (DatabaseManager.playerState != "Run")
            {
                DatabaseManager.playerState = "Run";
            }
            else
            {
                if (Mathf.Abs(xInput) > 0 || Mathf.Abs(yInput) > 0)
                {
                    DatabaseManager.playerState = "Walk";
                }
                else
                {
                    DatabaseManager.playerState = "Stay";
                }
            }
        }

        if (DatabaseManager.playerState != "Run")
        {
            if (Mathf.Abs(xInput) > 0 || Mathf.Abs(yInput) > 0)
            {
                DatabaseManager.playerState = "Walk";
            }
            else
            {
                DatabaseManager.playerState = "Stay";
            }
        }
        else
        {
            if (Mathf.Abs(xInput) > 0 || Mathf.Abs(yInput) > 0)
            {
                DatabaseManager.playerState = "Run";
            }
            else
            {
                DatabaseManager.playerState = "Stay";
            }
        }
    }
    void PlayerMovement()
    {
        if(DatabaseManager.playerState == "Run")
        {
            DatabaseManager.isAction = true;
            transform.Translate(new Vector2(xInput, yInput) * Time.deltaTime * runSpeed);
            if(DatabaseManager.nowStemina > 0)
            {
                DatabaseManager.nowStemina -= 1f;
            }
        }
        else
        {
            DatabaseManager.isAction = false;
            transform.Translate(new Vector2(xInput, yInput) * Time.deltaTime * walkSpeed);
        }
    }
}

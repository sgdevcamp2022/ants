using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlusSlot : MonoBehaviour
{
    public GameObject slot;
    public Transform parentContent;

    public void PlusSlotClick()
    {
        GameObject plusSlot = Instantiate(slot, parentContent);
    }
}

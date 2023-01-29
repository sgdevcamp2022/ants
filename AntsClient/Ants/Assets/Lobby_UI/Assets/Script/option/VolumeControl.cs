using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class VolumeControl : MonoBehaviour
{
    public AudioSource audioVolume;
    public float volume = 1f;
    public Slider slider;

    private void Start()
    {
        audioVolume = GetComponent<AudioSource>();
    }
    private void Update()
    {
        audioVolume.volume = volume;
    }
    public void setVolume()
    {
        volume = slider.value;
    }
}

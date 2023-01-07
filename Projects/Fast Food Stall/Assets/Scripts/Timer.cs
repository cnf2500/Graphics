/*
* Chris Forte
* 12/06/2022
* COMPSCI 657
* "Timer.cs" File
*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.EventSystems;

public class Timer : MonoBehaviour
{
    public TextMeshProUGUI time_txt;
    public TextMeshProUGUI msg_txt;

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.D))
        {
            StopAllCoroutines(); 
            msg_txt.color = Color.green;
            StartCoroutine(TimeStatus("Start!"));
            StartCoroutine(TimeDisplay());
        }

        if (Input.GetKeyDown(KeyCode.U))
        {
            StopAllCoroutines();
            msg_txt.color = Color.red;
            StartCoroutine(TimeStatus("Done!"));
        }
    }

    IEnumerator TimeDisplay() 
    {
        float elapsed = 0.0f;
        time_txt.text = "0:00";
       
        while (!Input.GetKeyDown(KeyCode.U))
        {
            elapsed += Time.deltaTime;
            time_txt.text = elapsed.ToString("00:00");
            yield return null;
        }
    }

    IEnumerator TimeStatus(string state)
    {
        msg_txt.text = state;
        float elapsed = 0.0f;
        
        while (elapsed <= 2.0f)
        {
            elapsed += Time.deltaTime;
            yield return null;
        }
        
        float fade = Time.time;
        float duration = 2f;
        float complete = 0f;
        
        while (complete < 1f)
        {
            complete = (Time.time - fade) / duration;
            msg_txt.alpha = Mathf.Lerp(1f, 0f, complete);
            yield return null;
        }
        
        msg_txt.text = "";
        msg_txt.alpha = 1f;
    }
}

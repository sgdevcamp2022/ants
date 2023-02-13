using UnityEngine;
using TMPro;


public class OpenChat : MonoBehaviour
{
    public TextMeshProUGUI listName;
    public TextMeshProUGUI chatPanelName;
    public GameObject chatPanel;
   // public Transform parent;
   // public GameObject scrollPrefab;


    public void OpenPanel()
    {
        chatPanelName.text = listName.text;
       //scrollview의 content초기화해서 나오는 방법?
       // GameObject clone = Instantiate(scrollPrefab,parent);
        chatPanel.SetActive(true);
    }
}

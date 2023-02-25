using System.Collections;
using System.Collections.Generic;
using UnityEngine;


[System.Serializable]
public abstract class Node
{
    protected NodeState _nodeState;
    public bool IsWaiting = false;
    public NodeState nodeState { get { return _nodeState; } set { _nodeState = value; } }
    public abstract NodeState Evaluate();

}

public enum NodeState
{
    RUNNING, SUCCESS, FAILURE, WAIT,
}
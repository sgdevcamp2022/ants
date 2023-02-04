using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sequence : Node
{
    protected List<Node> nodes = new List<Node>();

    public enum NODETYPE
    {
        SETDIR, WAIT, FINDMOVE1, FINDMOVE2, MOVE,
    }
    public Sequence(List<Node> nodes)
    {
        this.nodes = nodes;
    }

    public override NodeState Evaluate()
    {
        bool isAnyNodeRunning = false;
        foreach(var node in nodes)
        {
            switch (node.Evaluate())
            {
                case NodeState.RUNNING:
                    isAnyNodeRunning = true;
                    break;
                case NodeState.SUCCESS:
                    break;
                case NodeState.FAILURE:
                    _nodeState = NodeState.FAILURE;
                    return _nodeState;
                default:
                    break;
            }
        }
        _nodeState = isAnyNodeRunning ? NodeState.RUNNING : NodeState.SUCCESS;
        return _nodeState;
    }

    public Node GetNode(NODETYPE nodeType)
    {
        switch (nodeType)
        {
            case NODETYPE.WAIT:
                return nodes[2];
            default:
                return nodes[2];
        }
    }

}

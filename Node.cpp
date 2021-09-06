#include "Node.h"

Node::Node(QString title, NodeType type, NodeWidget *widget, Node* parent) :
    m_parent(parent), m_title(title), m_widget(widget), m_type(type)
{
    m_children = 0;
    if(parent != nullptr)
    {
        parent->m_children++;
        if(parent->m_children == 1)
            parent->setLeftChild(this);
        else
            parent->setRightChild(this);
    }
}

Node *Node::getLeftChild()
{
    return m_left_child;
}

Node *Node::getRightChild()
{
    return m_right_child;
}

Node *Node::getParent()
{
    return m_parent;
}

int Node::childCount()
{
    return m_children;
}

NodeWidget *Node::getWidget()
{
    return m_widget;
}

NodeType Node::getType()
{
    return m_type;
}

void Node::setValue(QString value)
{
    m_value = value;
}

void Node::setLeftChild(Node *node)
{
    m_left_child = node;
}

void Node::setRightChild(Node *node)
{
    m_right_child = node;
}

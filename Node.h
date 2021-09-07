#ifndef NODE_H
#define NODE_H

#include <QObject>
#include "NodeWidget.h"

class Node : public QObject
{

Q_OBJECT
public:
    enum NodeOrientation
    {
        LEFT = 0,
        RIGHT
    };
    Node(QString title, NodeType type, NodeWidget* widget, Node* parent = nullptr);
    Node* getLeftChild();
    Node* getRightChild();
    Node* getParent();
    int childCount();
    NodeWidget* getWidget();
    NodeType getType();
    int m_children;
    NodeOrientation m_orientation;

signals:
    void emitAddChild(Node*, NodeType, QString);

public slots:
    void setValue(QString value);
    void addChild();

protected:
    void setLeftChild(Node* node);
    void setRightChild(Node* node);

private:
    Node* m_parent;
    QString m_title;
    QString m_value;
    Node* m_left_child;
    Node* m_right_child;
    NodeWidget* m_widget;
    NodeType m_type;
};

#endif // NODE_H

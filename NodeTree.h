#ifndef NODETREE_H
#define NODETREE_H

#include <QMainWindow>
#include "NodeWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NodeTree; }
QT_END_NAMESPACE

class Node;

class NodeTree : public QMainWindow
{
    Q_OBJECT

public:
    NodeTree(QWidget *parent = nullptr);
    ~NodeTree();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    Node* createNode(Node *parent_node, NodeType type, QString title);

private:
    Ui::NodeTree *ui;
    QVector<Node*> m_nodes;
    void placeNode(Node *node);
};
#endif // NODETREE_H

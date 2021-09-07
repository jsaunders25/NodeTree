#include "NodeTree.h"
#include "ui_NodeTree.h"
#include "Node.h"
#include <QPainter>

#define NODE_SPACING 20

NodeTree::NodeTree(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NodeTree)
{
    ui->setupUi(this);
    setWindowTitle("Node Tree");
    resize(1800, 1200);
    Node* base_node = createNode(nullptr, FLOAT, "Base");
    Node* child_1 = createNode(base_node, STRING, "Child 1");
    Node* child_2 = createNode(base_node, STRING, "Child 2");
    Node* grandchild_1 = createNode(child_1, STRING, "Grandchild 1");
    Node* grandchild_2 = createNode(child_2, STRING, "Grandchild 2");
    Node* grandchild_3 = createNode(child_2, FLOAT, "Grandchild 3");
    Node* third_gen_1 = createNode(grandchild_1, FLOAT, "Third Gen 1");
    Node* third_gen_2 = createNode(grandchild_2, STRING, "Third Gen 2");
    Node* third_gen_3 = createNode(grandchild_2, FLOAT, "Third Gen 3");
    Node* fourth_gen_1 = createNode(third_gen_1, FLOAT, "Fourth Gen 1");
}

NodeTree::~NodeTree()
{
    delete ui;
}

void NodeTree::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QColor color(202, 103, 9); // color values from example image
    QPen pen(color);
    QBrush brush(color);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.setBrush(brush);

    // draw lines connecting the nodes
    for(auto node : m_nodes)
    {
        if(node->getParent() != nullptr)
        {
            if(node->getParent()->getType() == STRING || node->getParent()->getType() == FLOAT)
            {
                auto node_widget = node->getWidget();
                QPoint center_of_node = QPoint(node_widget->x() + (node_widget->width() / 2), node_widget->y() + (node_widget->height() / 2));
                auto parent_widget = node->getParent()->getWidget();
                QPoint center_of_parent = QPoint(parent_widget->x() + (parent_widget->width() / 2), parent_widget->y() + (parent_widget->height() / 2));
                painter.drawLine(center_of_node, center_of_parent);
            }
        }
    }
}

Node *NodeTree::createNode(Node *parent_node, NodeType type, QString title)
{
    NodeWidget* widget = new NodeWidget(type, title, this);
    Node* node = new Node(title, type, widget, parent_node);

    if(parent_node == nullptr)
    {
        // place base node near top center of the window
        widget->move(width() / 2 - NODE_SIZE / 2, 10);
        widget->show();
    }
    else if(parent_node->childCount() <= 2)
    {
        placeNode(node);
    }
    else
    {
        delete widget;
        delete node;
        return nullptr;
    }
    // Connect Widget Input with Node Data Structure
    connect(widget, &NodeWidget::emitValueChanged, node, &Node::setValue);
    connect(widget, &NodeWidget::emitAddNode, node, &Node::addChild);
    connect(node, &Node::emitAddChild, this, &NodeTree::createNode);
    m_nodes << node;
    update();   // to trigger paint event
    return node;
}

void NodeTree::placeNode(Node *node)
{
    Node *parent_node = node->getParent();
    NodeWidget *widget = node->getWidget();

    // place node appropriately below parent
    if(parent_node->childCount() == 1)
    {
        node->m_orientation = Node::LEFT;
        widget->move(parent_node->getWidget()->x() - (NODE_SIZE / 2) - NODE_SPACING, parent_node->getWidget()->y() + NODE_SIZE + NODE_SPACING);
        widget->show();
    }
    else
    {
        node->m_orientation = Node::RIGHT;
        widget->move(parent_node->getWidget()->x() + (NODE_SIZE / 2) + NODE_SPACING, parent_node->getWidget()->y() + NODE_SIZE + NODE_SPACING);
        widget->show();
    }
}


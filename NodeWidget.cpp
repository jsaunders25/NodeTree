#include "NodeWidget.h"
#include "ui_NodeWidget.h"
#include "FloatSlider.h"
#include <QLineEdit>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

NodeWidget::NodeWidget(NodeType type, QString title, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NodeWidget)
{
    ui->setupUi(this);
    ui->label_title->setText(title);

    resize(NODE_SIZE, NODE_SIZE);

    // create appropriate input fields
    if(type == STRING)
    {
        QLineEdit *line_edit = new QLineEdit("New Node", this);
        connect(line_edit, &QLineEdit::textChanged, this, &NodeWidget::valueChanged);
        ui->valueLayout->addWidget(line_edit);
     }
    else
    {
        FloatSlider *slider = new FloatSlider(this);
        connect(slider, &FloatSlider::emitValueChanged, this, &NodeWidget::valueChanged);
        ui->valueLayout->addWidget(slider);
    }
}

NodeWidget::~NodeWidget()
{
    delete ui;
}

void NodeWidget::valueChanged(QString value)
{
    emit emitValueChanged(value);
}

void NodeWidget::addNode()
{
    emit emitAddNode();
}

void NodeWidget::paintEvent(QPaintEvent *)
 {  // This allows this widget to be used in the stylesheet
     QStyleOption opt;
     opt.initFrom(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 }

void NodeWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        QMenu menu;
        QAction createNode("Add Node", this);
        connect(&createNode, &QAction::triggered, this, &NodeWidget::addNode);
        menu.addAction(&createNode);
        menu.exec(event->globalPosition().toPoint(), &createNode);
    }
}

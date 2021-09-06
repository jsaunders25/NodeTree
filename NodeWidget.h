#ifndef NODEWIDGET_H
#define NODEWIDGET_H

#include <QWidget>

#define NODE_SIZE 150 // width and height of nodes

namespace Ui {
class NodeWidget;
}

enum NodeType
{
    STRING = 0,
    FLOAT,
    TOTAL
};

class NodeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NodeWidget(NodeType type, QString title, QWidget *parent = nullptr);
    ~NodeWidget();

signals:
    void emitValueChanged(QString);

protected:
    void paintEvent(QPaintEvent *);
private slots:
    void valueChanged(QString value);

private:
    Ui::NodeWidget *ui;
};

#endif // NODEWIDGET_H

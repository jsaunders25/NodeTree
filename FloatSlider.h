#ifndef FLOATSLIDER_H
#define FLOATSLIDER_H

#include <QWidget>

namespace Ui {
class FloatSlider;
}

class FloatSlider : public QWidget
{
    Q_OBJECT

public:
    explicit FloatSlider(QWidget *parent = nullptr);
    ~FloatSlider();

signals:
    void emitValueChanged(QString);

private slots:
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::FloatSlider *ui;
};

#endif // FLOATSLIDER_H

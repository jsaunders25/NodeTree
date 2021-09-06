#include "FloatSlider.h"
#include "ui_FloatSlider.h"

FloatSlider::FloatSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FloatSlider)
{
    ui->setupUi(this);
    ui->horizontalSlider->setRange(0, 10000);
}

FloatSlider::~FloatSlider()
{
    delete ui;
}

void FloatSlider::on_horizontalSlider_valueChanged(int value)
{
    float new_value = static_cast<float>(value) / 100;
    ui->lineEdit->setText(QString::number(new_value));
    emit emitValueChanged(ui->lineEdit->text());
}


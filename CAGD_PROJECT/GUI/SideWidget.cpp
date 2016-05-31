#include "SideWidget.h"
#include <QDebug>

SideWidget::SideWidget(QWidget *parent):
        QWidget(parent)
{
    setupUi(this);
}

void SideWidget::set_combo(bool value)
{
    if(value)
    {
        x_point->setEnabled(true);
        y_point->setEnabled(true);
        x_point->setCurrentIndex(0);
        y_point->setCurrentIndex(3);
    }
    else
    {
        x_point->setEnabled(false);
        y_point->setEnabled(false);
        x_point->setCurrentIndex(0);
        y_point->setCurrentIndex(0);
    }
    qDebug() << "katt";
}

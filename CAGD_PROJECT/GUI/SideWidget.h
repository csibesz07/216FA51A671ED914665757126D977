#pragma once

#include <QWidget>
#include "ui_SideWidget.h"

class SideWidget: public QWidget, public Ui::SideWidget
{
    Q_OBJECT
public:
    // special and default constructor
    SideWidget(QWidget *parent = 0);

public slots:
    void set_combo(bool value);
};

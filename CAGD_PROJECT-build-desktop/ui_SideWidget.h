/********************************************************************************
** Form generated from reading UI file 'SideWidget.ui'
**
** Created: Mon May 30 20:03:30 2016
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEWIDGET_H
#define UI_SIDEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SideWidget
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSlider *rotate_x_slider;
    QLabel *label_2;
    QSlider *rotate_y_slider;
    QLabel *label_3;
    QSlider *rotate_z_slider;
    QLabel *label_4;
    QDoubleSpinBox *zoom_factor_spin_box;
    QLabel *label_5;
    QDoubleSpinBox *trans_x_spin_box;
    QLabel *label_6;
    QDoubleSpinBox *trans_y_spin_box;
    QLabel *label_7;
    QDoubleSpinBox *trans_z_spin_box;
    QLabel *label_8;
    QComboBox *x_point;
    QLabel *label_9;
    QComboBox *y_point;
    QLabel *label_10;
    QSlider *change_x_slider;
    QLabel *label_11;
    QSlider *change_y_slider;
    QLabel *label_12;
    QSlider *change_z_slider;
    QLabel *label_13;
    QPushButton *select_for_join;
    QLabel *label_15;
    QLabel *label_14;
    QComboBox *first_patch_side;
    QComboBox *second_patch_side;
    QPushButton *join;
    QCheckBox *shader_check_box;

    void setupUi(QWidget *SideWidget)
    {
        if (SideWidget->objectName().isEmpty())
            SideWidget->setObjectName(QString::fromUtf8("SideWidget"));
        SideWidget->resize(289, 483);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SideWidget->sizePolicy().hasHeightForWidth());
        SideWidget->setSizePolicy(sizePolicy);
        SideWidget->setMinimumSize(QSize(269, 0));
        groupBox = new QGroupBox(SideWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 271, 451));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(3, 21, 261, 421));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        rotate_x_slider = new QSlider(layoutWidget);
        rotate_x_slider->setObjectName(QString::fromUtf8("rotate_x_slider"));
        rotate_x_slider->setMinimum(-180);
        rotate_x_slider->setMaximum(180);
        rotate_x_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, rotate_x_slider);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        rotate_y_slider = new QSlider(layoutWidget);
        rotate_y_slider->setObjectName(QString::fromUtf8("rotate_y_slider"));
        rotate_y_slider->setMinimum(-180);
        rotate_y_slider->setMaximum(180);
        rotate_y_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, rotate_y_slider);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        rotate_z_slider = new QSlider(layoutWidget);
        rotate_z_slider->setObjectName(QString::fromUtf8("rotate_z_slider"));
        rotate_z_slider->setMinimum(-180);
        rotate_z_slider->setMaximum(180);
        rotate_z_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(2, QFormLayout::FieldRole, rotate_z_slider);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        zoom_factor_spin_box = new QDoubleSpinBox(layoutWidget);
        zoom_factor_spin_box->setObjectName(QString::fromUtf8("zoom_factor_spin_box"));
        zoom_factor_spin_box->setDecimals(5);
        zoom_factor_spin_box->setMinimum(0.0001);
        zoom_factor_spin_box->setMaximum(10000);
        zoom_factor_spin_box->setSingleStep(0.1);
        zoom_factor_spin_box->setValue(1);

        formLayout->setWidget(3, QFormLayout::FieldRole, zoom_factor_spin_box);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        trans_x_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_x_spin_box->setObjectName(QString::fromUtf8("trans_x_spin_box"));
        trans_x_spin_box->setMinimum(-100);
        trans_x_spin_box->setMaximum(100);
        trans_x_spin_box->setSingleStep(0.1);

        formLayout->setWidget(4, QFormLayout::FieldRole, trans_x_spin_box);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        trans_y_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_y_spin_box->setObjectName(QString::fromUtf8("trans_y_spin_box"));
        trans_y_spin_box->setMinimum(-100);
        trans_y_spin_box->setMaximum(100);
        trans_y_spin_box->setSingleStep(0.1);

        formLayout->setWidget(5, QFormLayout::FieldRole, trans_y_spin_box);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        trans_z_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_z_spin_box->setObjectName(QString::fromUtf8("trans_z_spin_box"));
        trans_z_spin_box->setMinimum(-100);
        trans_z_spin_box->setMaximum(100);
        trans_z_spin_box->setSingleStep(0.1);

        formLayout->setWidget(6, QFormLayout::FieldRole, trans_z_spin_box);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_8);

        x_point = new QComboBox(layoutWidget);
        x_point->setObjectName(QString::fromUtf8("x_point"));
        x_point->setMaxCount(4);

        formLayout->setWidget(7, QFormLayout::FieldRole, x_point);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_9);

        y_point = new QComboBox(layoutWidget);
        y_point->setObjectName(QString::fromUtf8("y_point"));
        y_point->setMaxCount(4);

        formLayout->setWidget(8, QFormLayout::FieldRole, y_point);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_10);

        change_x_slider = new QSlider(layoutWidget);
        change_x_slider->setObjectName(QString::fromUtf8("change_x_slider"));
        change_x_slider->setMinimum(-100);
        change_x_slider->setMaximum(100);
        change_x_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(9, QFormLayout::FieldRole, change_x_slider);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout->setWidget(10, QFormLayout::LabelRole, label_11);

        change_y_slider = new QSlider(layoutWidget);
        change_y_slider->setObjectName(QString::fromUtf8("change_y_slider"));
        change_y_slider->setMinimum(-100);
        change_y_slider->setMaximum(100);
        change_y_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(10, QFormLayout::FieldRole, change_y_slider);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        formLayout->setWidget(11, QFormLayout::LabelRole, label_12);

        change_z_slider = new QSlider(layoutWidget);
        change_z_slider->setObjectName(QString::fromUtf8("change_z_slider"));
        change_z_slider->setMinimum(-100);
        change_z_slider->setMaximum(100);
        change_z_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(11, QFormLayout::FieldRole, change_z_slider);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        formLayout->setWidget(12, QFormLayout::LabelRole, label_13);

        select_for_join = new QPushButton(layoutWidget);
        select_for_join->setObjectName(QString::fromUtf8("select_for_join"));

        formLayout->setWidget(13, QFormLayout::FieldRole, select_for_join);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        formLayout->setWidget(14, QFormLayout::LabelRole, label_15);

        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        formLayout->setWidget(15, QFormLayout::LabelRole, label_14);

        first_patch_side = new QComboBox(layoutWidget);
        first_patch_side->setObjectName(QString::fromUtf8("first_patch_side"));

        formLayout->setWidget(14, QFormLayout::FieldRole, first_patch_side);

        second_patch_side = new QComboBox(layoutWidget);
        second_patch_side->setObjectName(QString::fromUtf8("second_patch_side"));

        formLayout->setWidget(15, QFormLayout::FieldRole, second_patch_side);

        join = new QPushButton(layoutWidget);
        join->setObjectName(QString::fromUtf8("join"));

        formLayout->setWidget(16, QFormLayout::FieldRole, join);

        shader_check_box = new QCheckBox(SideWidget);
        shader_check_box->setObjectName(QString::fromUtf8("shader_check_box"));
        shader_check_box->setGeometry(QRect(10, 450, 271, 18));
        shader_check_box->setChecked(true);
#ifndef QT_NO_SHORTCUT
        label->setBuddy(rotate_x_slider);
        label_2->setBuddy(rotate_y_slider);
        label_3->setBuddy(rotate_z_slider);
        label_4->setBuddy(zoom_factor_spin_box);
        label_5->setBuddy(trans_x_spin_box);
        label_6->setBuddy(trans_y_spin_box);
        label_7->setBuddy(trans_z_spin_box);
#endif // QT_NO_SHORTCUT

        retranslateUi(SideWidget);

        x_point->setCurrentIndex(0);
        first_patch_side->setCurrentIndex(0);
        second_patch_side->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SideWidget);
    } // setupUi

    void retranslateUi(QWidget *SideWidget)
    {
        SideWidget->setWindowTitle(QApplication::translate("SideWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SideWidget", "Transformations", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SideWidget", "Rotate around x", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SideWidget", "Rotate around y", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SideWidget", "Rotate around z", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SideWidget", "Zoom factor", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SideWidget", "Translate along x", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SideWidget", "Translate along y", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("SideWidget", "Translate along z", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("SideWidget", "Select point X", 0, QApplication::UnicodeUTF8));
        x_point->clear();
        x_point->insertItems(0, QStringList()
         << QApplication::translate("SideWidget", "0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "3", 0, QApplication::UnicodeUTF8)
        );
        label_9->setText(QApplication::translate("SideWidget", "Select point Y", 0, QApplication::UnicodeUTF8));
        y_point->clear();
        y_point->insertItems(0, QStringList()
         << QApplication::translate("SideWidget", "0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "3", 0, QApplication::UnicodeUTF8)
        );
        label_10->setText(QApplication::translate("SideWidget", "Change point X", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("SideWidget", "Change point Y", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("SideWidget", "Change point Z", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("SideWidget", "Join two patches", 0, QApplication::UnicodeUTF8));
        select_for_join->setText(QApplication::translate("SideWidget", "Select second patch for join", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("SideWidget", "First patch joining side", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("SideWidget", "First patch joining side", 0, QApplication::UnicodeUTF8));
        first_patch_side->clear();
        first_patch_side->insertItems(0, QStringList()
         << QApplication::translate("SideWidget", "NW", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "N", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "NE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "E", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "SE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "S", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "SW", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "W", 0, QApplication::UnicodeUTF8)
        );
        second_patch_side->clear();
        second_patch_side->insertItems(0, QStringList()
         << QApplication::translate("SideWidget", "NW", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "N", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "NE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "E", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "SE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "S", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "SW", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SideWidget", "W", 0, QApplication::UnicodeUTF8)
        );
        join->setText(QApplication::translate("SideWidget", "Join selected patches", 0, QApplication::UnicodeUTF8));
        shader_check_box->setText(QApplication::translate("SideWidget", "Apply shader", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SideWidget: public Ui_SideWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEWIDGET_H

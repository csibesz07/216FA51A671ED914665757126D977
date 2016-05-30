#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setupUi(this);

/*

  the structure of the main window's central widget

 *---------------------------------------------------*
 |                 central widget                    |
 |                                                   |
 |  *---------------------------*-----------------*  |
 |  |     rendering context     |   scroll area   |  |
 |  |       OpenGL widget       | *-------------* |  |
 |  |                           | | side widget | |  |
 |  |                           | |             | |  |
 |  |                           | |             | |  |
 |  |                           | *-------------* |  |
 |  *---------------------------*-----------------*  |
 |                                                   |
 *---------------------------------------------------*

*/
    _side_widget = new SideWidget(this);

    _scroll_area = new QScrollArea(this);
    _scroll_area->setWidget(_side_widget);
    _scroll_area->setSizePolicy(_side_widget->sizePolicy());
    _scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    _gl_widget = new GLWidget(this);

    centralWidget()->setLayout(new QHBoxLayout());
    centralWidget()->layout()->addWidget(_gl_widget);
    centralWidget()->layout()->addWidget(_scroll_area);

    // creating a signal slot mechanism between the rendering context and the side widget
    connect(_side_widget->rotate_x_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_x(int)));
    connect(_side_widget->rotate_y_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_y(int)));
    connect(_side_widget->rotate_z_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_z(int)));

    //connect(_gl_widget,SIGNAL(customContextMenuRequested(QPoint)),_side_widget,SLOT(setLabel(int,int)));
    connect(_side_widget->zoom_factor_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_zoom_factor(double)));

    connect(_side_widget->trans_x_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_x(double)));
    connect(_side_widget->trans_y_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_y(double)));
    connect(_side_widget->trans_z_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_z(double)));

    //connect(_side_widget->shader_check_box, SIGNAL(clicked(bool)), _gl_widget, SLOT(setShaderStatus(bool)));





    //connect(_side_widget->x_point, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(select_x_point(int)));
    connect(_side_widget->y_point, SIGNAL(currentIndexChanged(QString)), _gl_widget, SLOT(select_y_point(QString)));

    connect(_side_widget->change_x_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_point_x_position(int)));
    //connect(_side_widget->change_y_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_point_y_position(int)));
    //connect(_side_widget->change_z_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_point_z_position(int)));

    //connect(_side_widget->select_for_join, SIGNAL(clicked()), _gl_widget, SLOT(select_patch_for_join()));

    //connect(_side_widget->first_patch_side, SIGNAL(currentIndexChanged(QString)), _gl_widget, SLOT(set_first_joning_side(QString)));
    //connect(_side_widget->second_patch_side, SIGNAL(currentIndexChanged(QString)), _gl_widget, SLOT(set_second_joning_side(QString)));

}

//--------------------------------
// implementation of private slots
//--------------------------------
void MainWindow::on_action_Quit_triggered()
{
    qApp->exit(0);
}

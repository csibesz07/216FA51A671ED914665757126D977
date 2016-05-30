#include "GLWidget.h"
#include "../Core/Materials.h"
#include "../Core/Constants.h"
#include "../Core/Exceptions.h"
#include <QtDebug>

using namespace cagd;
using namespace std;
//--------------------------------
// special and default constructor
//--------------------------------
GLWidget::GLWidget(QWidget *parent, const QGLFormat &format): QGLWidget(format, parent)
{
    _timer = new QTimer(this);
    _timer->setInterval(0);

    connect( _timer , SIGNAL(timeout()) , this , SLOT(_animate()) ) ;
}

void getMouse(int x, int y) {
    std::cout<<x<<y;
}

//--------------------------------------------------------------------------------------
// this virtual function is called once before the first call to paintGL() or resizeGL()
//--------------------------------------------------------------------------------------
void GLWidget::initializeGL()
{

    // creating a perspective projection matrix
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    _aspect = (float)width() / (float)height();
    _z_near = 1.0;
    _z_far = 1000.0;
    _fovy = 45.0;

    gluPerspective(_fovy, _aspect, _z_near, _z_far);

    // setting the model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    _eye[0] = _eye[1] = 0.0, _eye[2] = 6.0;
    _center[0] = _center[1] = _center[2] = 0.0;
    _up[0] = _up[2] = 0.0, _up[1] = 1.0;

    gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

    glewInit();

    // enabling depth test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    // initial values of transformation parameters
    _zoom = 0.5;
    _angle_x = _angle_y = _angle_z = 0.0;
    _trans_x = _trans_y = _trans_z = 0.0;


    setMouseTracking(true);




    cs = new CompositeBezierSurface();
    cs->InsertNewPatch(-2,2,1,2);
    cs->InsertNewPatch(-2,2,-1,0);


    cout << "Vektor hossza: " << cs->_entities.size()<< "\n";


    //cs->JoinExistingTwoPatches(1,1,2,3);

}


void GLWidget::mouseMoveEvent(QMouseEvent *event){
    std::cout<<"hello";

}

//-------------------
// the rendering function
//-----------------------
void GLWidget::paintGL()
{
    // clears the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // stores/duplicates the original model view matrix
    glPushMatrix();

    // applying transformations
    glRotatef(_angle_x, 1.0, 0.0, 0.0);
    glRotatef(_angle_y, 0.0, 1.0, 0.0);
    glRotatef(_angle_z, 0.0, 0.0, 1.0);

    glTranslated(_trans_x, _trans_y, _trans_z);

    glScaled(_zoom, _zoom, _zoom);

    glDisable(GL_LIGHTING);

    glColor4f(0.8, 0.8, 0.8, 1.0);
    for(std::vector<Entity>::iterator it = cs->_entities.begin(); it != cs->_entities.end(); ++it)
    {
        it->patch->UpdateVertexBufferObjectsOfData();
        it->patch->RenderData();              //halo kirajzolasa
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                DCoordinate3 &ref = (*(*it).patch)(i,j);
                renderText(ref[0],ref[1],ref[2],QString::number(i)+", " +QString::number(j));
            }
        }
    }
    glEnable(GL_LIGHTING);

    int i = 0;
    for(std::vector<Entity>::iterator it = cs->_entities.begin(); it != cs->_entities.end(); ++it, ++i)
    {
        if (it->mesh)
        {
            switch (i % 3)
            {
            case 0:
                MatFBRuby.Apply();
                break;
            case 2:
                MatFBBrass.Apply();
                break;
            case 1:
                MatFBTurquoise.Apply();
                break;
            }
            it->mesh->Render();               //felulet kirajzolasa
        }
    }

    glPopMatrix();



}
void GLWidget::_animate()
{
    GLfloat *vertex = _mouse.MapVertexBuffer(GL_READ_WRITE);
    GLfloat *normal = _mouse.MapNormalBuffer(GL_READ_ONLY);
    _angle += DEG_TO_RADIAN;
    if ( _angle >= TWO_PI)
        _angle -= TWO_PI;
    GLfloat scale = sin(_angle) / 3000.0;
    for ( GLuint i = 0; i < _mouse.VertexCount (); ++i )
    {
        for ( GLuint coordinate = 0; coordinate < 3; ++coordinate , ++vertex , ++normal )
            *vertex += scale * (*normal );
    }
    _mouse.UnmapVertexBuffer();
    _mouse.UnmapNormalBuffer();

    updateGL();
}
//----------------------------------------------------------------------------
// when the main window is resized one needs to redefine the projection matrix
//----------------------------------------------------------------------------
void GLWidget::resizeGL(int w, int h)
{
    // setting the new size of the rendering context
    glViewport(0, 0, w, h);

    // redefining the projection matrix
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    _aspect = (float)w / (float)h;

    gluPerspective(_fovy, _aspect, _z_near, _z_far);

    // switching back to the model view matrix
    glMatrixMode(GL_MODELVIEW);

    updateGL();
}

//-----------------------------------
// implementation of the public slots
//-----------------------------------

void GLWidget::set_angle_x(int value)
{
    if (_angle_x != value)
    {
        _angle_x = value;
        updateGL();
    }
}

void GLWidget::set_angle_y(int value)
{
    if (_angle_y != value)
    {
        _angle_y = value;
        updateGL();
    }
}

void GLWidget::set_angle_z(int value)
{
    if (_angle_z != value)
    {
        _angle_z = value;
        updateGL();
    }
}

void GLWidget::set_zoom_factor(double value)
{
    if (_zoom != value)
    {
        _zoom = value;
        updateGL();
    }
}

void GLWidget::set_trans_x(double value)
{
    if (_trans_x != value)
    {
        _trans_x = value;
        updateGL();
    }
}

void GLWidget::set_trans_y(double value)
{
    if (_trans_y != value)
    {
        _trans_y = value;
        updateGL();
    }
}

void GLWidget::set_trans_z(double value)
{
    if (_trans_z != value)
    {
        _trans_z = value;
        updateGL();
    }
}

void GLWidget::setShaderStatus(bool value)
{
    if (_apply_shader != value)
    {
        _apply_shader = value;

        if (!_apply_shader)
        {
            _shader.Disable();
        }
        else
        {
            _shader.Enable();
        }

        updateGL();
    }
}

void GLWidget::select_y_point(QString value)
{
    qDebug() << value;
}

void GLWidget::set_point_x_position(int value)
{
    qDebug() << " " << value;
    //modositja a kivalasztott pont x koordinatajat
}

GLWidget::~GLWidget()
{
    if ( _before_interpolation)
        delete _before_interpolation, _before_interpolation = 0;
    if (_after_interpolation)
        delete _after_interpolation, _after_interpolation = 0;
}

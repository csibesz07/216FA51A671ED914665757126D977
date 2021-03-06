#include "GLWidget.h"
#include "../Core/Materials.h"
#include "../Core/Constants.h"
#include "../Core/Exceptions.h"
#include "../Core/Lights.h"

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

    selected_x = 0;
    selected_y = 0;

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

    Entity *e1 = new Entity(-2,2,1,2,MatFBBrass);
    entities.push_back(e1);

    Entity *e2 = new Entity(-8,-4,-1,0);
    entities.push_back(e2);

    Entity *e3 = new Entity(-8,-2,-5,-3);
    entities.push_back(e3);

    Entity *e4 = new Entity(0,4,-5,-2);
    entities.push_back(e4);

    //e1->JoinExistingTwoPatches(*e2,-1,-2);
    e2->JoinExistingTwoPatches(*e3,1,2);
    e3->JoinExistingTwoPatches(*e4,-2,-1);
    e4->JoinExistingTwoPatches(*e1,2,1);

    selected=0;
    select_second_patch = false;

    lastPos.setX(0);
    lastPos.setY(0);
    _move_camera=false;
}


void GLWidget::mouseMoveEvent(QMouseEvent *event){

    //selection
   /* int index=0;
    glReadPixels(event->x(), height()-event->y(), 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
    if (index>0) {
        if (selected!=0) {
            selected->setMaterial(selectedMaterial);
        }
        selected=entities[index-1];
        selectedMaterial.setMaterial(entities[index-1]->getMaterial());
        entities[index-1]->setMaterial(MatFBEmerald);
        updateGL();
    }
    else {
        if (selected!=0 && !selected_w_click) {
            selected->setMaterial(selectedMaterial);
            updateGL();
        }
    }*/

    //camera rotation
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    //qDebug() << dx<<" "<<dy;

    if (event->buttons() & Qt::LeftButton) {
        if (!_move_camera) {
            _angle_x+= dy;
            _angle_y+= dx;
        }
        else {
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            _center[0]+=dx/(double)5;
            _center[1]-=dy/(double)5;
            gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);
        }
        updateGL();
    } else if (event->buttons() & Qt::RightButton) {
        if (!_move_camera) {
            _angle_x+= dy;
            _angle_z+= dx;
        }
        else {
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            _center[0]+=dx/(double)5;
            _center[1]-=dy/(double)5;
            gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);
        }
        updateGL();
    }
    lastPos = event->pos();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    //selection
    int index=0;
    glReadPixels(event->x(), height()-event->y(), 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
    if (index>0) {
        if (selected!=0) {
            selected->setMaterial(selectedMaterial);
        }
        selected=entities[index-1];
        selectedMaterial.setMaterial(entities[index-1]->getMaterial());
        entities[index-1]->setMaterial(MatFBEmerald);
        setValue(true);
        updateGL();
    }
    else {
        if (selected!=0) {
            selected->setMaterial(selectedMaterial);
            setValue(false);
            updateGL();
        }
    }
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    _zoom+=event->delta()/(double)1000*_zoom;
    //qDebug() << _zoom;
    updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent* event) {
    //qDebug()<< event->key() << " "<< Qt::Key_Left <<"\n";
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (event->key()==Qt::Key_Left || event->key()==Qt::Key_A) {
        //qDebug() << "LEFT\n";
        if (!_move_camera) {
            _eye[0]-=.15;
            _center[0]-=.2;
            gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);
        }
        else {
            _trans_x-=.2;
        }
        updateGL();
    }
    else if (event->key()==Qt::Key_Right || event->key()==Qt::Key_D) {
        //qDebug() << "RIGHT\n";
        if (!_move_camera) {
            _eye[0]+=.15;
            _center[0]+=.2;
            gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);
        }
        else {
            _trans_x+=.2;
        }updateGL();
    }
    else if (event->key()==Qt::Key_Up || event->key()==Qt::Key_W) {
        //qDebug() << "UP\n";
        if (!_move_camera) {
            _eye[1]+=.15;
            _center[1]+=.2;
            gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);
        }else {
            _trans_y+=.2;
        }updateGL();
    }
    else if (event->key()==Qt::Key_Down || event->key()==Qt::Key_S) {
        //qDebug() << "DOWN\n";
        if (!_move_camera) {_eye[1]-=.15;
            _center[1]-=.2;
            gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);
        }else {_trans_y-=.2;
        }updateGL();
    }
    else if (event->key()==Qt::Key_F) {
        _eye[2]+=.2;
        _center[2]+=.2;
        gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);
        updateGL();
    }
    else if (event->key()==Qt::Key_R) {
        _eye[2]-=.2;
        _center[2]-=.2;
        gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);
        updateGL();
    }

}

//-------------------
// the rendering function
//-----------------------
void GLWidget::paintGL()
{
    //STENCIL BUFFER az eger detektalasahoz

    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


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
    for(std::vector<cagd::Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        (*it)->patch->UpdateVertexBufferObjectsOfData();
        (*it)->patch->RenderData();              //halo kirajzolasa
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                DCoordinate3 &ref = (*(*it)->patch)(i,j);
                renderText(ref[0],ref[1],ref[2],QString::number(i)+", " +QString::number(j));
            }
        }
    }

   /* DirectionalLight *dl=0;
    HCoordinate3 direction(25.0,0.0,1.0,0.0);
    Color4 ambient(0.4,0.4,0.4,1.0);
    Color4 diffuse(0.8,0.8,0.8,1.0);
    Color4 specular(1.0,1.0,1.0,1.0);
    dl = new DirectionalLight(GL_LIGHT0,direction,ambient,diffuse,specular);*/

    glEnable(GL_LIGHTING);

  /*  if(dl)
    {
        dl->Enable();*/

        for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
        {
            int i = std::distance(entities.begin(), it);
            if ((*it)->mesh) {
                (*it)->materialApply();
                glStencilFunc(GL_ALWAYS, i + 1, -1);
                (*it)->mesh->Render();
                (*it)->mesh->RenderNormals();
            }
        }

      /*  dl->Disable();
    }*/

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

void GLWidget::select_x_point(int value)
{
    selected_x = value;
}

void GLWidget::select_y_point(int value)
{
    selected_y = value;
}

void GLWidget::set_point_x_position(int value)
{
    //qDebug() << " " << value;
    //modositja a kivalasztott pont x koordinatajat
}

void GLWidget::setValue(bool value)
{
    emit valueChanged(value);
}

GLWidget::~GLWidget()
{
}

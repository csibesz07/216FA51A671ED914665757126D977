/****************************************************************************
** Meta object code from reading C++ file 'GLWidget.h'
**
** Created: Tue May 31 15:05:24 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CAGD_PROJECT/GUI/GLWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,    9,    9,    9, 0x0a,
      55,   49,    9,    9, 0x0a,
      72,   49,    9,    9, 0x0a,
      89,   49,    9,    9, 0x0a,
     106,   49,    9,    9, 0x0a,
     130,   49,    9,    9, 0x0a,
     150,   49,    9,    9, 0x0a,
     170,   49,    9,    9, 0x0a,
     190,   49,    9,    9, 0x0a,
     212,   49,    9,    9, 0x0a,
     232,   49,    9,    9, 0x0a,
     252,   49,    9,    9, 0x0a,
     278,   49,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GLWidget[] = {
    "GLWidget\0\0newValue\0valueChanged(bool)\0"
    "_animate()\0value\0set_angle_x(int)\0"
    "set_angle_y(int)\0set_angle_z(int)\0"
    "set_zoom_factor(double)\0set_trans_x(double)\0"
    "set_trans_y(double)\0set_trans_z(double)\0"
    "setShaderStatus(bool)\0select_x_point(int)\0"
    "select_y_point(int)\0set_point_x_position(int)\0"
    "setValue(bool)\0"
};

const QMetaObject GLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLWidget,
      qt_meta_data_GLWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GLWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget))
        return static_cast<void*>(const_cast< GLWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _animate(); break;
        case 2: set_angle_x((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: set_angle_y((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: set_angle_z((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: set_zoom_factor((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: set_trans_x((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: set_trans_y((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: set_trans_z((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: setShaderStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: select_x_point((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: select_y_point((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: set_point_x_position((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: setValue((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void GLWidget::valueChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

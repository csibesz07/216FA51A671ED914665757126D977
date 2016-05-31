/****************************************************************************
** Meta object code from reading C++ file 'SideWidget.h'
**
** Created: Tue May 31 14:47:10 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CAGD_PROJECT/GUI/SideWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SideWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SideWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   12,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SideWidget[] = {
    "SideWidget\0\0value\0set_combo(bool)\0"
};

const QMetaObject SideWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SideWidget,
      qt_meta_data_SideWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SideWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SideWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SideWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SideWidget))
        return static_cast<void*>(const_cast< SideWidget*>(this));
    if (!strcmp(_clname, "Ui::SideWidget"))
        return static_cast< Ui::SideWidget*>(const_cast< SideWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SideWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: set_combo((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

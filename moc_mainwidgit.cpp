/****************************************************************************
** Meta object code from reading C++ file 'mainwidgit.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwidgit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwidgit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Mainwidgit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   27,   11,   11, 0x0a,
      47,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Mainwidgit[] = {
    "Mainwidgit\0\0kill_mplayer()\0mod\0"
    "label_func(int)\0close_list()\0"
};

void Mainwidgit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Mainwidgit *_t = static_cast<Mainwidgit *>(_o);
        switch (_id) {
        case 0: _t->kill_mplayer(); break;
        case 1: _t->label_func((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->close_list(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Mainwidgit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Mainwidgit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Mainwidgit,
      qt_meta_data_Mainwidgit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Mainwidgit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Mainwidgit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Mainwidgit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Mainwidgit))
        return static_cast<void*>(const_cast< Mainwidgit*>(this));
    return QWidget::qt_metacast(_clname);
}

int Mainwidgit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Mainwidgit::kill_mplayer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

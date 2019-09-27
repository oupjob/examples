/****************************************************************************
** Meta object code from reading C++ file 'inputcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../untitled/inputcontroller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inputcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InputController[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      24,   16,   16,   16, 0x05,
      39,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   54,   16,   16, 0x09,
      91,   87,   16,   16, 0x09,
     113,   16,   16,   16, 0x0a,
     126,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_InputController[] = {
    "InputController\0\0stop()\0inputHandled()\0"
    "errorHandled()\0code2value\0"
    "inputHandler(QString)\0msg\0"
    "errorHandler(QString)\0runObserve()\0"
    "stopObserve()\0"
};

void InputController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InputController *_t = static_cast<InputController *>(_o);
        switch (_id) {
        case 0: _t->stop(); break;
        case 1: _t->inputHandled(); break;
        case 2: _t->errorHandled(); break;
        case 3: _t->inputHandler((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->errorHandler((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->runObserve(); break;
        case 6: _t->stopObserve(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData InputController::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InputController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_InputController,
      qt_meta_data_InputController, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InputController::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InputController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InputController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InputController))
        return static_cast<void*>(const_cast< InputController*>(this));
    return QObject::qt_metacast(_clname);
}

int InputController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void InputController::stop()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void InputController::inputHandled()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void InputController::errorHandled()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE

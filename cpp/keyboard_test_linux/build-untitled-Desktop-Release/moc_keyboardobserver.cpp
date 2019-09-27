/****************************************************************************
** Meta object code from reading C++ file 'keyboardobserver.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../untitled/keyboardobserver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keyboardobserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KeyboardObserver[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   18,   17,   17, 0x05,
      43,   38,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      58,   17,   17,   17, 0x0a,
      68,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_KeyboardObserver[] = {
    "KeyboardObserver\0\0code\0input(QString)\0"
    "text\0error(QString)\0process()\0stop()\0"
};

void KeyboardObserver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        KeyboardObserver *_t = static_cast<KeyboardObserver *>(_o);
        switch (_id) {
        case 0: _t->input((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->process(); break;
        case 3: _t->stop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData KeyboardObserver::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject KeyboardObserver::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KeyboardObserver,
      qt_meta_data_KeyboardObserver, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KeyboardObserver::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KeyboardObserver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KeyboardObserver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KeyboardObserver))
        return static_cast<void*>(const_cast< KeyboardObserver*>(this));
    return QObject::qt_metacast(_clname);
}

int KeyboardObserver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void KeyboardObserver::input(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KeyboardObserver::error(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_QwertyKeyboardObserver[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x0a,
      34,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QwertyKeyboardObserver[] = {
    "QwertyKeyboardObserver\0\0process()\0"
    "stop()\0"
};

void QwertyKeyboardObserver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QwertyKeyboardObserver *_t = static_cast<QwertyKeyboardObserver *>(_o);
        switch (_id) {
        case 0: _t->process(); break;
        case 1: _t->stop(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QwertyKeyboardObserver::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QwertyKeyboardObserver::staticMetaObject = {
    { &KeyboardObserver::staticMetaObject, qt_meta_stringdata_QwertyKeyboardObserver,
      qt_meta_data_QwertyKeyboardObserver, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QwertyKeyboardObserver::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QwertyKeyboardObserver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QwertyKeyboardObserver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QwertyKeyboardObserver))
        return static_cast<void*>(const_cast< QwertyKeyboardObserver*>(this));
    return KeyboardObserver::qt_metacast(_clname);
}

int QwertyKeyboardObserver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KeyboardObserver::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_FunctionalKeyboardObserver[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x0a,
      38,   27,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FunctionalKeyboardObserver[] = {
    "FunctionalKeyboardObserver\0\0process()\0"
    "stop()\0"
};

void FunctionalKeyboardObserver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FunctionalKeyboardObserver *_t = static_cast<FunctionalKeyboardObserver *>(_o);
        switch (_id) {
        case 0: _t->process(); break;
        case 1: _t->stop(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData FunctionalKeyboardObserver::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FunctionalKeyboardObserver::staticMetaObject = {
    { &KeyboardObserver::staticMetaObject, qt_meta_stringdata_FunctionalKeyboardObserver,
      qt_meta_data_FunctionalKeyboardObserver, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FunctionalKeyboardObserver::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FunctionalKeyboardObserver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FunctionalKeyboardObserver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FunctionalKeyboardObserver))
        return static_cast<void*>(const_cast< FunctionalKeyboardObserver*>(this));
    return KeyboardObserver::qt_metacast(_clname);
}

int FunctionalKeyboardObserver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KeyboardObserver::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

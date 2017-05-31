/****************************************************************************
** Meta object code from reading C++ file 'gra.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kod/gra.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gra.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Gra_t {
    QByteArrayData data[9];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Gra_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Gra_t qt_meta_stringdata_Gra = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Gra"
QT_MOC_LITERAL(1, 4, 11), // "zmianaetapu"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 4), // "info"
QT_MOC_LITERAL(4, 22, 6), // "saveOn"
QT_MOC_LITERAL(5, 29, 7), // "saveOff"
QT_MOC_LITERAL(6, 37, 7), // "nowagra"
QT_MOC_LITERAL(7, 45, 9), // "zapiszgra"
QT_MOC_LITERAL(8, 55, 10) // "wczytajgre"

    },
    "Gra\0zmianaetapu\0\0info\0saveOn\0saveOff\0"
    "nowagra\0zapiszgra\0wczytajgre"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Gra[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    0,   47,    2, 0x06 /* Public */,
       5,    0,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   49,    2, 0x0a /* Public */,
       7,    0,   50,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Gra::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Gra *_t = static_cast<Gra *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->zmianaetapu((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->saveOn(); break;
        case 2: _t->saveOff(); break;
        case 3: _t->nowagra(); break;
        case 4: _t->zapiszgra(); break;
        case 5: _t->wczytajgre(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Gra::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Gra::zmianaetapu)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Gra::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Gra::saveOn)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Gra::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Gra::saveOff)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject Gra::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Gra.data,
      qt_meta_data_Gra,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Gra::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gra::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Gra.stringdata0))
        return static_cast<void*>(const_cast< Gra*>(this));
    return QWidget::qt_metacast(_clname);
}

int Gra::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Gra::zmianaetapu(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Gra::saveOn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Gra::saveOff()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

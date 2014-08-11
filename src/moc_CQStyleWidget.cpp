/****************************************************************************
** Meta object code from reading C++ file 'CQStyleWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/CQStyleWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CQStyleWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CQStyleWidgetMgr_t {
    QByteArrayData data[7];
    char stringdata[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CQStyleWidgetMgr_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CQStyleWidgetMgr_t qt_meta_stringdata_CQStyleWidgetMgr = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 10),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 5),
QT_MOC_LITERAL(4, 35, 12),
QT_MOC_LITERAL(5, 48, 10),
QT_MOC_LITERAL(6, 59, 1)
    },
    "CQStyleWidgetMgr\0styleAdded\0\0style\0"
    "styleChanged\0removeSlot\0o\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQStyleWidgetMgr[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06,
       4,    1,   32,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    1,   35,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QObjectStar,    6,

       0        // eod
};

void CQStyleWidgetMgr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQStyleWidgetMgr *_t = static_cast<CQStyleWidgetMgr *>(_o);
        switch (_id) {
        case 0: _t->styleAdded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->styleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->removeSlot((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CQStyleWidgetMgr::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CQStyleWidgetMgr::styleAdded)) {
                *result = 0;
            }
        }
        {
            typedef void (CQStyleWidgetMgr::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CQStyleWidgetMgr::styleChanged)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject CQStyleWidgetMgr::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CQStyleWidgetMgr.data,
      qt_meta_data_CQStyleWidgetMgr,  qt_static_metacall, 0, 0}
};


const QMetaObject *CQStyleWidgetMgr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQStyleWidgetMgr::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CQStyleWidgetMgr.stringdata))
        return static_cast<void*>(const_cast< CQStyleWidgetMgr*>(this));
    return QObject::qt_metacast(_clname);
}

int CQStyleWidgetMgr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CQStyleWidgetMgr::styleAdded(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CQStyleWidgetMgr::styleChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

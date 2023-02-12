/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../skproject/mainwindow.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[28];
    char stringdata0[11];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[22];
    char stringdata5[7];
    char stringdata6[6];
    char stringdata7[3];
    char stringdata8[5];
    char stringdata9[5];
    char stringdata10[6];
    char stringdata11[5];
    char stringdata12[12];
    char stringdata13[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 19),  // "on_startBtn_clicked"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 18),  // "on_exitBtn_clicked"
        QT_MOC_LITERAL(51, 21),  // "read_data_from_server"
        QT_MOC_LITERAL(73, 6),  // "rdyYes"
        QT_MOC_LITERAL(80, 5),  // "rdyNo"
        QT_MOC_LITERAL(86, 2),  // "up"
        QT_MOC_LITERAL(89, 4),  // "down"
        QT_MOC_LITERAL(94, 4),  // "left"
        QT_MOC_LITERAL(99, 5),  // "right"
        QT_MOC_LITERAL(105, 4),  // "bomb"
        QT_MOC_LITERAL(110, 11),  // "backToStart"
        QT_MOC_LITERAL(122, 21)   // "on_confirmBtn_clicked"
    },
    "MainWindow",
    "on_startBtn_clicked",
    "",
    "on_exitBtn_clicked",
    "read_data_from_server",
    "rdyYes",
    "rdyNo",
    "up",
    "down",
    "left",
    "right",
    "bomb",
    "backToStart",
    "on_confirmBtn_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x08,    1 /* Private */,
       3,    0,   87,    2, 0x08,    2 /* Private */,
       4,    0,   88,    2, 0x08,    3 /* Private */,
       5,    0,   89,    2, 0x08,    4 /* Private */,
       6,    0,   90,    2, 0x08,    5 /* Private */,
       7,    0,   91,    2, 0x08,    6 /* Private */,
       8,    0,   92,    2, 0x08,    7 /* Private */,
       9,    0,   93,    2, 0x08,    8 /* Private */,
      10,    0,   94,    2, 0x08,    9 /* Private */,
      11,    0,   95,    2, 0x08,   10 /* Private */,
      12,    0,   96,    2, 0x08,   11 /* Private */,
      13,    0,   97,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_startBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_exitBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'read_data_from_server'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rdyYes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rdyNo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'up'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'down'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'left'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'right'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'bomb'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'backToStart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_confirmBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_startBtn_clicked(); break;
        case 1: _t->on_exitBtn_clicked(); break;
        case 2: _t->read_data_from_server(); break;
        case 3: _t->rdyYes(); break;
        case 4: _t->rdyNo(); break;
        case 5: _t->up(); break;
        case 6: _t->down(); break;
        case 7: _t->left(); break;
        case 8: _t->right(); break;
        case 9: _t->bomb(); break;
        case 10: _t->backToStart(); break;
        case 11: _t->on_confirmBtn_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

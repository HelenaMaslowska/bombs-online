/****************************************************************************
** Meta object code from reading C++ file 'game.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../skproject/game.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_Game_t {
    uint offsetsAndSizes[24];
    char stringdata0[5];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[11];
    char stringdata5[13];
    char stringdata6[13];
    char stringdata7[14];
    char stringdata8[13];
    char stringdata9[11];
    char stringdata10[20];
    char stringdata11[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Game_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Game_t qt_meta_stringdata_Game = {
    {
        QT_MOC_LITERAL(0, 4),  // "Game"
        QT_MOC_LITERAL(5, 7),  // "readyNo"
        QT_MOC_LITERAL(13, 0),  // ""
        QT_MOC_LITERAL(14, 8),  // "readyYes"
        QT_MOC_LITERAL(23, 10),  // "keyboardUp"
        QT_MOC_LITERAL(34, 12),  // "keyboardDown"
        QT_MOC_LITERAL(47, 12),  // "keyboardLeft"
        QT_MOC_LITERAL(60, 13),  // "keyboardRight"
        QT_MOC_LITERAL(74, 12),  // "keyboardBomb"
        QT_MOC_LITERAL(87, 10),  // "quitGameUI"
        QT_MOC_LITERAL(98, 19),  // "on_readyBtn_clicked"
        QT_MOC_LITERAL(118, 18)   // "on_exitBtn_clicked"
    },
    "Game",
    "readyNo",
    "",
    "readyYes",
    "keyboardUp",
    "keyboardDown",
    "keyboardLeft",
    "keyboardRight",
    "keyboardBomb",
    "quitGameUI",
    "on_readyBtn_clicked",
    "on_exitBtn_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Game[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x06,    1 /* Public */,
       3,    0,   75,    2, 0x06,    2 /* Public */,
       4,    0,   76,    2, 0x06,    3 /* Public */,
       5,    0,   77,    2, 0x06,    4 /* Public */,
       6,    0,   78,    2, 0x06,    5 /* Public */,
       7,    0,   79,    2, 0x06,    6 /* Public */,
       8,    0,   80,    2, 0x06,    7 /* Public */,
       9,    0,   81,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    0,   82,    2, 0x0a,    9 /* Public */,
      11,    0,   83,    2, 0x0a,   10 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Game::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_Game.offsetsAndSizes,
    qt_meta_data_Game,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_Game_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Game, std::true_type>,
        // method 'readyNo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'readyYes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'keyboardUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'keyboardDown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'keyboardLeft'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'keyboardRight'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'keyboardBomb'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'quitGameUI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_readyBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_exitBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Game *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->readyNo(); break;
        case 1: _t->readyYes(); break;
        case 2: _t->keyboardUp(); break;
        case 3: _t->keyboardDown(); break;
        case 4: _t->keyboardLeft(); break;
        case 5: _t->keyboardRight(); break;
        case 6: _t->keyboardBomb(); break;
        case 7: _t->quitGameUI(); break;
        case 8: _t->on_readyBtn_clicked(); break;
        case 9: _t->on_exitBtn_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Game::*)();
            if (_t _q_method = &Game::readyNo; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Game::*)();
            if (_t _q_method = &Game::readyYes; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Game::*)();
            if (_t _q_method = &Game::keyboardUp; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Game::*)();
            if (_t _q_method = &Game::keyboardDown; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Game::*)();
            if (_t _q_method = &Game::keyboardLeft; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Game::*)();
            if (_t _q_method = &Game::keyboardRight; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Game::*)();
            if (_t _q_method = &Game::keyboardBomb; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Game::*)();
            if (_t _q_method = &Game::quitGameUI; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Game::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Game.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Game::readyNo()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Game::readyYes()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Game::keyboardUp()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Game::keyboardDown()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Game::keyboardLeft()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Game::keyboardRight()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Game::keyboardBomb()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Game::quitGameUI()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

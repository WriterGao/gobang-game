/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/ui/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[29];
    char stringdata0[326];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 9), // "onNewGame"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "onNewPvPGame"
QT_MOC_LITERAL(4, 35, 12), // "onNewPvCGame"
QT_MOC_LITERAL(5, 48, 11), // "onPauseGame"
QT_MOC_LITERAL(6, 60, 13), // "onRestartGame"
QT_MOC_LITERAL(7, 74, 6), // "onUndo"
QT_MOC_LITERAL(8, 81, 10), // "onSettings"
QT_MOC_LITERAL(9, 92, 6), // "onExit"
QT_MOC_LITERAL(10, 99, 7), // "onAbout"
QT_MOC_LITERAL(11, 107, 18), // "onGameStateChanged"
QT_MOC_LITERAL(12, 126, 21), // "GameEngine::GameState"
QT_MOC_LITERAL(13, 148, 5), // "state"
QT_MOC_LITERAL(14, 154, 15), // "onPlayerChanged"
QT_MOC_LITERAL(15, 170, 21), // "ChessBoard::PieceType"
QT_MOC_LITERAL(16, 192, 6), // "player"
QT_MOC_LITERAL(17, 199, 10), // "onMoveMade"
QT_MOC_LITERAL(18, 210, 8), // "position"
QT_MOC_LITERAL(19, 219, 5), // "piece"
QT_MOC_LITERAL(20, 225, 9), // "onGameWon"
QT_MOC_LITERAL(21, 235, 6), // "winner"
QT_MOC_LITERAL(22, 242, 10), // "onGameDraw"
QT_MOC_LITERAL(23, 253, 15), // "onErrorOccurred"
QT_MOC_LITERAL(24, 269, 7), // "message"
QT_MOC_LITERAL(25, 277, 8), // "updateUI"
QT_MOC_LITERAL(26, 286, 15), // "updateStatusBar"
QT_MOC_LITERAL(27, 302, 10), // "formatTime"
QT_MOC_LITERAL(28, 313, 12) // "milliseconds"

    },
    "MainWindow\0onNewGame\0\0onNewPvPGame\0"
    "onNewPvCGame\0onPauseGame\0onRestartGame\0"
    "onUndo\0onSettings\0onExit\0onAbout\0"
    "onGameStateChanged\0GameEngine::GameState\0"
    "state\0onPlayerChanged\0ChessBoard::PieceType\0"
    "player\0onMoveMade\0position\0piece\0"
    "onGameWon\0winner\0onGameDraw\0onErrorOccurred\0"
    "message\0updateUI\0updateStatusBar\0"
    "formatTime\0milliseconds"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x08 /* Private */,
       3,    0,  105,    2, 0x08 /* Private */,
       4,    0,  106,    2, 0x08 /* Private */,
       5,    0,  107,    2, 0x08 /* Private */,
       6,    0,  108,    2, 0x08 /* Private */,
       7,    0,  109,    2, 0x08 /* Private */,
       8,    0,  110,    2, 0x08 /* Private */,
       9,    0,  111,    2, 0x08 /* Private */,
      10,    0,  112,    2, 0x08 /* Private */,
      11,    1,  113,    2, 0x08 /* Private */,
      14,    1,  116,    2, 0x08 /* Private */,
      17,    2,  119,    2, 0x08 /* Private */,
      20,    1,  124,    2, 0x08 /* Private */,
      22,    0,  127,    2, 0x08 /* Private */,
      23,    1,  128,    2, 0x08 /* Private */,
      25,    0,  131,    2, 0x08 /* Private */,
      26,    0,  132,    2, 0x08 /* Private */,
      27,    1,  133,    2, 0x08 /* Private */,

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
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 15,   18,   19,
    QMetaType::Void, 0x80000000 | 15,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString, QMetaType::LongLong,   28,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onNewGame(); break;
        case 1: _t->onNewPvPGame(); break;
        case 2: _t->onNewPvCGame(); break;
        case 3: _t->onPauseGame(); break;
        case 4: _t->onRestartGame(); break;
        case 5: _t->onUndo(); break;
        case 6: _t->onSettings(); break;
        case 7: _t->onExit(); break;
        case 8: _t->onAbout(); break;
        case 9: _t->onGameStateChanged((*reinterpret_cast< GameEngine::GameState(*)>(_a[1]))); break;
        case 10: _t->onPlayerChanged((*reinterpret_cast< ChessBoard::PieceType(*)>(_a[1]))); break;
        case 11: _t->onMoveMade((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< ChessBoard::PieceType(*)>(_a[2]))); break;
        case 12: _t->onGameWon((*reinterpret_cast< ChessBoard::PieceType(*)>(_a[1]))); break;
        case 13: _t->onGameDraw(); break;
        case 14: _t->onErrorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->updateUI(); break;
        case 16: _t->updateStatusBar(); break;
        case 17: { QString _r = _t->formatTime((*reinterpret_cast< qint64(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

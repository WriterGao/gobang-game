/****************************************************************************
** Meta object code from reading C++ file 'ConfigManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/managers/ConfigManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConfigManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConfigManager_t {
    QByteArrayData data[18];
    char stringdata0[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigManager_t qt_meta_stringdata_ConfigManager = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ConfigManager"
QT_MOC_LITERAL(1, 14, 15), // "gameModeChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 20), // "GameEngine::GameMode"
QT_MOC_LITERAL(4, 52, 4), // "mode"
QT_MOC_LITERAL(5, 57, 19), // "aiDifficultyChanged"
QT_MOC_LITERAL(6, 77, 10), // "difficulty"
QT_MOC_LITERAL(7, 88, 22), // "showCoordinatesChanged"
QT_MOC_LITERAL(8, 111, 4), // "show"
QT_MOC_LITERAL(9, 116, 22), // "backgroundImageChanged"
QT_MOC_LITERAL(10, 139, 4), // "path"
QT_MOC_LITERAL(11, 144, 22), // "backgroundMusicChanged"
QT_MOC_LITERAL(12, 167, 13), // "volumeChanged"
QT_MOC_LITERAL(13, 181, 6), // "volume"
QT_MOC_LITERAL(14, 188, 15), // "languageChanged"
QT_MOC_LITERAL(15, 204, 8), // "language"
QT_MOC_LITERAL(16, 213, 12), // "themeChanged"
QT_MOC_LITERAL(17, 226, 5) // "theme"

    },
    "ConfigManager\0gameModeChanged\0\0"
    "GameEngine::GameMode\0mode\0aiDifficultyChanged\0"
    "difficulty\0showCoordinatesChanged\0"
    "show\0backgroundImageChanged\0path\0"
    "backgroundMusicChanged\0volumeChanged\0"
    "volume\0languageChanged\0language\0"
    "themeChanged\0theme"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,
       7,    1,   60,    2, 0x06 /* Public */,
       9,    1,   63,    2, 0x06 /* Public */,
      11,    1,   66,    2, 0x06 /* Public */,
      12,    1,   69,    2, 0x06 /* Public */,
      14,    1,   72,    2, 0x06 /* Public */,
      16,    1,   75,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Float,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   17,

       0        // eod
};

void ConfigManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConfigManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->gameModeChanged((*reinterpret_cast< GameEngine::GameMode(*)>(_a[1]))); break;
        case 1: _t->aiDifficultyChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->showCoordinatesChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->backgroundImageChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->backgroundMusicChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->volumeChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->languageChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->themeChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConfigManager::*)(GameEngine::GameMode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigManager::gameModeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConfigManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigManager::aiDifficultyChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ConfigManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigManager::showCoordinatesChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ConfigManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigManager::backgroundImageChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ConfigManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigManager::backgroundMusicChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ConfigManager::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigManager::volumeChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ConfigManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigManager::languageChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ConfigManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigManager::themeChanged)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConfigManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ConfigManager.data,
    qt_meta_data_ConfigManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConfigManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ConfigManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ConfigManager::gameModeChanged(GameEngine::GameMode _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConfigManager::aiDifficultyChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ConfigManager::showCoordinatesChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ConfigManager::backgroundImageChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ConfigManager::backgroundMusicChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ConfigManager::volumeChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ConfigManager::languageChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ConfigManager::themeChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

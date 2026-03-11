/****************************************************************************
** Meta object code from reading C++ file 'qt_io.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../comal-ide/include/qt_io.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_io.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN4QtIOE_t {};
} // unnamed namespace

template <> constexpr inline auto QtIO::qt_create_metaobjectdata<qt_meta_tag_ZN4QtIOE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "QtIO",
        "textOutput",
        "",
        "text",
        "screenCleared",
        "cursorMoved",
        "row",
        "col",
        "inputRequested",
        "prompt"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'textOutput'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'screenCleared'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'cursorMoved'
        QtMocHelpers::SignalData<void(int, int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 }, { QMetaType::Int, 7 },
        }}),
        // Signal 'inputRequested'
        QtMocHelpers::SignalData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<QtIO, qt_meta_tag_ZN4QtIOE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject QtIO::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4QtIOE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4QtIOE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN4QtIOE_t>.metaTypes,
    nullptr
} };

void QtIO::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QtIO *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->textOutput((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->screenCleared(); break;
        case 2: _t->cursorMoved((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 3: _t->inputRequested((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (QtIO::*)(const QString & )>(_a, &QtIO::textOutput, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (QtIO::*)()>(_a, &QtIO::screenCleared, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (QtIO::*)(int , int )>(_a, &QtIO::cursorMoved, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (QtIO::*)(const QString & )>(_a, &QtIO::inputRequested, 3))
            return;
    }
}

const QMetaObject *QtIO::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtIO::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4QtIOE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "comal::runtime::IOInterface"))
        return static_cast< comal::runtime::IOInterface*>(this);
    return QObject::qt_metacast(_clname);
}

int QtIO::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QtIO::textOutput(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void QtIO::screenCleared()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QtIO::cursorMoved(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}

// SIGNAL 3
void QtIO::inputRequested(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}
QT_WARNING_POP

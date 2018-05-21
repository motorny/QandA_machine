/****************************************************************************
** Meta object code from reading C++ file 'tst_qaunittests.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../test/tst_qaunittests.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tst_qaunittests.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QAUnitTests_t {
    QByteArrayData data[14];
    char stringdata0[231];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QAUnitTests_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QAUnitTests_t qt_meta_stringdata_QAUnitTests = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QAUnitTests"
QT_MOC_LITERAL(1, 12, 19), // "VocabularyTest_data"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 14), // "VocabularyTest"
QT_MOC_LITERAL(4, 48, 28), // "VocabularyRejectionTest_data"
QT_MOC_LITERAL(5, 77, 23), // "VocabularyRejectionTest"
QT_MOC_LITERAL(6, 101, 24), // "SimilarQuestionTest_data"
QT_MOC_LITERAL(7, 126, 19), // "SimilarQuestionTest"
QT_MOC_LITERAL(8, 146, 12), // "IdfTest_data"
QT_MOC_LITERAL(9, 159, 7), // "IdfTest"
QT_MOC_LITERAL(10, 167, 19), // "StrToIndexTest_data"
QT_MOC_LITERAL(11, 187, 14), // "StrToIndexTest"
QT_MOC_LITERAL(12, 202, 16), // "StemmerTest_data"
QT_MOC_LITERAL(13, 219, 11) // "StemmerTest"

    },
    "QAUnitTests\0VocabularyTest_data\0\0"
    "VocabularyTest\0VocabularyRejectionTest_data\0"
    "VocabularyRejectionTest\0"
    "SimilarQuestionTest_data\0SimilarQuestionTest\0"
    "IdfTest_data\0IdfTest\0StrToIndexTest_data\0"
    "StrToIndexTest\0StemmerTest_data\0"
    "StemmerTest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QAUnitTests[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

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

void QAUnitTests::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QAUnitTests *_t = static_cast<QAUnitTests *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->VocabularyTest_data(); break;
        case 1: _t->VocabularyTest(); break;
        case 2: _t->VocabularyRejectionTest_data(); break;
        case 3: _t->VocabularyRejectionTest(); break;
        case 4: _t->SimilarQuestionTest_data(); break;
        case 5: _t->SimilarQuestionTest(); break;
        case 6: _t->IdfTest_data(); break;
        case 7: _t->IdfTest(); break;
        case 8: _t->StrToIndexTest_data(); break;
        case 9: _t->StrToIndexTest(); break;
        case 10: _t->StemmerTest_data(); break;
        case 11: _t->StemmerTest(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QAUnitTests::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QAUnitTests.data,
      qt_meta_data_QAUnitTests,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QAUnitTests::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QAUnitTests::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QAUnitTests.stringdata0))
        return static_cast<void*>(const_cast< QAUnitTests*>(this));
    return QObject::qt_metacast(_clname);
}

int QAUnitTests::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

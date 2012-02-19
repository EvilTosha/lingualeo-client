/****************************************************************************
** Meta object code from reading C++ file 'serialport.h'
**
** Created: Mon 20. Feb 02:19:05 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/serialport.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SerialPort[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
      10,   54, // properties
       9,   84, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   17,   12,   11, 0x0a,
      34,   17,   12,   11, 0x0a,
      56,   47,   12,   11, 0x0a,
      71,   11,   12,   11, 0x2a,
      83,   17,   12,   11, 0x0a,
      98,   11,   12,   11, 0x2a,
     115,  109,   12,   11, 0x0a,
     132,   11,   12,   11, 0x2a,

 // properties: name, type, flags
     152,  145, 0x02095103,
     166,  157, 0x0009510b,
     182,  175, 0x0009510b,
     198,  189, 0x0009510b,
     219,  207, 0x0009510b,
     247,  231, 0x0009510b,
     263,   12, 0x01095103,
     267,   12, 0x01095103,
     281,  271, 0x0009500d,
     287,   12, 0x01095103,

 // enums: name, flags, count, data
     310, 0x0,    3,  120,
     321, 0x0,    9,  126,
     157, 0x0,    5,  144,
     175, 0x0,    6,  154,
     189, 0x0,    4,  166,
     207, 0x0,    4,  174,
     326, 0x0,    9,  182,
     231, 0x0,    5,  200,
     271, 0x0,   11,  210,

 // enum data: key, value
     332, uint(SerialPort::Input),
     338, uint(SerialPort::Output),
     345, uint(SerialPort::AllDirections),
     359, uint(SerialPort::Rate1200),
     368, uint(SerialPort::Rate2400),
     377, uint(SerialPort::Rate4800),
     386, uint(SerialPort::Rate9600),
     395, uint(SerialPort::Rate19200),
     405, uint(SerialPort::Rate38400),
     415, uint(SerialPort::Rate57600),
     425, uint(SerialPort::Rate115200),
     436, uint(SerialPort::UnknownRate),
     448, uint(SerialPort::Data5),
     454, uint(SerialPort::Data6),
     460, uint(SerialPort::Data7),
     466, uint(SerialPort::Data8),
     472, uint(SerialPort::UnknownDataBits),
     488, uint(SerialPort::NoParity),
     497, uint(SerialPort::EvenParity),
     508, uint(SerialPort::OddParity),
     518, uint(SerialPort::SpaceParity),
     530, uint(SerialPort::MarkParity),
     541, uint(SerialPort::UnknownParity),
     555, uint(SerialPort::OneStop),
     563, uint(SerialPort::OneAndHalfStop),
     578, uint(SerialPort::TwoStop),
     586, uint(SerialPort::UnknownStopBits),
     602, uint(SerialPort::NoFlowControl),
     616, uint(SerialPort::HardwareControl),
     632, uint(SerialPort::SoftwareControl),
     648, uint(SerialPort::UnknownFlowControl),
     667, uint(SerialPort::Le),
     670, uint(SerialPort::Dtr),
     674, uint(SerialPort::Rts),
     678, uint(SerialPort::St),
     681, uint(SerialPort::Sr),
     684, uint(SerialPort::Cts),
     688, uint(SerialPort::Dcd),
     692, uint(SerialPort::Ri),
     695, uint(SerialPort::Dsr),
     699, uint(SerialPort::SkipPolicy),
     710, uint(SerialPort::PassZeroPolicy),
     725, uint(SerialPort::IgnorePolicy),
     738, uint(SerialPort::StopReceivingPolicy),
     758, uint(SerialPort::UnknownPolicy),
     772, uint(SerialPort::NoError),
     780, uint(SerialPort::NoSuchDeviceError),
     798, uint(SerialPort::PermissionDeniedError),
     820, uint(SerialPort::DeviceAlreadyOpenedError),
     845, uint(SerialPort::DeviceIsNotOpenedError),
     868, uint(SerialPort::ParityError),
     880, uint(SerialPort::FramingError),
     893, uint(SerialPort::BreakConditionError),
     913, uint(SerialPort::IoError),
     921, uint(SerialPort::UnsupportedPortOperationError),
     951, uint(SerialPort::UnknownPortError),

       0        // eod
};

static const char qt_meta_stringdata_SerialPort[] = {
    "SerialPort\0\0bool\0set\0setDtr(bool)\0"
    "setRts(bool)\0duration\0sendBreak(int)\0"
    "sendBreak()\0setBreak(bool)\0setBreak()\0"
    "clear\0clearBreak(bool)\0clearBreak()\0"
    "qint32\0rate\0DataBits\0dataBits\0Parity\0"
    "parity\0StopBits\0stopBits\0FlowControl\0"
    "flowControl\0DataErrorPolicy\0dataErrorPolicy\0"
    "dtr\0rts\0PortError\0error\0restoreSettingsOnClose\0"
    "Directions\0Rate\0Lines\0Input\0Output\0"
    "AllDirections\0Rate1200\0Rate2400\0"
    "Rate4800\0Rate9600\0Rate19200\0Rate38400\0"
    "Rate57600\0Rate115200\0UnknownRate\0Data5\0"
    "Data6\0Data7\0Data8\0UnknownDataBits\0"
    "NoParity\0EvenParity\0OddParity\0SpaceParity\0"
    "MarkParity\0UnknownParity\0OneStop\0"
    "OneAndHalfStop\0TwoStop\0UnknownStopBits\0"
    "NoFlowControl\0HardwareControl\0"
    "SoftwareControl\0UnknownFlowControl\0"
    "Le\0Dtr\0Rts\0St\0Sr\0Cts\0Dcd\0Ri\0Dsr\0"
    "SkipPolicy\0PassZeroPolicy\0IgnorePolicy\0"
    "StopReceivingPolicy\0UnknownPolicy\0"
    "NoError\0NoSuchDeviceError\0"
    "PermissionDeniedError\0DeviceAlreadyOpenedError\0"
    "DeviceIsNotOpenedError\0ParityError\0"
    "FramingError\0BreakConditionError\0"
    "IoError\0UnsupportedPortOperationError\0"
    "UnknownPortError\0"
};

void SerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SerialPort *_t = static_cast<SerialPort *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->setDtr((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = _t->setRts((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->sendBreak((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->sendBreak();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->setBreak((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->setBreak();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->clearBreak((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->clearBreak();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SerialPort::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SerialPort::staticMetaObject = {
    { &QIODevice::staticMetaObject, qt_meta_stringdata_SerialPort,
      qt_meta_data_SerialPort, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SerialPort::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SerialPort))
        return static_cast<void*>(const_cast< SerialPort*>(this));
    return QIODevice::qt_metacast(_clname);
}

int SerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QIODevice::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qint32*>(_v) = rate(); break;
        case 1: *reinterpret_cast< DataBits*>(_v) = dataBits(); break;
        case 2: *reinterpret_cast< Parity*>(_v) = parity(); break;
        case 3: *reinterpret_cast< StopBits*>(_v) = stopBits(); break;
        case 4: *reinterpret_cast< FlowControl*>(_v) = flowControl(); break;
        case 5: *reinterpret_cast< DataErrorPolicy*>(_v) = dataErrorPolicy(); break;
        case 6: *reinterpret_cast< bool*>(_v) = dtr(); break;
        case 7: *reinterpret_cast< bool*>(_v) = rts(); break;
        case 8: *reinterpret_cast< PortError*>(_v) = error(); break;
        case 9: *reinterpret_cast< bool*>(_v) = restoreSettingsOnClose(); break;
        }
        _id -= 10;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setRate(*reinterpret_cast< qint32*>(_v)); break;
        case 1: setDataBits(*reinterpret_cast< DataBits*>(_v)); break;
        case 2: setParity(*reinterpret_cast< Parity*>(_v)); break;
        case 3: setStopBits(*reinterpret_cast< StopBits*>(_v)); break;
        case 4: setFlowControl(*reinterpret_cast< FlowControl*>(_v)); break;
        case 5: setDataErrorPolicy(*reinterpret_cast< DataErrorPolicy*>(_v)); break;
        case 6: setDtr(*reinterpret_cast< bool*>(_v)); break;
        case 7: setRts(*reinterpret_cast< bool*>(_v)); break;
        case 9: setRestoreSettingsOnClose(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 10;
    } else if (_c == QMetaObject::ResetProperty) {
        switch (_id) {
        case 8: unsetError(); break;
        }
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE

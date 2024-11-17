#include "CANBusReader.h"
#include <QDebug>

CANBusReader::CANBusReader(QString interface, QObject *parent)
    : QObject{parent}
{
    if (QCanBus::instance()->plugins().contains(CAN_BUS_PLUGIN)) {
        QString errorString;
        m_canDevice = QCanBus::instance()->createDevice(
            CAN_BUS_PLUGIN, interface, &errorString);
        if (!m_canDevice) {
            qDebug() << "couldn't create device";
            // TODO: Notify of the error
            qDebug() << errorString;
            return;
        } else {
            qDebug() << "device was created";
        }

        if (!m_canDevice->connectDevice()) {
            qDebug() << "connection failed";
            errorString = m_canDevice->errorString();
            qDebug() << "error details:" << errorString;
            delete m_canDevice;
            m_canDevice = nullptr;
            return;
        } else {
            connect(m_canDevice, &QCanBusDevice::framesReceived, this, &CANBusReader::readCanData);
            qDebug() << "connection was successful";
        }
    }
}
CANBusReader::~CANBusReader() {
    if (m_canDevice) {
        m_canDevice->disconnectDevice();
        delete m_canDevice;
    }
}

void CANBusReader::readCanData()
{
    // qDebug() << "read can data called";
    while (m_canDevice->framesAvailable()) {
        // qDebug() << "frame available";
        QCanBusFrame frame = m_canDevice->readFrame();
        if (frame.isValid() && frame.frameId() == FRAME_ID_SPEED) {
            int speed = static_cast<int>(frame.payload().at(0));
            emit newData(speed);
        }
    }
}

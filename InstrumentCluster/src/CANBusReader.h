#ifndef CANBUSREADER_H
#define CANBUSREADER_H

#include <QObject>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>

class CANBusReader : public QObject
{
    Q_OBJECT
public:
    explicit CANBusReader(QString interface = "can0", QObject *parent = nullptr);
    ~CANBusReader();

signals:
    void newData(int speed);

public slots:
    void readCanData();

private:
    QCanBusDevice *m_canDevice = nullptr;
    const quint32 FRAME_ID_SPEED = 0x021;
    const QString CAN_BUS_PLUGIN = "socketcan";
};

#endif // CANBUSREADER_H

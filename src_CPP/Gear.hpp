#ifndef GEAR_HPP
#define GEAR_HPP

#include <QObject>
#include <QThread>

#include "Props.hpp"
#include "GearWorker.hpp"

extern "C"
{
#include "../src_C/libpca9685.h"
}

class Gear : public QObject, virtual public Props
{
    Q_OBJECT
    Q_PROPERTY(quint8 isGear READ isGear WRITE setGear NOTIFY isGearChanged)
    QThread theThread;

public:
    explicit Gear(QObject *parent = nullptr);
    virtual ~Gear();

    quint8  isGear() const;
    void    setGear(quint8 gear);
    
public slots:
    void	setGearToP();
    void	setGearToN();
    void	setGearToD();
    void	setGearToR();

signals:
    void    operate();
    void    isGearChanged();

protected:
    quint8 & _gear;         // active gear
    quint8   clutch_;       // active clutch. This is that flywheel thing represented as the smallest flywheel == 0, next == 1...
    quint8   wheelSpeed_;   // this data will be gotten from CAN speed sensor to ensure D and R can only be entered when vehicle wheels are still
    quint8   _mode;         // throttle value assigned to current active gear
    quint8   _init;         // 0 if PCA9685 not init-ed, 1 if init-ed
    

    GearWorker  _gearWorker;

};

#endif // GEAR_HPP

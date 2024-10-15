#ifndef GEAR_HPP
#define GEAR_HPP

#include <QObject>
#include <QThread>

#include "Props.hpp"
#include "GearWorker.hpp"

// zzz
// extern "C"
// {
//     #include "../src_C/aptc.h"
// }

class Gear : virtual public Props
{
    QThread theThread;

public:
    explicit Gear(QObject *parent = nullptr);
    virtual ~Gear();

    void    abortThread();

    quint8  getGear() const override;
    void    setGear(quint8 gear) override;

    quint16 getSpeed() const override;
    void    setSpeed(quint16 speed) override;

protected:
    quint8  & _gear;  // active gear
    quint16   speed_; // current speed
    quint8    _mode;  // throttle value assigned to current active gear
    bool      _init;  // false if PCA9685 not yet init-ed, true if init-ed

    GearWorker  gearWorker_;
};

#endif // GEAR_HPP

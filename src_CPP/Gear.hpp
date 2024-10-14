#ifndef GEAR_HPP
#define GEAR_HPP

#include <QObject>
#include <QThread>

#include "Props.hpp"
#include "GearWorker.hpp"

<<<<<<< HEAD
// uncomment
// extern "C"
// {
// #include "../src_C/libpca9685.h"
// }

class Gear : virtual public Props
=======
extern "C"
{
#include "../src_C/libpca9685.h"
}

class Gear : public QObject, virtual public Props
>>>>>>> 459021e95ec89256e1383440028915b8be95ade7
{
    QThread theThread;

public:
    explicit Gear(QObject *parent = nullptr);
    virtual ~Gear();

<<<<<<< HEAD
    void    abortThread();
=======
    quint8  isGear() const;
    void    setGear(quint8 gear);
    
public slots:
    void	setGearToP();
    void	setGearToN();
    void	setGearToD();
    void	setGearToR();
>>>>>>> 459021e95ec89256e1383440028915b8be95ade7

    quint8  getGear() const override;
    void    setGear(quint8 gear) override;

    quint16 getSpeed() const override;
    void    setSpeed(quint16 speed) override;

protected:
<<<<<<< HEAD
    quint8  & _gear;  // active gear
    quint16   speed_; // current speed
    quint8    _mode;  // throttle value assigned to current active gear
    quint8    _init;  // 0 if PCA9685 not yet init-ed, 1 if init-ed
=======
    quint8 & _gear;         // active gear
    quint8   clutch_;       // active clutch. This is that flywheel thing represented as the smallest flywheel == 0, next == 1...
    quint8   wheelSpeed_;   // this data will be gotten from CAN speed sensor to ensure D and R can only be entered when vehicle wheels are still
    quint8   _mode;         // throttle value assigned to current active gear
    quint8   _init;         // 0 if PCA9685 not init-ed, 1 if init-ed
    

    GearWorker  _gearWorker;
>>>>>>> 459021e95ec89256e1383440028915b8be95ade7

    GearWorker  gearWorker_;
};

#endif // GEAR_HPP

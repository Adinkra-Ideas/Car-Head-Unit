#ifndef STEERING_HPP
#define STEERING_HPP

#include <QObject>
#include <QThread>
#include <QDebug>

#include "Props.hpp"
#include "SteeringWorker.hpp"

extern "C"
{
    #include "../src_C/apsc.h"
}

class Steering : virtual public Props
{
    QThread theThread;

public:
    explicit Steering(QObject *parent = nullptr);
    virtual ~Steering();

    void    abortThread();

    quint8  getSteering() const override;
    void    setSteering(quint8 steer) override;

protected:
    quint8          steering_;
    bool            init_;  // false if PCA9685 not yet init-ed, true if init-ed

    SteeringWorker  steeringWorker_;
};

#endif // STEERING_HPP

#ifndef STEERING_HPP
#define STEERING_HPP

#include <QObject>
#include <QThread>

#include "Props.hpp"
#include "SteeringWorker.hpp"

class Steering : virtual public Props
{
    QThread theThread;

public:
    explicit Steering(QObject *parent = nullptr);
    virtual ~Steering();

    void    abortThread();

    quint8  getSteering() const override;
    void    setSteering(quint8 steeringPos) override;

protected:
    quint8          steeringPos_;

    SteeringWorker  steeringWorker_;
};

#endif // STEERING_HPP

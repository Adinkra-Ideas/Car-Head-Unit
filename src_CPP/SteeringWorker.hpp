#ifndef STEERINGWORKER_HPP
#define STEERINGWORKER_HPP

#include <QObject>
// #include <QDebug>  //
#include <QThread> //

#include "Props.hpp"

class SteeringWorker : public QObject
{
public:
    explicit SteeringWorker(Props * instance,
                        QObject *parent = nullptr);
    ~SteeringWorker();

    void    doWork();
    void    abortThread();

private:
    Props * steeringInstance_;
    bool    abort_;
};

#endif // STEERINGWORKER_HPP

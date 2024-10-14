#ifndef GEARWORKER_HPP
#define GEARWORKER_HPP

#include <QObject>
// #include <QDebug>  //
#include <QThread> //

#include "Props.hpp" //

class GearWorker : public QObject
{
public:
    explicit GearWorker(Props * instance,
                  QObject *parent = nullptr);
    ~GearWorker();

    void    doWork();
    void    abortThread();

private:
    Props * gearInstance_;
    bool   abort_;
};

#endif // GEARWORKER_HPP

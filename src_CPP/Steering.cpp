#include "Steering.hpp"

Steering::Steering(QObject *parent) :
    Props{parent},
    steeringPos_{184},
    steeringWorker_(this)
{
    steeringWorker_.moveToThread(&theThread);
    connect(this, &Props::operateSteering, &steeringWorker_, &SteeringWorker::doWork);
    theThread.start();

    // emit operateSteering();
}

Steering::~Steering() {}

void    Steering::abortThread() {
    steeringWorker_.abortThread();
    theThread.quit();
    theThread.wait();
}

// // **************************************
// //          GETTER METHODS BEGINS       *
// // **************************************
quint8 Steering::getSteering() const {
    return steeringPos_;
}
// **************************************
//          GETTER METHODS ENDS         *
// **************************************


// **************************************
//          SETTER METHODS BEGINS       *
// **************************************
void Steering::setSteering(quint8 steeringPos) {
    steeringPos_ = steeringPos;
    emit steeringChanged();
}

#include "Steering.hpp"

Steering::Steering(QObject *parent) :
    Props{parent},
    steering_{0},
    // init_{false}, // zzz
    init_{true},
    steeringWorker_(this)
{
    steeringWorker_.moveToThread(&theThread);
    connect(this, &Props::operateSteering, &steeringWorker_, &SteeringWorker::doWork);
    theThread.start();
    
    // zzz
    // if ( ! apsc_init() ) {
    //     init_ = true;
    // }
    
    //apsc_setSteering(steer); // will be used to set lastKnownSteeringPosition

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
    return steering_;
}
// **************************************
//          GETTER METHODS ENDS         *
// **************************************


// **************************************
//          SETTER METHODS BEGINS       *
// **************************************
void Steering::setSteering(quint8 steer) {
    // If steering MPU is init-ed
    if (! init_) { return ; }
    // if (steer > APSC_MAX_BEFORE_MAPPING) { return ; }
    
    steering_ = steer;
    // apsc_setSteering(steer);
    
    emit steeringChanged();
}

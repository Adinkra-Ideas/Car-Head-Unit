#include "Gear.hpp"

Gear::Gear(QObject *parent) :
        Props{parent},
        _gear{Props::gear_},
        speed_{0},
        _mode{0},
        _init{false},
        gearWorker_(this)
{
    gearWorker_.moveToThread(&theThread);
    connect(this, &Props::operateGear, &gearWorker_, &GearWorker::doWork);
    theThread.start();

    if ( ! aptc_init() ) {
        _init = true;
    }

    // emit operateGear();
}

Gear::~Gear() {}

void    Gear::abortThread() {
    gearWorker_.abortThread();
    theThread.quit();
    theThread.wait();
}

// **************************************
//          GETTER METHODS BEGINS       *
// **************************************
quint8 Gear::getGear() const {
    return _gear;
}

quint16 Gear::getSpeed() const {
    return speed_;
}
// **************************************
//          GETTER METHODS ENDS         *
// **************************************


// **************************************
//          SETTER METHODS BEGINS       *
// **************************************
void Gear::setGear(quint8 gear) {
    // If throttle MPU is init-ed
    if (! _init) { return ; }

    _gear = gear;

    // set base speed for gear accordingly
    switch (_gear) {
        case 0: // P // use macro from lib to define cases
            setSpeed(0);
            break;
        case 1: // N
            setSpeed(0);
            break;
        case 2: // D
            setSpeed(400);
            break;
        case 3: // R
            setSpeed(400);
            break;
        default: // Unknown error
            _gear = 0; // park car if unknown error occurs
            setSpeed(0);
    }

    emit gearChanged();
}

void   Gear::setSpeed(quint16 speed) {
    // If throttle MPU is init-ed
    if (! _init) { return; }

    switch (_gear) {
        case 0: // P // use macro from lib to define cases
            speed_ = 0;
            aptc_setSpeed(speed_, APTC_FWD);
            break;
        case 1: // N // use macro from lib to define cases
            speed_ = 0;
            aptc_setSpeed(speed_, APTC_FWD);
            break;
        case 2: // D // use macro from lib to define cases
            if (speed > 4000) { return; }
            speed_ = speed;
            aptc_setSpeed(speed_, APTC_FWD);
            break;
        case 3: // R // use macro from lib to define cases
            if (speed > 700) { return; }
            speed_ = speed;
            aptc_setSpeed(speed_, APTC_BKWD);
            break;
        default: // Unknown error
            _gear = 0; // park car if unknown error occurs
            speed_ = 0;
            aptc_setSpeed(speed_, APTC_FWD);
    }

    emit speedChanged();
}

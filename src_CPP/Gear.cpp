#include "Gear.hpp"

Gear::Gear(QObject *parent) :
        Props{parent},
        _gear{Props::gear_},
        speed_{0},
        _mode{0},
        // _init{0},
        _init{1}, // for testing purpose
        gearWorker_(this)
{
    gearWorker_.moveToThread(&theThread);
    connect(this, &Props::operateGear, &gearWorker_, &GearWorker::doWork);
    theThread.start();

    // uncomment
    // // Initialize the Throttle HAL
    // if (! begin_txv() /*ready_hut_hal()*/) {

    //     if (! init_chip_on_0x60() /*init_throttle_mpu*/) {
    //         _init = 1;
    //     }

    // }

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
             // Head Unit Throttle Lib
            break;
        case 1: // N
            setSpeed(0);
            // speed_ = 0;
            // hut_setSpeed(speed_, HUT_FWD);
            break;
        case 2: // D
            setSpeed(400);
            // speed_ = 400;
            // hut_setSpeed(speed_, HUT_FWD);
            break;
        case 3: // R
            setSpeed(400);
            // speed_ = 400;
            // hut_setSpeed(speed_, HUT_BKWD);
            break;
        default: // Unknown error
            _gear = 0; // park car if unknown error occurs
            setSpeed(0);
            // speed_ = 0;
            // hut_setSpeed(speed, HUT_FWD);
    }

    emit gearChanged();
}

// for testing purpose
quint8 HUT_FWD = 0;
quint8 HUT_BKWD = 0;
static void hut_setSpeed(quint16, quint8) {}

void   Gear::setSpeed(quint16 speed) {
    // If throttle MPU is init-ed
    if (! _init) { return; }

    switch (_gear) {
        case 0: // P // use macro from lib to define cases
            speed_ = 0;
            hut_setSpeed(speed_, HUT_FWD);
            break;
        case 1: // N // use macro from lib to define cases
            speed_ = 0;
            hut_setSpeed(speed_, HUT_FWD);
            break;
        case 2: // D // use macro from lib to define cases
            if (speed > 4000) { return; }
            speed_ = speed;
            hut_setSpeed(speed_, HUT_FWD);
            break;
        case 3: // R // use macro from lib to define cases
            if (speed > 700) { return; }
            speed_ = speed;
            hut_setSpeed(speed_, HUT_BKWD);
            break;
        default: // Unknown error
            _gear = 0; // park car if unknown error occurs
            speed_ = 0;
            hut_setSpeed(speed_, HUT_FWD);
    }

    emit speedChanged();
}

// //
// void	Gear::setGearToP() {
//     // If throttle MPU is init-ed, and vehicle is at a standstill
//     if (_init && ! wheelSpeed_) {
//         p_gear_control(&_gear, &clutch_);
//         emit isGearChanged();
//     }
// }

// //
// void	Gear::setGearToN() {
//     // If throttle MPU is init-ed
//     if (_init) {
//         n_gear_control(&_gear, &clutch_);
//         emit isGearChanged();
//     }
// }

// //
// void    Gear::setGearToD() {
//     // If throttle MPU is init-ed, and vehicle is at a standstill
//     if (_init && ! wheelSpeed_) {
//         d_gear_control(&_gear, &clutch_);
//         emit isGearChanged();
//     }
// }

// //
// void	Gear::setGearToR() {
//     // If throttle MPU is init-ed, and vehicle is at a standstill
//     if (_init && ! wheelSpeed_) {
//         r_gear_control(&_gear, &clutch_);
//         emit isGearChanged();
//     }
// }


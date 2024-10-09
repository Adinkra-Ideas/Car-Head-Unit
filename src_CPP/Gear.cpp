#include "Gear.hpp"

Gear::Gear(QObject *parent) :
        Props{},
        _gear{Props::gear_},
        clutch_{0},
        wheelSpeed_{0},
        _mode{0},
        _init{0},
        _gearWorker(_gear, _mode, _init),
        QObject{parent}
{
    _gearWorker.moveToThread(&theThread);
    connect(this, &Gear::operate, &_gearWorker, &GearWorker::doWork);
    connect(&_gearWorker, &GearWorker::isGearChanged, this, &Gear::isGearChanged);

    // signals will be emitted from this in order to connect() with a method in thread
    // more connect() can be added here depending on your needs
    // Now we need to work on RPi to use the c lib grom gearHMI to manipulate speed
    // Then we can now look into putting the construct of this that calls gearHMI into the thread by manipulating the object called from main()
    theThread.start();
    
    // Initialize the Throttle HAL
    if (! begin_txv() /*ready_throttle_hal()*/) {
                
        if (! init_chip_on_0x60() /*init_throttle_mpu*/) {
            _init = 1;
        }
        
    }
    
}

Gear::~Gear() {
    theThread.quit();
    theThread.wait();
}


// **************************************
//          GETTER METHODS BEGINS       *
// **************************************
quint8 Gear::isGear() const {
    return _gear;
}

// **************************************
//          GETTER METHODS ENDS         *
// **************************************


// **************************************
//          SETTER METHODS BEGINS       *
// **************************************
void Gear::setGear(quint8 gear) {
    _gear = gear;

    emit isGearChanged();
}

//
void	Gear::setGearToP() {
    // If throttle MPU is init-ed, and vehicle is at a standstill
    if (_init && ! wheelSpeed_) {
        p_gear_control(&_gear, &clutch_);
        emit isGearChanged();
    }
}

//
void	Gear::setGearToN() {
    // If throttle MPU is init-ed
    if (_init) {
        n_gear_control(&_gear, &clutch_);
        emit isGearChanged();
    }
}

//
void    Gear::setGearToD() {
    // If throttle MPU is init-ed, and vehicle is at a standstill
    if (_init && ! wheelSpeed_) {
        d_gear_control(&_gear, &clutch_);
        emit isGearChanged();
    }
}

//
void	Gear::setGearToR() {
    // If throttle MPU is init-ed, and vehicle is at a standstill
    if (_init && ! wheelSpeed_) {
        r_gear_control(&_gear, &clutch_);
        emit isGearChanged();
    }
}


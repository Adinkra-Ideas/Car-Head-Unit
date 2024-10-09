#include "Gear.hpp"

Gear::Gear(QObject *parent) :
        Props{},
        _gear{Props::gear_},
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

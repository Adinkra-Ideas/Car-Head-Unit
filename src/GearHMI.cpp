#include "GearHMI.hpp"

GearHMI::GearHMI(QObject *parent) :
    QObject{parent},
    _gear{0},
    _mode{0},
    _init{0} {
    // init here
}

GearHMI::~GearHMI() {}

// **************************************
//          GETTER METHODS BEGINS       *
// **************************************
quint8 GearHMI::isGear() const {
    return _gear;
}
// **************************************
//          GETTER METHODS ENDS         *
// **************************************


// **************************************
//          SETTER METHODS BEGINS       *
// **************************************
void GearHMI::setIsGear(quint8 gear) {
    _gear = gear;

    emit isGearChanged();
}
// **************************************
//          SETTER METHODS ENDS         *
// **************************************

void    GearHMI::doWork() {
    _gear = 2;

    emit isGearChanged();
}

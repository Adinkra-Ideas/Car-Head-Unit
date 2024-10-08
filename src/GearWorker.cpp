#include "GearWorker.hpp"

GearWorker::GearWorker(quint8 & gear,
            quint8 & mode,
            quint8 & init,
            QObject *parent) :
    QObject{parent},
    _gear{gear},
    _mode{mode},
    _init{init} {
    // init here
}


GearWorker::~GearWorker() {}

// **************************************
//          GETTER METHODS BEGINS       *
// **************************************
quint8 GearWorker::isGear() const {
    return _gear;
}

// **************************************
//          GETTER METHODS ENDS         *
// **************************************


// **************************************
//          SETTER METHODS BEGINS       *
// **************************************
void GearWorker::setIsGear(quint8 gear) {
    _gear = gear;

    emit isGearChanged();
}
// **************************************
//          SETTER METHODS ENDS         *
// **************************************

void    GearWorker::doWork() {
    _gear = 2;

    emit isGearChanged();
}

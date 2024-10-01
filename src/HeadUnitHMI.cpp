#include "HeadUnitHMI.hpp"

HeadUnitHMI::HeadUnitHMI(GearHMI & gearHMI, QObject *parent) :
        _gearHMI{gearHMI},
        QObject{parent}
{
    _gearHMI.moveToThread(&theThread);
    connect(this, &HeadUnitHMI::operate, &_gearHMI, &GearHMI::doWork);
    // signals will be emitted from this in order to connect() with a method in thread
    // more connect() can be added here depending on your needs
    theThread.start();
}

HeadUnitHMI::~HeadUnitHMI() {
    theThread.quit();
    theThread.wait();
}

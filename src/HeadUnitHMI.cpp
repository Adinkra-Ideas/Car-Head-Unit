#include "HeadUnitHMI.hpp"

HeadUnitHMI::HeadUnitHMI(GearHMI & gearHMI, QObject *parent) :
        _gearHMI{gearHMI},
        QObject{parent}
{
    _gearHMI.moveToThread(&theThread);
    connect(this, &HeadUnitHMI::operate, &_gearHMI, &GearHMI::doWork);
    // signals will be emitted from this in order to connect() with a method in thread
    // more connect() can be added here depending on your needs
    // Now we need to work on RPi to use the c lib grom gearHMI to manipulate speed
    // Then we can now look into putting the construct of this that calls gearHMI into the thread by manipulating the object called from main()
    theThread.start();
}

HeadUnitHMI::~HeadUnitHMI() {
    theThread.quit();
    theThread.wait();
}

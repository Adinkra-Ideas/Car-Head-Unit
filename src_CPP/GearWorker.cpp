#include "GearWorker.hpp"

GearWorker::GearWorker(Props * instance,
                        QObject *parent) :
                QObject{parent},
                gearInstance_{instance},
                abort_{false} {}

GearWorker::~GearWorker() {}

void    GearWorker::abortThread() {
    abort_ = true;
}

void    GearWorker::doWork() {
    while(true && !abort_) {
        QThread::sleep(5);
        gearInstance_->setGear(2);
        // qDebug() << "gear = " << gearInstance_->getGear() ;
    }
}

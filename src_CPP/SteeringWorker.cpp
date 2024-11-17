#include "SteeringWorker.hpp"

SteeringWorker::SteeringWorker(Props * instance,
                                QObject *parent) :
                    QObject{parent},
                    steeringInstance_{instance},
                    abort_{false} {}

SteeringWorker::~SteeringWorker() {}

void    SteeringWorker::abortThread() {
    abort_ = true;
}

void    SteeringWorker::doWork() {
    while(true && !abort_) {
        QThread::sleep(5);
        steeringInstance_->setSteering(149);
        // qDebug() << "steering = " << steeringInstance_->getSteering() ;
    }
}


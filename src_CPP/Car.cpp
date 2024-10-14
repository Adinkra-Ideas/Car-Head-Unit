#include "Car.hpp"

Car::Car(QObject * parent) :
        Gear{parent},
        Steering{parent}
{}

Car::~Car() {}

void Car::safeQuitAllThreads() {
    Gear::abortThread();
    Steering::abortThread();
}

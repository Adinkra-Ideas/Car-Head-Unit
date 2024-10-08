#ifndef CAR_HPP
#define CAR_HPP

#include <QObject>

#include "Gear.hpp"

class Car : public Gear
{
public:
    explicit Car(QObject * parent = nullptr);
    ~Car();
};

#endif // CAR_HPP

#ifndef CAR_HPP
#define CAR_HPP

#include <QObject>

#include "Gear.hpp"
#include "Steering.hpp"
#include "MediaDirectory.hpp"

class Car :
            public Gear,
            public Steering,
            public MediaDirectory
{
public:
    explicit Car(QObject * parent = nullptr);
    ~Car();

    void        safeQuitAllThreads();
};

#endif // CAR_HPP

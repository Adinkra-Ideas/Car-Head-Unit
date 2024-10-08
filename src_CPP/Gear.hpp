#ifndef GEAR_HPP
#define GEAR_HPP

#include <QObject>
#include <QThread>

#include "Props.hpp"
#include "GearWorker.hpp"

class Gear : public QObject, virtual public Props
{
    Q_OBJECT
    Q_PROPERTY(quint8 isGear READ isGear WRITE setGear NOTIFY isGearChanged)
    QThread theThread;

public:
    explicit Gear(QObject *parent = nullptr);
    virtual ~Gear();

    quint8  isGear() const;
    void    setGear(quint8 gear);

signals:
    void    operate();
    void    isGearChanged();

protected:
    quint8      _gear;  // current active gear
    quint8      _mode;  // throttle value assigned to current active gear
    quint8      _init;  // 0 if PCA9685 not yet init-ed, 1 if init-ed

    GearWorker  _gearWorker;

};

#endif // GEAR_HPP

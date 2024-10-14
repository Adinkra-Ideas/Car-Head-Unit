#ifndef PROPS_HPP
#define PROPS_HPP

#include <QObject>
#include <QDebug>

class Props : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint8 gear READ getGear WRITE setGear NOTIFY gearChanged)
    Q_PROPERTY(quint16 speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(quint8 steering READ getSteering WRITE setSteering NOTIFY steeringChanged)

public:
    explicit    Props(QObject *parent = nullptr);
    virtual     ~Props() = 0;

    virtual void    safeQuitAllThreads() = 0;

    virtual quint8  getGear() const = 0;
    virtual void    setGear(quint8 gear) = 0;

    virtual quint16 getSpeed() const = 0;
    virtual void    setSpeed(quint16 speed) = 0;

    virtual quint8  getSteering() const = 0;
    virtual void    setSteering(quint8 steeringPos) = 0;

signals:
    void    operateGear();
    void    gearChanged();
    void    speedChanged();

    void    operateSteering();
    void    steeringChanged();

private:
    // Prevent all the constructors and operators below
    Props &operator=(const Props &) ;
    Props &operator=(Props &&) ;
    Props(const Props &) ;
    Props(Props &&) ;


protected:
    quint8      gear_;  // active gear
};


#endif // PROPS_HPP

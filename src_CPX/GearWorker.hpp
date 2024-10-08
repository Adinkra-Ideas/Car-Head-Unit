#ifndef GEARWORKER_HPP
#define GEARWORKER_HPP

#include <QObject>


class GearWorker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 isGear READ isGear WRITE setIsGear NOTIFY isGearChanged)
public:
    explicit GearWorker(quint8 & gear,
                  quint8 & mode,
                  quint8 & init,
                  QObject *parent = nullptr);
    ~GearWorker();

    // getters
    quint8 isGear() const;

    // setters
    void setIsGear(quint8 gear);

public slots:
    void doWork();

signals:
    void        isGearChanged();

private:
    quint8 & _gear;  // current active gear
    quint8 & _mode;  // throttle value assigned to current active gear
    quint8 & _init;  // 0 if PCA9685 not yet init-ed, 1 if init-ed
};

#endif // GEARWORKER_HPP

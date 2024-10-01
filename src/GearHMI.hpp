#ifndef GEARHMI_HPP
#define GEARHMI_HPP

#include <QObject>

class GearHMI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 isGear READ isGear WRITE setIsGear NOTIFY isGearChanged)
public:
    explicit GearHMI(QObject *parent = nullptr);
    ~GearHMI();

    // getters
    quint8 isGear() const;

    // setters
    void setIsGear(quint8 gear);

public slots:
    void doWork();

signals:
    void        isGearChanged();

private:
    quint8  _gear;  // current active gear
    quint8  _mode;  // throttle value assigned to current active gear
    quint8  _init;  // 0 if PCA9685 not yet init-ed, 1 if init-ed
};

#endif // GEARHMI_HPP

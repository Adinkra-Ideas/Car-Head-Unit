#ifndef HEADUNITHMI_HPP
#define HEADUNITHMI_HPP

#include <QObject>
#include <QThread>

#include "GearHMI.hpp"

class HeadUnitHMI : public QObject
{
    Q_OBJECT
    QThread theThread; // simply naming the thread to be spawned

public:
    explicit HeadUnitHMI(GearHMI & gearHMI, QObject *parent = nullptr);
    ~HeadUnitHMI();
    GearHMI & _gearHMI;

signals:
    void operate();
};

#endif // HEADUNITHMI_HPP

#ifndef ACTIVEGEAR_H
#define ACTIVEGEAR_H

#include <QObject>
#include <QDebug>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


class ActiveGear : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 currentGear READ getGear NOTIFY gearIsChanged)

public:
    ActiveGear(QObject *parent = nullptr);
    ~ActiveGear();

    quint8 getGear() const;

signals:
    void gearIsChanged();

protected:
    void timerEvent(QTimerEvent *event);

private:
    int                fd_; // for storing the fd of opened path_
    const char     * path_; // file path for storing the active gear so other processes can read active gear
    quint8             gear_;
    quint8         oldGear_;

    int       timerId_;
};

#endif // ACTIVEGEAR_H

#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QObject>

class Speedometer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)
    Q_PROPERTY(double newSpeed READ newSpeed WRITE setNewSpeed NOTIFY newSpeedChanged FINAL)
public:
    explicit Speedometer(QObject *parent = nullptr);
    // Getters
    int speed();
    double newSpeed();

    // Setters
    void setSpeed(int);
    void setNewSpeed(double);
    void kalmanFilter(double measuredSpeed);
    void emaFilter(double measuredSpeed);


signals:
    void speedChanged();
    void newSpeedChanged();

private:
    int m_speed;
    double m_newSpeed;
    const double TYRE_RADIUS = 3.35;
    double smoothedSpeed;
    double alpha;
    double estimatedSpeed;
    double P;
    double Q;
    double R;
    
};

#endif // SPEEDOMETER_H

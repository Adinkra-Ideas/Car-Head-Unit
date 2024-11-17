#include "Speedometer.h"
#include <QDebug>
#include <QtMath>

Speedometer::Speedometer(QObject *parent)
    : QObject{parent}, m_newSpeed(0.0), smoothedSpeed(0.0), alpha(0.9), estimatedSpeed(0.0), P(100.0), Q(15.0), R(0.5)
{}

int Speedometer::speed()
{
    return m_speed;
}

double Speedometer::newSpeed()
{
    return m_newSpeed;
}

void Speedometer::setSpeed(int newSpeed)
{
    const unsigned long sampleTime = 100;
    const int resolution = 20;    
    const double circumference = 2 * M_PI * 3.35;
    
    double rpm = ((newSpeed * 60.0) * (1000)) / (static_cast<double>(resolution) * sampleTime);
    
    double speedCmPerSec = (rpm * circumference) / 60.0;
    
    // kalmanFilter(speedCmPerSec);
    emaFilter(speedCmPerSec);
    //setNewSpeed(speedCmPerSec+30);
    // qDebug() << speedCmPerSec << "cm/s";

}

void Speedometer::kalmanFilter(double measuredSpeed)
{
    if(measuredSpeed == 0.0){
        estimatedSpeed = 0.0;
    }
    //if(measuredSpeed < estimatedSpeed){
    //    Q = 10.0;// process noise covariance - higher for faster responsiveness
    //}else{
    //    Q = 0.1;
   //     }
        
    double predictedSpeed = estimatedSpeed;
    P = P + Q;
    
    double K = P / (P + R);
    estimatedSpeed = predictedSpeed + K * (measuredSpeed - predictedSpeed);
    P = (1-K)*P;
    
    if(estimatedSpeed < 80){
        setNewSpeed(estimatedSpeed+10);
    }
    else if(estimatedSpeed < 125){
        setNewSpeed(estimatedSpeed+18);
    }
    else{
        setNewSpeed(estimatedSpeed+30);
        }
    qDebug() << estimatedSpeed << "cm/s";

}

void Speedometer::emaFilter(double measuredSpeed)
{
    
    if(measuredSpeed == 0.0){
        smoothedSpeed = 0.0;
    }else if(measuredSpeed < smoothedSpeed){
        smoothedSpeed = measuredSpeed;
    }else{
        smoothedSpeed = alpha * measuredSpeed + (1.0 - alpha) * smoothedSpeed;
        }

    if(smoothedSpeed < 80){
        setNewSpeed(smoothedSpeed+10);
    }
    else if(smoothedSpeed < 125){
        setNewSpeed(smoothedSpeed+18);
    }
    else{
        setNewSpeed(smoothedSpeed+30);
        }
    qDebug() << smoothedSpeed << "cm/s";
}

void Speedometer::setNewSpeed(double speed)
{
    if (qFuzzyCompare(m_newSpeed, speed))
        return;
    m_newSpeed = speed;
    emit newSpeedChanged();
    //qDebug() << "Hi";
}

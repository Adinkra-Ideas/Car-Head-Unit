#include "Gear.hpp"

Gear::Gear(QObject *parent) :
        Props{parent},
        _gear{Props::gear_},
        speed_{0},
        _mode{0},
        // _init{false}, // zzz
        _init{true},
        gearWorker_(this)
{
    gearWorker_.moveToThread(&theThread);
    connect(this, &Props::operateGear, &gearWorker_, &GearWorker::doWork);
    theThread.start();

    // get current user home path
    #ifdef Q_OS_WIN32
    path_ = QString(getenv("USERPROFILE"))
                   .append("\\activeGear")
                   .toLocal8Bit()
                   .constData();
    #elif defined(Q_OS_LINUX)
    if ((path_ = getenv("HOME")) == NULL) {
        path_ = getpwuid(getuid())->pw_dir;
    }
    #else
    qDebug() << "UNSUPPORTED PLATFORM!";
    #endif

    // open the file for storing active gear as text.
    // Create if not exist
    fd_ = open(path_, /*O_NONBLOCK |*/ O_RDWR | O_TRUNC | O_CREAT, 0640);
    write(fd_, "P", 1);
    lseek(fd_, 0, SEEK_SET);

    // zzz
    // if ( ! aptc_init() ) {
    //     _init = true;
    // }

    // emit operateGear();
}

Gear::~Gear() {
    // close the fd for storing active gear
    close(fd_);
    // fclose(file_);
}

void    Gear::abortThread() {
    gearWorker_.abortThread();
    theThread.quit();
    theThread.wait();
}

// **************************************
//          GETTER METHODS BEGINS       *
// **************************************
quint8 Gear::getGear() const {
    return _gear;
}

quint16 Gear::getSpeed() const {
    return speed_;
}
// **************************************
//          GETTER METHODS ENDS         *
// **************************************


// **************************************
//          SETTER METHODS BEGINS       *
// **************************************
void Gear::setGear(quint8 gear) {
    // If throttle MPU is init-ed
    if (! _init) { return ; }

    _gear = gear;

    // set base speed for gear accordingly
    switch (_gear) {
        case 0: // P // use macro from lib to define cases
            setSpeed(0);
            // store the gear to active gear file for reading by other processes
            write(fd_, "P", 1);
            lseek(fd_, 0, SEEK_SET);
            break;
        case 1: // N
            setSpeed(0);
            write(fd_, "N", 1);
            lseek(fd_, 0, SEEK_SET);
            break;
        case 2: // D
            setSpeed(400);
            write(fd_, "D", 1);
            lseek(fd_, 0, SEEK_SET);
            break;
        case 3: // R
            setSpeed(400);
            write(fd_, "R", 1);
            lseek(fd_, 0, SEEK_SET);
            break;
        default: // Unknown error
            _gear = 0; // park car if unknown error occurs
            write(fd_, "P", 1);
            lseek(fd_, 0, SEEK_SET);
            setSpeed(0);
    }

    emit gearChanged();
}

void   Gear::setSpeed(quint16 speed) {
    // If throttle MPU is init-ed
    if (! _init) { return; }

    switch (_gear) {
        case 0: // P // use macro from lib to define cases
            speed_ = 0;
            // aptc_setSpeed(speed_, APTC_FWD);
            break;
        case 1: // N // use macro from lib to define cases
            speed_ = 0;
            // aptc_setSpeed(speed_, APTC_FWD);
            break;
        case 2: // D // use macro from lib to define cases
            if (speed > 4000) { return; }
            speed_ = speed;
            // aptc_setSpeed(speed_, APTC_FWD);
            break;
        case 3: // R // use macro from lib to define cases
            if (speed > 700) { return; }
            speed_ = speed;
            // aptc_setSpeed(speed_, APTC_BKWD);
            break;
        default: // Unknown error
            _gear = 0; // park car if unknown error occurs
            speed_ = 0;
            // aptc_setSpeed(speed_, APTC_FWD);
    }

    emit speedChanged();
}

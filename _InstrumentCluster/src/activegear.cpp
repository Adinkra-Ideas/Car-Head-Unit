#include "ActiveGear.hpp"

ActiveGear::ActiveGear(QObject *parent) :
    QObject{parent} {

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

    // open the file for reading active gear as text.
    fd_ = open(path_, O_RDONLY);
    read(fd_, &gear_, 1);
    lseek(fd_, 0, SEEK_SET);

    oldGear_ = gear_;

    timerId_ = startTimer(300);
}

ActiveGear::~ActiveGear() {
    close(fd_);

    // free the timer from destructor
    killTimer(timerId_);
}

void ActiveGear::timerEvent(QTimerEvent *event) {
    read(fd_, &gear_, 1);
    lseek(fd_, 0, SEEK_SET);

    if (gear_ != oldGear_) {
        oldGear_ = gear_;
        emit gearIsChanged();
        qDebug() << "ttttttttttttt" << oldGear_;
    }
}

quint8 ActiveGear::getGear() const {
    qDebug() << "uuuuuuuuuuuuuuuuuu" << oldGear_;
    return oldGear_;
}

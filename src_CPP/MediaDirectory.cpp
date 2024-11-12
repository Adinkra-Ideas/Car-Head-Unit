#include "MediaDirectory.hpp"
#include <QDebug>

MediaDirectory::MediaDirectory(QObject *parent) :
    Props{parent}
{}

MediaDirectory::~MediaDirectory() {}

void    MediaDirectory::mp_addDir(QUrl path) {
    qDebug() << "pathhhhhhhhhhhhhh =" << path;
    // pathhhhhhhhhhhhhh = QUrl("file:///C:/Users/user/Documents/head-unit/build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug")

}

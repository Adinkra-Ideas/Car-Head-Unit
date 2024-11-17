#include "Directory.hpp"

#include <QDebug>

#ifdef Q_OS_ANDROID
bool checkPermission() {
    QList<bool> permissions;

    auto r = QtAndroidPrivate::checkPermission("android.permission.READ_EXTERNAL_STORAGE").result();
    if (r != QtAndroidPrivate::Authorized)
    {
        r = QtAndroidPrivate::requestPermission("android.permission.READ_EXTERNAL_STORAGE").result();
        if (r == QtAndroidPrivate::Denied)
            permissions.append(false);
    }
    // r = QtAndroidPrivate::checkPermission("android.permission.WRITE_EXTERNAL_STORAGE").result();
    // qDebug() << "r2" << r;
    // if (r != QtAndroidPrivate::Authorized)
    // {
    //     r = QtAndroidPrivate::requestPermission("android.permission.WRITE_EXTERNAL_STORAGE").result();
    //     qDebug() << "r20" << r;
    //     if (r == QtAndroidPrivate::Denied)
    //         permissions.append(false);
    // }
    // r = QtAndroidPrivate::checkPermission("android.permission.MANAGE_EXTERNAL_STORAGE").result();
    // qDebug() << "r3" << r;
    // if (r != QtAndroidPrivate::Authorized)
    // {
    //     r = QtAndroidPrivate::requestPermission("android.permission.MANAGE_EXTERNAL_STORAGE").result();
    //     qDebug() << "r30" << r;
    //     if (r == QtAndroidPrivate::Denied)
    //         permissions.append(false);
    // }
    // r = QtAndroidPrivate::checkPermission("android.permission.READ_MEDIA_IMAGES").result();
    // qDebug() << "r4" << r;
    // if (r != QtAndroidPrivate::Authorized)
    // {
    //     r = QtAndroidPrivate::requestPermission("android.permission.READ_MEDIA_IMAGES").result();
    //     qDebug() << "r40" << r;
    //     if (r == QtAndroidPrivate::Denied)
    //         permissions.append(false);
    // }
    // r = QtAndroidPrivate::checkPermission("android.permission.WRITE_MEDIA_IMAGES").result();
    // qDebug() << "r5" << r;
    // if (r != QtAndroidPrivate::Authorized)
    // {
    //     r = QtAndroidPrivate::requestPermission("android.permission.WRITE_MEDIA_IMAGES").result();
    //     qDebug() << "r50" << r;
    //     if (r == QtAndroidPrivate::Denied)
    //         permissions.append(false);
    // }
    return (permissions.count() != 5);
}
#endif


Directory::Directory(QObject *parent) :
    Media{parent}
{}

Directory::~Directory(){}


void    Directory::addDir(QUrl path) {

    // change path to a usable path in times
    // when FileDialog sends random file scheme.
    // "C:/Users/user/Downloads/" works in QDir
    // "file:///C:/Users/user/Downloads/" this doesnt
    // FolderDialog sends any of the two schemed randomly
    if (! path.isLocalFile()) {
        path.setScheme(QString());
        path = QUrl::fromLocalFile(path.toString());
    }

    currDir_ = path.toString() + '/';
    doAddDir();
    emit dirChanged();
}
QString Directory::getDir() const {
    return currDir_;
}


void Directory::doAddDir() {
    QDir dir(QUrl(currDir_).toLocalFile());
    QStringList mp3 = dir.entryList(QStringList() << "*.mp3", QDir::Files);
    for (QString &aMp3: mp3) {
        if (! audioPaths_.contains(currDir_ + aMp3))   // no repeat
            audioPaths_.push_back(currDir_ + aMp3);
    }
    QStringList mp4 = dir.entryList(QStringList() << "*.mp4", QDir::Files);
    for (QString &aMp4: mp4) {
        videoPaths_.push_back(currDir_ + aMp4);
    }

    audIt_ = audioPaths_.begin();
    vpIt_ = videoPaths_.begin();

    // so that after the user sets a directory
    // the interval timer can trigger the playlist
    if (audioPaths_.size()) {
        chooseActiveMedia(*audIt_);
    }

    emit audioPathsChanged();       // refresh the qml view displaying audioPaths_ as list

    // for (QString &i: audioPaths_)
    //     qDebug() << "audiolll:" << i;
}

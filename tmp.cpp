#include "Directory.hpp"

#include <QDebug>




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


#ifdef Q_OS_ANDROID
    // decode twice from %253A to %3A then to :
    path.setUrl(QUrl::fromPercentEncoding(path.toString().toLatin1()));
    path.setUrl(QUrl::fromPercentEncoding(path.toString().toLatin1()));

    qsizetype pos = QString(path.toString()).indexOf("/tree/"); // /tree/primary:
    qsizetype subPathPos = QString(path.toString()).indexOf(":", pos);
    QString subPath;
    if (subPathPos != -1) {
        subPath = QString(path.toString()).sliced(subPathPos + 1);
        if (subPath.size() > 0 && subPath.at(0) != '/')
            subPath.prepend("/");
    }

    if (QString(path.toString()).sliced(pos + 6).startsWith("primary")) // inbuilt memory contains */tree/primary*
        path.setUrl(subPath.prepend("/storage/emulated/0"));
    else
        path.setUrl(QString(path.toString()).sliced(pos + 6, subPathPos - (pos + 6)).prepend("/storage/").append(subPath)); // 6 == len("/tree/"), 9 == len("xxxx-xxxx")
    path = QUrl::fromLocalFile(path.toString());
#endif

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

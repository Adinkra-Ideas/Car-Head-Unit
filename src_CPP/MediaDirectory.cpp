#include "MediaDirectory.hpp"
#include <QDebug>

MediaDirectory::MediaDirectory(QObject *parent) :
    Props{parent}
{}

MediaDirectory::~MediaDirectory() {}

void    MediaDirectory::mp_addDir(QUrl path) {
    // change path to a usable path in times
    // when FileDialog sends random file scheme.
    if (! path.isLocalFile()) {
        path.setScheme(QString());
        path = QUrl::fromLocalFile(path.toString());
    }

    // backup directory tree
    mp_currDir_ = path.toString() + '/';

    // filter only the .mp3 files in the selected directory
    QDir dir(QUrl(mp_currDir_).toLocalFile());
    QStringList mp3 = dir.entryList(QStringList() << "*.mp3", QDir::Files);
    for (QString & aMp3: mp3) {
        if (! mp_audioPaths_.contains(mp_currDir_ + aMp3))   // no repeat
            mp_audioPaths_.push_back(mp_currDir_ + aMp3);
    }

    mp_audIt_ = mp_audioPaths_.begin();

    // so that after the user sets a directory
    // the interval timer can trigger the playlist
    if (mp_audioPaths_.size()) {
        mp_chooseActiveMedia(*mp_audIt_);
    }

    // refresh the directory lists under Audio page
    emit audioPathsChanged();
}




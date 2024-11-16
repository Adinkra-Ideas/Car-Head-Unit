#include "Props.hpp"
#include "QDebug"

Props::Props(QObject *parent) :
            QObject{parent},
            gear_{0},
            mp_repeat_{0}
{}

Props::~Props() {
}

void Props::mp_playHasChanged(QMediaPlayer::PlaybackState newState) {
    // This part prevents the qml dependencies that
    // hides onQMediaPlayer::StoppedState to not hide
    // after one song ends, before the next song start.
    // firing out the emit, when audioPaths_
    // didnt reach end track but only current
    // track ended, will cause the QML to be
    // erratic in the parts that uses
    // player_->stop() to hide their parts
    // ALSO: we will add a check to check repeat
    // and act to either play again, play next, or do nothing
    if (mp_audioPaths_.size()
        && newState == QMediaPlayer::StoppedState) {
        if (mp_repeat_ == 1
            && mp_audioPaths_.contains(*mp_audIt_)) {
            mp_player_->setPosition(0);
            mp_setAudio(QMediaPlayer::PlayingState);
        } else if (mp_repeat_ == 2) {                   // if repeat all
            mp_changePlay(true);
        } else {
            // Dont let Qml dependencies hide their
            // stuffs onStop and then show it again
            // when next track begins, leading to
            // a GUI blink
            mp_setAudio(QMediaPlayer::StoppedState);
            mp_setAudio(QMediaPlayer::PausedState);
        }
    }

    emit mp_playingChanged();
}

// this gets called after clicking play,
// right before the song starts playing
void Props::mp_refreshMetadata() {
    // // get filename if audio
    // // same will be done for video part using same activeFilename_
    // // so that the name can be gotten whether video or audio
    qsizetype pos = (*mp_audIt_).lastIndexOf("/", -1); // CONTINUE FROM HERE. WE NEED TO FIX PLAYING PAGE
    mp_activeFilename_ = (*mp_audIt_).sliced(pos + 1);

    QMediaMetaData tmp = mp_player_->metaData();

    mp_author_ = tmp.value(QMediaMetaData::Author);
    if (mp_author_.isNull()) mp_author_ = tmp.value(QMediaMetaData::Comment);
    if (mp_author_.isNull()) mp_author_ = tmp.value(QMediaMetaData::Description);
    if (mp_author_.isNull()) mp_author_ = tmp.value(QMediaMetaData::Publisher);
    if (mp_author_.isNull()) mp_author_ = tmp.value(QMediaMetaData::Copyright);
    if (mp_author_.isNull()) mp_author_ = tmp.value(QMediaMetaData::Url);
    if (mp_author_.isNull()) mp_author_ = tmp.value(QMediaMetaData::AlbumArtist);
    if (mp_author_.isNull()) mp_author_ = QVariant(tr("Unknown"));

    mp_title_ = tmp.value(QMediaMetaData::Title);
    if (mp_title_.isNull()) mp_title_ = mp_activeFilename_;

    emit mp_mmetaDataChanged();
}

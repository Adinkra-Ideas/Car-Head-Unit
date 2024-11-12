#include "Props.hpp"
#include "QDebug"

Props::Props(QObject *parent) :
            QObject{parent},
            gear_{0},
            mp_repeat_{0}
{
    // Initialize the mediaplayer
    mp_player_ = new QMediaPlayer;
    mp_audioOutput_ = new QAudioOutput;
    mp_player_->setAudioOutput(mp_audioOutput_);
    mp_audioOutput_->setVolume(50);

    // Connect the mediaplayer's signals to the methods to manage what happens
    connect(mp_player_, &QMediaPlayer::playbackStateChanged, this, &Props::mp_playHasChanged);
    connect(mp_player_, &QMediaPlayer::metaDataChanged, this, &Props::mp_refreshMetadata);

    // set iterator accordingly
    mp_audIt_ = mp_audioPaths_.begin();

}

Props::~Props() {
    delete mp_player_;
    delete mp_audioOutput_;
}

void Props::mp_playHasChanged(QMediaPlayer::PlaybackState newState) {
    // changePlay(true);
    // return ;
    // // This part prevents the qml dependencies that
    // // hides onQMediaPlayer::StoppedState to not hide
    // // after one song ends, before the next song start.
    // // firing out the emit, when audioPaths_
    // // didnt reach end track but only current
    // // track ended, will cause the QML to be
    // // erratic in the parts that uses
    // // player_->stop() to hide their parts
    // // ALSO: we will add a check to check repeat
    // // and act to either play again, play next, or do nothing
    // if (audioPaths_.size()
    //     && newState == QMediaPlayer::StoppedState) {
    //     if (repeat_ == 1
    //         && audioPaths_.contains(*audIt_)) {   // wrong! we're dereferencing *audit without first checking if the vector is empty
    //         player_->setPosition(0);
    //         setAudio(QMediaPlayer::PlayingState);
    //     } else if (repeat_ == 2) { // if repeat all
    //         changePlay(true);
    //     } else {
    //         // Dont let Qml dependencies hide their
    //         // stuffs onStop and then show it again
    //         // when next track begins, leading to
    //         // a GUI blink
    //         setAudio(QMediaPlayer::StoppedState);
    //         setAudio(QMediaPlayer::PausedState);
    //     }
    // }

    // emit playingChanged();
    // // refresh the qml view displaying audioPaths_ as list
    // emit audioPathsChanged();
}

// this gets called after clicking play,
// right before the song starts playing
void Props::mp_refreshMetadata() {
    // // get filename if audio
    // // same will be done for video part using same activeFilename_
    // // so that the name can be gotten whether video or audio
    // qsizetype pos = (*audIt_).lastIndexOf("/", -1);
    // activeFilename_ = (*audIt_).sliced(pos + 1);

    // QMediaMetaData tmp = player_->metaData();

    // author_ = tmp.value(QMediaMetaData::Author);
    // if (author_.isNull())
    //     author_ = tmp.value(QMediaMetaData::Comment);
    // if (author_.isNull())
    //     author_ = tmp.value(QMediaMetaData::Description);
    // if (author_.isNull())
    //     author_ = tmp.value(QMediaMetaData::Publisher);
    // if (author_.isNull())
    //     author_ = tmp.value(QMediaMetaData::Copyright);
    // if (author_.isNull())
    //     author_ = tmp.value(QMediaMetaData::Url);
    // if (author_.isNull())
    //     author_ = tmp.value(QMediaMetaData::AlbumArtist);
    // if (author_.isNull())
    //     author_ = QVariant(tr("Unknown"));

    // title_ = tmp.value(QMediaMetaData::Title);
    // if (title_.isNull())
    //     title_ = activeFilename_;
    // emit mmetaDataChanged();
}

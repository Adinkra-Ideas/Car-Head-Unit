#include "Media.hpp"

Media::Media(QObject *parent) :
    Props{parent}
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

Media::~Media() {
    delete mp_player_;
    delete mp_audioOutput_;
}


/**
  * Function called to set a new Active
  * media path for both Audio and Video.
  * But it wont play the new path until
  * setAudio(QMediaPlayer::PlayingState);
  * is called.
  * Calling this function also sets STOP
  * to the currently Active playing.
  * This should be the ONLY function where
  * QMediaPlayer::setSource() should be
  * called in the whole program.
  * @param path is the absolute filepath
  * of the media to be played.
  * @returns void
  */
void Media::mp_chooseActiveMedia(QString path) {
    qsizetype pos = mp_audioPaths_.indexOf(path);

    if (pos != -1) {
        mp_setAudio(QMediaPlayer::StoppedState);
        mp_audIt_ = mp_audioPaths_.begin() + pos;
        mp_player_->setSource(*mp_audIt_);
    }
    qDebug() << "fffffffffffffffffffffffffffff" << path;
}

/**
  * Sets the current Active media to
  * Pause, Play or Stop.
  * This should be the only function
  * where QMediaPlayer::play(),
  * QMediaPlayer::pause() and
  * QMediaPlayer::stop() should be
  * called in the whole program.
  * @param newState is the playing
  * state that should be set to the
  * current Active media
  * @returns void
  */
void Media::mp_setAudio(QMediaPlayer::PlaybackState newState) {
    if (mp_audioPaths_.size()
        && mp_audioPaths_.contains(*mp_audIt_)) {
        if (newState == QMediaPlayer::PlayingState) {
            mp_player_->play();
        }
        else if (newState == QMediaPlayer::PausedState) {
            mp_player_->pause();
        }
        else if (newState == QMediaPlayer::StoppedState) {
            mp_player_->stop();
        }
    }
}

QMediaPlayer::PlaybackState Media::mp_getAudio() const {
    return mp_player_->playbackState();
}


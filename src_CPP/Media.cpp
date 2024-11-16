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

void    Media::mp_setRepeat(quint8 val) {
    mp_repeat_ = val;
    emit mp_repeatChanged();
}
quint8  Media::mp_getRepeat() {
    return mp_repeat_;
}
QString Media::mp_getTitle() {
    return mp_title_.toString();
}
QString Media::mp_getAuthor() {
    return mp_author_.toString();
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


/**
  * Moves to next or previous sound on the audio list.
  * @param move, if true, sound forwards to next,
  * if false, will be previous
  * @returns void
  */
void Media::mp_changePlay(bool move) {
    // didnt use audIt_ != audItRealBegin_ coz
    // Qlist begin() is never the same

    // if last, stop
    // if not last, next
    if (move && mp_audioPaths_.size()) { // fwd
        if (*mp_audIt_ == mp_audioPaths_.last()
            && mp_repeat_ == 2) {
            mp_audIt_ = mp_audioPaths_.begin();
        } else if (*mp_audIt_ != mp_audioPaths_.last()) {
            ++mp_audIt_;
        }
        mp_chooseActiveMedia(*mp_audIt_);
        mp_setAudio(QMediaPlayer::PlayingState);
    } else if (!move && mp_audioPaths_.size()) { // bkwd
        if (*mp_audIt_ != mp_audioPaths_.first()) {
            qsizetype pos = mp_audioPaths_.indexOf(*mp_audIt_);
            if (pos != -1 && pos != 0) {
                // I know its because I did not properly plan my DRY right from the onset
                mp_audIt_ = mp_audioPaths_.begin();
                mp_chooseActiveMedia(*mp_audIt_);
                mp_setAudio(QMediaPlayer::PlayingState);

                mp_audIt_ = mp_audioPaths_.begin() + (pos - 1);
            }
        }
        mp_chooseActiveMedia(*mp_audIt_);
        mp_setAudio(QMediaPlayer::PlayingState);
    }
}

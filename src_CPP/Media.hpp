#ifndef MEDIA_HPP
#define MEDIA_HPP

#include "Props.hpp"

class Media : virtual public Props
{
public:
    explicit Media(QObject *parent = nullptr);
    virtual ~Media();

    void mp_chooseActiveMedia(QString path) override;
    void mp_setAudio(QMediaPlayer::PlaybackState newState) override;
    QMediaPlayer::PlaybackState mp_getAudio() const override;
};

#endif // MEDIA_HPP

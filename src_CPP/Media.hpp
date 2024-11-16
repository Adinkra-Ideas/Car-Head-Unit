#ifndef MEDIA_HPP
#define MEDIA_HPP

#include "Props.hpp"

class Media : virtual public Props
{
public:
    explicit Media(QObject *parent = nullptr);
    virtual ~Media();

    void    mp_setRepeat(quint8 val) override;
    quint8  mp_getRepeat() override;
    QString mp_getTitle() override;
    QString mp_getAuthor() override;
    void mp_setAudio(QMediaPlayer::PlaybackState newState) override;
    QMediaPlayer::PlaybackState mp_getAudio() const override;

    void mp_chooseActiveMedia(QString path) override;
    void mp_changePlay(bool move) override;
};

#endif // MEDIA_HPP

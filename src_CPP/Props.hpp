#ifndef PROPS_HPP
#define PROPS_HPP

#include <QObject>
#include <QDebug>
#include <QAudioOutput> /*** ***/
#include <QMediaPlayer> /*** ***/
#include <QStringList>  /*** ***/
#include <QString>      /*** ***/
#include <QUrl>         /*** ***/
#include <QVariant>         /*** ***/
#include <QQmlListProperty> /*** ***/
#include <QMediaMetaData>   /*** ***/
#include <Qt>               /*** ***/

class Props : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 gear READ getGear WRITE setGear NOTIFY gearChanged)
    Q_PROPERTY(quint16 speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(quint8 steering READ getSteering WRITE setSteering NOTIFY steeringChanged)

    /****************** For the Media Parts ***************************/
    Q_PROPERTY(QMediaPlayer::PlaybackState mp_audio READ mp_getAudio WRITE mp_setAudio NOTIFY mp_playingChanged) // rename to getCurrAudio
    Q_PROPERTY(QStringList mp_audiopaths READ mp_getAudioPaths WRITE mp_setAudioPaths NOTIFY mp_audioPathsChanged)
    Q_PROPERTY(QString mp_activeMedia WRITE mp_chooseActiveMedia)
    Q_PROPERTY(bool mp_change WRITE mp_changePlay NOTIFY mp_playingChanged) // prevOrNext
    Q_PROPERTY(quint8 mp_repeat READ mp_getRepeat WRITE mp_setRepeat NOTIFY mp_repeatChanged)
    Q_PROPERTY(QString mp_title READ mp_getTitle NOTIFY mp_mmetaDataChanged)
    Q_PROPERTY(QString mp_author READ mp_getAuthor NOTIFY mp_mmetaDataChanged)


public:
    explicit    Props(QObject *parent = nullptr);
    virtual     ~Props() = 0;

    virtual void    safeQuitAllThreads() = 0;

    virtual quint8  getGear() const = 0;
    virtual void    setGear(quint8 gear) = 0;

    virtual quint16 getSpeed() const = 0;
    virtual void    setSpeed(quint16 speed) = 0;

    virtual quint8  getSteering() const = 0;
    virtual void    setSteering(quint8 steer) = 0;

    /////////////////////////////////////////////////////
    void mp_playHasChanged(QMediaPlayer::PlaybackState newState);
    void mp_refreshMetadata();

    /****************** For the Media Parts ***************************/
    // implemented in MediaDirectory.cpp
    virtual QStringList mp_getAudioPaths() = 0;
    virtual void    mp_setAudioPaths(QStringList path) = 0;
    // implemented in Media.cpp
    virtual void mp_chooseActiveMedia(QString path) = 0;
    virtual void mp_setAudio(QMediaPlayer::PlaybackState newState) = 0;
    virtual QMediaPlayer::PlaybackState mp_getAudio() const = 0;
    virtual void mp_changePlay(bool move) = 0;
    virtual void    mp_setRepeat(quint8 val) = 0;
    virtual quint8  mp_getRepeat() = 0;
    virtual QString mp_getTitle() = 0;
    virtual QString mp_getAuthor() = 0;

    /////////////////////////////////////////////////////

signals:
    void    operateGear();
    void    gearChanged();
    void    speedChanged();
    void    operateSteering();
    void    steeringChanged();

    /****************** For the Media Parts ***************************/
    void    mp_audioPathsChanged();
    void    mp_playingChanged();
    void    mp_repeatChanged();
    void    mp_mmetaDataChanged();

private:
    // Prevent all the constructors and operators below
    Props &operator=(const Props &) ;
    Props &operator=(Props &&) ;
    Props(const Props &) ;
    Props(Props &&) ;


protected:
    quint8      gear_;  // active gear

    /****************** For the Media Parts ***************************/
    QMediaPlayer          * mp_player_;
    QAudioOutput     * mp_audioOutput_;
    QStringList         mp_audioPaths_; // holds all the mp3 files found in directory selected by the user for media search
    QStringList::iterator    mp_audIt_; // iterator to audioPaths_
    QString                mp_currDir_; // Dir selected by the user, from where media files was last added
    QString         mp_activeFilename_; // filename being played. could be a video or audio
    QVariant                mp_author_; // Holds the Author metadata for active media
    QVariant                 mp_title_; // Holds the Title metadata for active media
    quint8                  mp_repeat_; // 0 == repeat none, 1 == repeat 1, 2 == repeat all
};

#endif // PROPS_HPP

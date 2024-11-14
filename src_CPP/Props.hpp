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
    /*** ***/
    Q_PROPERTY(QMediaPlayer::PlaybackState mp_audio READ mp_getAudio WRITE mp_setAudio NOTIFY playingChanged) // rename to getCurrAudio
    Q_PROPERTY(QString mp_currDir WRITE mp_addDir)
    Q_PROPERTY(QStringList mp_audiopaths READ mp_getAudioPaths NOTIFY audioPathsChanged)
    Q_PROPERTY(QString mp_activeMedia WRITE mp_chooseActiveMedia)
    // Q_PROPERTY(bool change WRITE changePlay NOTIFY playingChanged) // prevOrNext
    // Q_PROPERTY(QString title READ getTitle NOTIFY mmetaDataChanged)
    // Q_PROPERTY(QString author READ getAuthor NOTIFY mmetaDataChanged)
    // Q_PROPERTY(quint8 repeat READ getRepeat WRITE setRepeat NOTIFY repeatChanged)

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

    virtual void    mp_addDir(QUrl path) = 0;

    virtual void mp_chooseActiveMedia(QString path) = 0;
    virtual void mp_setAudio(QMediaPlayer::PlaybackState newState) = 0;
    virtual QMediaPlayer::PlaybackState mp_getAudio() const = 0;
    // void appStateChanged(Qt::ApplicationState state);



    // virtual QString getDir() const = 0;
    // virtual void    changePlay(bool move) = 0;
    // QString getTitle();
    // QString getAuthor();
    QStringList mp_getAudioPaths();
    // void    setRepeat(quint8 val);
    // quint8  getRepeat();
    /////////////////////////////////////////////////////

signals:
    void    operateGear();
    void    gearChanged();
    void    speedChanged();

    void    operateSteering();
    void    steeringChanged();

    void playingChanged();  //  continue from all the methods that emits this
    // void dirChanged();
    // void mmetaDataChanged();
    void audioPathsChanged();
    // void thePrintout();
    // void repeatChanged();
    // void startrThread();

private:
    // Prevent all the constructors and operators below
    Props &operator=(const Props &) ;
    Props &operator=(Props &&) ;
    Props(const Props &) ;
    Props(Props &&) ;


protected:
    quint8      gear_;  // active gear

    QMediaPlayer     * mp_player_;
    QAudioOutput     * mp_audioOutput_;
    QStringList         mp_audioPaths_;    // holds all the mp3 files found in directory selected by the user for media search
    QStringList::iterator    mp_audIt_;  // iterator to audioPaths_
    // QStringList           videoPaths_;
    // QStringList::iterator       vpIt_; // iterator to videoPaths_
    QString                mp_currDir_;  // Dir selected by the user, from where media files was last added
    // QString           activeFilename_; // filename being played. could be a video or audio
    // QVariant                  author_; // Holds the Author metadata for active media
    // QVariant                   title_; // Holds the Title metadata for active media
    quint8                  mp_repeat_; // 0 == repeat none, 1 == repeat 1, 2 == repeat all
};


#endif // PROPS_HPP

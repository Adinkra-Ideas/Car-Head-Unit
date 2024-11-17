#ifndef MEDIADIRECTORY_HPP
#define MEDIADIRECTORY_HPP

#include <QUrl>
#include <QDir>

#include "Props.hpp"

class MediaDirectory : virtual public Props
{
public:
    explicit MediaDirectory(QObject *parent = nullptr);
    virtual ~MediaDirectory();

    QStringList mp_getAudioPaths() override;
    void        mp_setAudioPaths(QStringList path) override;

private:
    void    doAddDir();
};

#endif // MEDIADIRECTORY_HPP

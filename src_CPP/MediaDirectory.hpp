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

    void    mp_addDir(QUrl path) override;

private:
    void    doAddDir();
};

#endif // MEDIADIRECTORY_HPP

#ifndef PROPS_HPP
#define PROPS_HPP

#include <QObject>

class Props
{
public:
    Props();
    virtual ~Props() = 0;

private:
    // Prevent all the constructors and operators below
    Props &operator=(const Props &) ;
    Props &operator=(Props &&) ;
    Props(const Props &) ;
    Props(Props &&) ;


protected:
    quint8      gear_;  // active gear
};


#endif // PROPS_HPP

#ifndef REFCONNECTOR_H
#define REFCONNECTOR_H

#include <QObject>
#include <iostream>
#include "macro.h"

class Test: public QObject {

    Q_OBJECT

    FUNC_MACRO(One)
//    FUNC_MACRO(Two)

public:

    Test()
    {
        std::cout << "Test instance created with addr: " << this << std::endl;
    }

    ~Test()
    {
        std::cout << "Test instance destroyed. Addr: " << this << std::endl;
    }

    enum Value: unsigned char{
        FirstValue,
        SecondValue
    };

    typedef void (Test::*functionPointer)();
    functionPointer signalPointer;
    functionPointer getSignal(Value value);
    void call();

signals:
//    void signalOne();
//    void signalTwo();
//    void boolSignal(bool);

};

#endif // REFCONNECTOR_H

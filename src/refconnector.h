#ifndef REFCONNECTOR_H
#define REFCONNECTOR_H

#include <QObject>

class Test: public QObject {
Q_OBJECT

public:

    enum Value: unsigned char{
        FirstValue,
        SecondValue
    };

    typedef void (Test::*functionPointer)();
    typedef void (Test::*boolFunctionPointer)(bool);
    functionPointer signalPointer;
    functionPointer getSignal(Value value);
    void call();

signals:
    void signalOne();
    void signalTwo();
    void boolSignal(bool);

};

#endif // REFCONNECTOR_H

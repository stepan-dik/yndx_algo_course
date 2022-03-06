#include "refconnector.h"


void Test::call() {
    emit (this->*signalPointer)();
//    emit (this->getSignal(Value::FirstValue));
}

Test::functionPointer Test::getSignal(Value value){
//    switch (value){
//        case FirstValue: return &Test::signalOne;
//        case SecondValue: return &Test::signalTwo;
//    }
    return &Test::signalOne;
}

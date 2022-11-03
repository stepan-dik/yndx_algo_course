#ifndef RPCMETHOD_H
#define RPCMETHOD_H

#include <QObject>
#include <QVariant>
#include "reqtypes.h"

class RpcMethod
{
    Q_GADGET

public:
    enum Value : unsigned char {
        Invalid = 0,
        GenerateTempCode,
        Register,
        Authorize,
        RequestMenu,
        RequestImage,
        RequestTheme,
        CreateOrder,
        RemainingAmountsChanged,
    };
    Q_ENUM(Value)

    RpcMethod() = default;
    constexpr RpcMethod(Value m) : val(m) {}

    operator Value() const {return val;}
    explicit operator bool() = delete;

    operator QString() {return toString();}

    const QString method() {
        return methods.value(val).name();
    }

    static const RpcMethod fromMethod(const QString name) {
        return methods.key(getByName(name), Invalid);
    }

    static const RpcMethod fromString(const QString name) {
        return QVariant(name).value<Value>();
    }

    bool isInbound() {
        return methods.value(val).isInbound();
//        switch (val) {
//            case Invalid:                   return false;
//            case GenerateTempCode:          return false;
//            case Register:                  return false;
//            case Authorize:                 return false;
//            case RequestMenu:               return false;
//            case RequestImage:              return false;
//            case RequestTheme:              return false;
//            case CreateOrder:               return false;
//            case RemainingAmountsChanged:   return true;
//        }
        return false;
    }

    bool isNotification() {
        switch (val) {
            case Invalid:                   return false;
            case GenerateTempCode:          return false;
            case Register:                  return false;
            case Authorize:                 return false;
            case RequestMenu:               return false;
            case RequestImage:              return false;
            case RequestTheme:              return false;
            case CreateOrder:               return false;
            case RemainingAmountsChanged:   return true;
        }
        return false;
    }

    bool hasParams() {
        switch (val) {
            case Invalid:                   return false;
            case GenerateTempCode:          return false;
            case Register:                  return true;
            case Authorize:                 return true;
            case RequestMenu:               return false;
            case RequestImage:              return true;
            case RequestTheme:              return false;
            case CreateOrder:               return true;
            case RemainingAmountsChanged:   return true;
        }
        return false;
    }

    bool hasResult() {
        switch (val) {
            case Invalid:                   return false;
            case GenerateTempCode:          return true;
            case Register:                  return true;
            case Authorize:                 return true;
            case RequestMenu:               return true;
            case RequestImage:              return true;
            case RequestTheme:              return true;
            case CreateOrder:               return true;
            case RemainingAmountsChanged:   return false;
        }
        return false;
    }

    bool hasErrorSignal(){
        switch (val) {
            case Invalid:                   return false;
            case GenerateTempCode:          return false;
            case Register:                  return false;
            case Authorize:                 return false;
            case RequestMenu:               return true;
            case RequestImage:              return true;
            case RequestTheme:              return true;
            case CreateOrder:               return true;
            case RemainingAmountsChanged:   return false;
        }
        RpcMethod(val).hasResult();
        return false;
    }

    bool isValid() {
        if (val == Invalid) {
            return false;
        }
        return true;
    }

    const QString toString() const {
        return QVariant::fromValue(val).toString();
    }

private:
    Value val;
    static ReqType getByName(QString name) {
        for (auto akey: methods.keys()){
            if (methods[akey].name() == name)
                return methods[akey];
        }
        return ReqType();
    }
    static const QMap<Value, ReqType> methods;
};

#endif // RPCMETHOD_H

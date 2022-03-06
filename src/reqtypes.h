#ifndef REQTYPES_H
#define REQTYPES_H

#include <QVariant>
#include <QJsonObject>

class ReqType
{

public:
    ReqType(QString name, QMap<QString, bool> data,
                     QMap<QString, QList<QJsonValue::Type>> fieldTypes){
        m_name = name;
        m_isInbound = data.value("isInbound");
        m_isNotification = data.value("isNotification");
        m_hasResult = data.value("isResult");
        m_hasParams = data.value("isParams");
        m_hasErrorSignal = data.value("hasErrorSignal");
        m_allowedFieldTypes = fieldTypes;
        m_isValid = true;
    }

    ReqType(){
        m_name = "";
        m_isInbound = false;
        m_hasResult = false;
        m_hasParams = false;
        m_isNotification = false;
        m_hasErrorSignal = false;
        m_isValid = false;
    }

    inline bool operator==(const ReqType& other) const {
        return name() == other.name();
    }

    inline QString name() const {return m_name;}
    inline bool isInbound() const {return m_isInbound;}
    inline bool isNotification() const {return m_isNotification;}
    inline bool hasResult() const {return m_hasResult;}
    inline bool hasParams() const {return m_hasParams;}
    inline bool hasErrorSignal() const {return m_hasErrorSignal;}
    inline QStringList fields() const {return m_allowedFieldTypes.keys();}
    inline QList<QJsonValue::Type> allowedTypes(QString field) const {
        return m_allowedFieldTypes[field];}

private:
    QString m_name;
    bool m_isInbound;
    bool m_isNotification;
    bool m_hasResult;
    bool m_hasParams;
    bool m_hasErrorSignal;
    bool m_isValid;
    QMap<QString, QList<QJsonValue::Type>> m_allowedFieldTypes;
};

#endif // REQTYPES_H

#include "rpcmethod.h"

const QMap<RpcMethod::Value, ReqType> RpcMethod::methods = {
    {
        Invalid,
        ReqType()
    },
    {
        RequestMenu,
        ReqType("GetDirectory",
        {
            {"isInbound", false},
            {"isNotification", false},
            {"hasParams", false},
            {"hasResult", true},
            {"hasErrorSignal", true},
        },
        {{}})
    },
    {
        RequestImage,
        ReqType("GetImageById",
        {
            {"isInbound", false},
            {"isNotification", false},
            {"hasParams", false},
            {"hasResult", true},
            {"hasErrorSignal", true},
        },
        {
            {"asd", {QJsonValue::Bool, QJsonValue::Null}}
        }
        )
    },
//    {RequestTheme,            "GetTheme"                },
//    {CreateOrder,             "CreateOrder"             },
//    {RemainingAmountsChanged, "RemainingAmountsChanged" },
//    {GenerateTempCode,        "GenerateTempCode"        },
//    {Register,                "Register"                },
//    {Authorize,               "Authorize"               },
};

#include "serialize.h"

// {
//     "status" : 200,
//     "data" : {
//             "user" :
//                 {
//                     "id" : 1,
//                     "user_name" : "uos",
//                     "nickname" : "雨夜之光",
//                     "type" : 0,
//                     "email" : "hqh2010_9@163.com",
//                     "status" : "active",
//                     "avatar" : "http://127.0.0.1:3000/static/imgs/avatar/user1/uos.jpg",
//                     "create_at" : 1678694531
//                 },
//             "token" : "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6MSwidXNlcm5hbWUiOiJ1b3MiLCJhdXRob3JpdHkiOjAsImV4cCI6MTY3OTcxMTMxMCwiaXNzIjoibWFsbCJ9.IDaawr3R3YglvSZvLq_SsDuZsAl3r0Ajw6UFYaVIRv8"
//     },
//     "msg" : "ok",
//     "error" : ""
// }

namespace utils
{
    int load_from_json(const QString &jsonString, UserInfo &user)
    {
        QString err;
        QJsonParseError parseJsonErr;
        QJsonDocument document = QJsonDocument::fromJson(jsonString.toUtf8(), &parseJsonErr);
        if (QJsonParseError::NoError != parseJsonErr.error)
        {
            err = "parse server's json data failed";
            qCritical() << err;
            return -1;
        }

        QJsonObject jsonObject = document.object();
        if (jsonObject.size() == 0)
        {
            err = "query failed, receive data is empty";
            qCritical().noquote() << jsonString;
            return -1;
        }

        if (!jsonObject.contains("status") || !jsonObject.contains("data"))
        {
            err = "receive data format err";
            qCritical().noquote() << jsonString;
            return -1;
        }

        int code = jsonObject["status"].toInt();
        if (code != 200)
        {
            err = "app not found in repo";
            qCritical().noquote() << jsonString;
            return -1;
        }
        QJsonObject dataObj = jsonObject["data"].toObject();
        if (dataObj.contains("user"))
        {
            QJsonObject userObj = dataObj["user"].toObject();
            user.id = userObj["id"].toInt();
            user.user_name = userObj["user_name"].toString();
            user.nickname = userObj["nickname"].toString();
            user.email = userObj["email"].toString();
            user.avatar = userObj["avatar"].toString();
            if (dataObj.contains("token"))
            {
                user.token = dataObj["token"].toString();
            }
            return 0;
        }
        return -1;
    }
}

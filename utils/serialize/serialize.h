#ifndef UTILS_SERIALIZE_SERIALIZE_H_
#define UTILS_SERIALIZE_SERIALIZE_H_

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "model/data/data_def.h"

// https://blog.51cto.com/u_15045304/5963635
// 第三方库　https://github.com/flavio/qjson
// https://qjson.sourceforge.net/
namespace utils
{
    int load_from_json(const QString &jsonString, UserInfo &user, QString &err_info);
}
#endif
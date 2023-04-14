#ifndef UTILS_COMMON_COMMON_H_
#define UTILS_COMMON_COMMON_H_

#include <QFileInfo>

namespace utils
{
    bool inline fileExists(const QString &path);

    int getLocalConfig(const QString &key, QString &value);
}
#endif

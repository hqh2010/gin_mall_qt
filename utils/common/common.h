#ifndef UTILS_COMMON_COMMON_H_
#define UTILS_COMMON_COMMON_H_

#include <QFileInfo>
#include <QDir>

namespace utils
{
    bool fileExists(const QString &path);

    bool createDir(const QString &path);

    int getLocalConfig(const QString &key, QString &value);
}
#endif

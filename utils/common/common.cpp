
#include "common.h"

#include <QSettings>

const QString SERVER_CFG_PATH = "/home/uthuqinghong/Desktop/gin-mall-qt/gin_mall_qt/misc/conf/config";

namespace utils
{
    bool fileExists(const QString &path)
    {
        QFileInfo fs(path);
        return fs.exists() && fs.isFile() ? true : false;
    }

    int getLocalConfig(const QString &key, QString &value)
    {
        if (!fileExists(SERVER_CFG_PATH))
        {
            return -1;
        }

        QSettings *cfg = new QSettings(SERVER_CFG_PATH, QSettings::IniFormat);
        cfg->beginGroup("service");
        value = cfg->value(key).toString();
        cfg->endGroup();
        delete cfg;
        return 0;
    }
}

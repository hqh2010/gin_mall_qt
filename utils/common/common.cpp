
#include "common.h"

#include <QSettings>

// 调试时可以使用项目代码库中的配置文件
const QString SERVER_CFG_PATH = "/etc/gin-mall-qt-client/config";

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

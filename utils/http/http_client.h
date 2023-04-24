#ifndef UTILS_HTTP_HTTP_CLIENT_H_
#define UTILS_HTTP_HTTP_CLIENT_H_

#include <QNetworkReply>
#include <QNetworkRequest>

#include "utils/singleton/singleton.h"
#include "model/data/data_def.h"

namespace utils
{
    QNetworkAccessManager &networkMgr();

    class HttpRestClient : public Singleton<HttpRestClient>
    {
    public:
        HttpRestClient();

        void post_test();
        void post_test2();

        int download_img(const QString &url, QByteArray &image);
        bool get(QNetworkRequest &request, QString &outMsg);
        int post(int action, QMap<QString, QString> mapData, QString &outMsg, QString& err_info);
        bool put(QNetworkRequest &request, const QByteArray &data, QString &outMsg);
        bool put(QNetworkRequest &request, QHttpMultiPart *multiPart, QString &outMsg);
        // QNetworkReply *del(QNetworkRequest &request);
        bool del(QNetworkRequest &request, QString &outMsg);

    private:
        bool doRequest(const QByteArray &verb, QNetworkRequest &request, QIODevice *data,
                       QHttpMultiPart *multiPart, const QByteArray &bytes, QString &outMsg);
         int prepare_login_cfg(QMap<QString, QString> mapData, QHttpMultiPart *multiPart, QUrl &url, int type);              
        QString userAgent;
    };

} // namespace utils

#define HTTPCLIENT utils::HttpRestClient::instance()
#endif

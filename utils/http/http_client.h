#ifndef UTILS_HTTP_HTTP_CLIENT_H_
#define UTILS_HTTP_HTTP_CLIENT_H_

#include <QNetworkReply>
#include <QNetworkRequest>

#include "utils/singleton/singleton.h"

namespace utils
{
    QNetworkAccessManager &networkMgr();

    class HttpRestClient : public Singleton<HttpRestClient>
    {
    public:
        HttpRestClient();

        void post_test();
        void post_test2();

        bool get(QNetworkRequest &request, QString &outMsg);
        bool post(int action, QMap<QString, QString> mapData, QString &outMsg);
        bool put(QNetworkRequest &request, const QByteArray &data, QString &outMsg);
        bool put(QNetworkRequest &request, QHttpMultiPart *multiPart, QString &outMsg);
        // QNetworkReply *del(QNetworkRequest &request);
        bool del(QNetworkRequest &request, QString &outMsg);

    private:
        bool doRequest(const QByteArray &verb, QNetworkRequest &request, QIODevice *data,
                       QHttpMultiPart *multiPart, const QByteArray &bytes, QString &outMsg);
        QString userAgent;
    };

} // namespace utils

#define HTTPCLIENT utils::HttpRestClient::instance()
#endif

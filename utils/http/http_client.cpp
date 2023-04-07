#include "http_client.h"

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QHttpMultiPart>

#include "model/data/data_def.h"
#include "utils/serialize/serialize.h"

namespace utils
{
    QNetworkAccessManager &networkMgr()
    {
        static QNetworkAccessManager manager;
        return manager;
    }

    bool HttpRestClient::doRequest(const QByteArray &verb, QNetworkRequest &request, QIODevice *data,
                                   QHttpMultiPart *multiPart, const QByteArray &bytes, QString &outMsg)
    {
        bool ret = false;
        QEventLoop loop;
        request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);

        if (multiPart == nullptr)
        {
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        }

        QNetworkReply *reply = nullptr;

        if (data != nullptr)
        {
            reply = networkMgr().sendCustomRequest(request, verb, data);
        }
        else if (multiPart != nullptr)
        {
            reply = networkMgr().sendCustomRequest(request, verb, multiPart);
        }
        else
        {
            reply = networkMgr().sendCustomRequest(request, verb, bytes);
        }
        QObject::connect(reply, &QNetworkReply::finished, &loop, [&]()
                         {
                             outMsg = QString::fromUtf8(reply->readAll());
                             if (reply->error() == QNetworkReply::NoError)
                             {
                                 ret = true;
                             }
                             else
                             {
                                 outMsg.append(QString(" err info:%1").arg(reply->errorString()));
                                 qCritical() << outMsg << reply->error();
                                 reply->abort();
                             }
                             reply->deleteLater();
                             loop.quit();
                         });
        // 3min 超时
        QTimer::singleShot(3 * 60 * 1000, &loop, &QEventLoop::quit);
        loop.exec();
        return ret;
    }

    void syncPostOfFormData(QString url, QMap<QString, QString> mapData, int num)
    {
        QByteArray post_data;
        QString strAnd = "&";
        QMap<QString, QString>::iterator it;
        for (it = mapData.begin(); it != mapData.end(); it++)
        {
            QString key = it.key();
            QString val = it.value();

            QString str = key + "=" + val + strAnd;
            post_data.append(str);
        }

        QNetworkRequest requst;
        //QString header="application/json";
        QString header = "application/x-www-form-urlencoded";
        requst.setHeader(QNetworkRequest::ContentTypeHeader, header);
        requst.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());

        requst.setUrl(QUrl(url));

        requst.setAttribute(QNetworkRequest::User, num);

        // QNetworkReply* reply =QNetworkAccessManager::post(requst,post_data);
        QEventLoop loop;
        // connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
    }

    // 表单的发包方式有两种：application/x-www-form-urlencoded是最常用的表单发包方式，普通的表单提交，或者js发包，
    // 默认都是通过这种方式；如果需要传输文件，则就用到了multipart/form-data
    // post_test测试ok
    void HttpRestClient::post_test()
    {
        QString outMsg = "";
        QString post_data = "user_name=uos&password=1";
        QNetworkRequest requst;
        QString header = "application/x-www-form-urlencoded";
        requst.setHeader(QNetworkRequest::ContentTypeHeader, header);
        requst.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());

        QUrl url("http://10.20.6.68:3000/api/v1/user/login");
        requst.setUrl(url);
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.post(requst, post_data.toUtf8());
        QEventLoop loop;
        bool ret = false;
        QObject::connect(reply, &QNetworkReply::finished, &loop, [&]()
                         {
                             outMsg = QString::fromUtf8(reply->readAll());
                             qInfo() << "ttttttttttttttttt post2:" << outMsg;
                             if (reply->error() == QNetworkReply::NoError)
                             {
                                 ret = true;
                             }
                             else
                             {
                                 outMsg.append(QString(" err info:%1").arg(reply->errorString()));
                                 qCritical() << outMsg << reply->error();
                                 reply->abort();
                             }
                             reply->deleteLater();
                             loop.quit();
                         });
        // 3min 超时
        QTimer::singleShot(3 * 60 * 1000, &loop, &QEventLoop::quit);
        loop.exec();
    }

    void HttpRestClient::post_test2()
    {
        // 参考官网源码 https://doc.qt.io/archives/qt-4.8/qhttpmultipart.html
        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

        QHttpPart keyPart;
        keyPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"key\""));
        // namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"user_name\""));
        keyPart.setBody("1111111111111111");

        // QHttpPart imagePart;
        // imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
        // imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));
        // QFile *file = new QFile("image.jpg");
        // file->open(QIODevice::ReadOnly);
        // imagePart.setBodyDevice(file);
        // file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
        // multiPart->append(imagePart);

        multiPart->append(keyPart);

        QUrl url("http://10.20.6.68:3000/api/v1/money");
        QNetworkRequest request(url);
        QString headerData = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6MSwidXNlcm5hbWUiOiJ1b3MiLCJhdXRob3JpdHkiOjAsImV4cCI6MTY3OTcxMTMxMCwiaXNzIjoibWFsbCJ9.IDaawr3R3YglvSZvLq_SsDuZsAl3r0Ajw6UFYaVIRv8";
        // 传递token信息
        request.setRawHeader("Authorization", headerData.toLocal8Bit());

        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.post(request, multiPart);
        multiPart->setParent(reply); // delete the multiPart with the reply
                                     // here connect signals etc.
        QString outMsg = "";
        QEventLoop loop;
        bool ret = false;
        QObject::connect(reply, &QNetworkReply::finished, &loop, [&]()
                         {
                             outMsg = QString::fromUtf8(reply->readAll());
                             qInfo() << "ttttttttttttttttt post_test2:" << outMsg;
                             if (reply->error() == QNetworkReply::NoError)
                             {
                                 ret = true;
                             }
                             else
                             {
                                 outMsg.append(QString(" err info:%1").arg(reply->errorString()));
                                 qCritical() << outMsg << reply->error();
                                 reply->abort();
                             }
                             reply->deleteLater();
                             loop.quit();
                         });
        // 3min 超时
        QTimer::singleShot(3 * 60 * 1000, &loop, &QEventLoop::quit);
        loop.exec();
    }

    bool HttpRestClient::post(int action, QMap<QString, QString> mapData, QString &outMsg)
    {
        UserInfo user;
        user.user_name = "uos";
        user.pwd = "1";
        QString key1 = "user_name";

        // 参考官网源码 https://doc.qt.io/archives/qt-4.8/qhttpmultipart.html
        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

        QHttpPart namePart;
        namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=").append(key1)));
        // namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"user_name\""));
        namePart.setBody("uos");
        QHttpPart pwdPart;
        pwdPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"password\""));
        pwdPart.setBody("1");

        // QHttpPart imagePart;
        // imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
        // imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));
        // QFile *file = new QFile("image.jpg");
        // file->open(QIODevice::ReadOnly);
        // imagePart.setBodyDevice(file);
        // file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
        // multiPart->append(imagePart);

        multiPart->append(namePart);
        multiPart->append(pwdPart);

        QUrl url("http://10.20.6.68:3000/api/v1/user/login");
        QNetworkRequest request1(url);

        // 传递token信息
        // request.setRawHeader("Authorization", headerData.toLocal8Bit());
        // post_test();
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.post(request1, multiPart);
        multiPart->setParent(reply); // delete the multiPart with the reply
                                     // here connect signals etc.
        QEventLoop loop;
        bool ret = false;
        QObject::connect(reply, &QNetworkReply::finished, &loop, [&]()
                         {
                             outMsg = QString::fromUtf8(reply->readAll());
                             qInfo() << "ttttttttttttttttt:" << outMsg;
                             if (reply->error() == QNetworkReply::NoError)
                             {
                                 ret = true;
                             }
                             else
                             {
                                 outMsg.append(QString(" err info:%1").arg(reply->errorString()));
                                 qCritical() << outMsg << reply->error();
                                 reply->abort();
                             }
                             reply->deleteLater();
                             loop.quit();
                         });
        // 3min 超时
        QTimer::singleShot(3 * 60 * 1000, &loop, &QEventLoop::quit);
        loop.exec();
        int ttt = load_from_json(outMsg, user);
        qInfo() << "load_from_json ret:" << ttt << user.nickname << ", token:" << user.token;
        return 0;
    }

    bool HttpRestClient::del(QNetworkRequest &request, QString &outMsg)
    {
        return doRequest("DELETE", request, nullptr, nullptr, "", outMsg);
    }

    bool HttpRestClient::put(QNetworkRequest &request, const QByteArray &data, QString &outMsg)
    {
        return doRequest("PUT", request, nullptr, nullptr, data, outMsg);
    }

    bool HttpRestClient::get(QNetworkRequest &request, QString &outMsg)
    {
        return doRequest("GET", request, nullptr, nullptr, "", outMsg);
    }

    HttpRestClient::HttpRestClient()
    {
        // User-Agent: Mozilla/<version> (<system-information>) <platform> (<platform-details>) <extensions>
        // User-Agent: <product> / <product-version> <comment>
        userAgent = "linglong/1.0.0";
    }

    bool HttpRestClient::put(QNetworkRequest &request, QHttpMultiPart *multiPart, QString &outMsg)
    {
        return doRequest("PUT", request, nullptr, multiPart, "", outMsg);
    }
}

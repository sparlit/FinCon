#pragma once
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QQueue>
#include "core/Result.h"

namespace FinConNetwork {

class FinConHttpClient : public QObject {
    Q_OBJECT
public:
    static FinConHttpClient& instance() {
        static FinConHttpClient inst;
        return inst;
    }

    void get(const QUrl& url, std::function<void(const FinConCore::FinConResult<QByteArray>&)> callback) {
        auto* reply = manager_->get(QNetworkRequest(url));
        connect(reply, &QNetworkReply::finished, this, [reply, callback]() {
            if (reply->error() == QNetworkReply::NoError) {
                callback(FinConCore::FinConResult<QByteArray>(reply->readAll()));
            } else {
                callback(FinConCore::FinConResult<QByteArray>(reply->errorString().toStdString()));
            }
            reply->deleteLater();
        });
    }

private:
    FinConHttpClient() {
        manager_ = new QNetworkAccessManager(this);
    }
    QNetworkAccessManager* manager_;
};

}

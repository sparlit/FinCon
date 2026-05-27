#pragma once
#include <QWebSocket>
#include <QTimer>
#include "core/Logger.h"

namespace FinConNetwork {

class FinConWebSocketClient : public QObject {
    Q_OBJECT
public:
    FinConWebSocketClient(const QUrl& url, QObject* parent = nullptr) : QObject(parent), url_(url) {
        connect(&socket_, &QWebSocket::connected, this, &FinConWebSocketClient::onConnected);
        connect(&socket_, &QWebSocket::disconnected, this, &FinConWebSocketClient::onDisconnected);
        connect(&socket_, &QWebSocket::textMessageReceived, this, &FinConWebSocketClient::onMessage);

        reconnectTimer_ = new QTimer(this);
        connect(reconnectTimer_, &QTimer::timeout, this, &FinConWebSocketClient::connectToServer);
    }

    void connectToServer() {
        socket_.open(url_);
    }

private slots:
    void onConnected() {
        FINCON_LOG_INFO("WebSocket", "Connected to " + url_.toString().toStdString());
        reconnectTimer_->stop();
        backoff_ = 1000;
    }

    void onDisconnected() {
        FINCON_LOG_WARN("WebSocket", "Disconnected. Reconnecting...");
        reconnectTimer_->start(backoff_);
        backoff_ = std::min(backoff_ * 2, 30000);
    }

    void onMessage(const QString& msg) {
        emit messageReceived(msg);
    }

signals:
    void messageReceived(const QString& msg);

private:
    QWebSocket socket_;
    QUrl url_;
    QTimer* reconnectTimer_;
    int backoff_ = 1000;
};

}

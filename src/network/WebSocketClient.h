#pragma once
#include <QWebSocket>
#include <QTimer>
#include "core/Logger.h"

namespace FinConNetwork {

class FinConWebSocketClient : public QObject {
    Q_OBJECT
public:
    FinConWebSocketClient(const QUrl& url, QObject* parent = nullptr) : QObject(parent), url_(url) {
        connect(&FinConNet_Socket, &QWebSocket::connected, this, &FinConWebSocketClient::onConnected);
        connect(&FinConNet_Socket, &QWebSocket::disconnected, this, &FinConWebSocketClient::onDisconnected);
        connect(&FinConNet_Socket, &QWebSocket::textMessageReceived, this, &FinConWebSocketClient::onMessage);

        FinConNet_ReconnectTimer = new QTimer(this);
        connect(FinConNet_ReconnectTimer, &QTimer::timeout, this, &FinConWebSocketClient::connectToServer);
    }

    void connectToServer() {
        FinConNet_Socket.open(url_);
    }

private slots:
    void onConnected() {
        FINCON_LOG_INFO("WebSocket", "Connected to " + url_.toString().toStdString());
        FinConNet_ReconnectTimer->stop();
        FinConNet_Backoff = 1000;
    }

    void onDisconnected() {
        FINCON_LOG_WARN("WebSocket", "Disconnected. Reconnecting...");
        FinConNet_ReconnectTimer->start(FinConNet_Backoff);
        FinConNet_Backoff = std::min(FinConNet_Backoff * 2, 30000);
    }

    void onMessage(const QString& msg) {
        emit messageReceived(msg);
    }

signals:
    void messageReceived(const QString& msg);

private:
    QWebSocket FinConNet_Socket;
    QUrl url_;
    QTimer* FinConNet_ReconnectTimer;
    int FinConNet_Backoff = 1000;
};

}

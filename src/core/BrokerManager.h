#pragma once
#include <QObject>
#include <QMap>
#include <QTimer>
#include "core/DomainInterfaces.h"
#include "core/Logger.h"

namespace FinConCore {

class FinConExchangeSession : public QObject {
    Q_OBJECT
public:
    FinConExchangeSession(const QString& name, QObject* parent = nullptr)
        : QObject(parent), name_(name) {
        reconnectTimer_ = new QTimer(this);
        connect(reconnectTimer_, &QTimer::timeout, this, &FinConExchangeSession::connectExchange);
    }

    void start() {
        connectExchange();
    }

private slots:
    void connectExchange() {
        FINCON_LOG_INFO("Exchange", "Connecting to " + name_.toStdString());
        // Mock connection failure/success
        bool success = true;
        if (!success) {
            FINCON_LOG_WARN("Exchange", "Connection failed for " + name_.toStdString() + ". Retrying in " + std::to_string(backoff_) + "ms");
            reconnectTimer_->start(backoff_);
            backoff_ = std::min(backoff_ * 2, 30000);
        } else {
            backoff_ = 1000;
        }
    }

private:
    QString name_;
    QTimer* reconnectTimer_;
    int backoff_ = 1000;
};

class FinConBrokerManager : public QObject {
    Q_OBJECT
public:
    static FinConBrokerManager& instance() {
        static FinConBrokerManager inst;
        return inst;
    }

    void startSession(const QString& brokerName) {
        if (!sessions_.contains(brokerName)) {
            auto* session = new FinConExchangeSession(brokerName, this);
            sessions_[brokerName] = session;
            session->start();
        }
    }

private:
    FinConBrokerManager() {}
    QMap<QString, FinConExchangeSession*> sessions_;
};

}

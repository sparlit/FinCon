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
        FinConNet_ReconnectTimer = new QTimer(this);
        connect(FinConNet_ReconnectTimer, &QTimer::timeout, this, &FinConExchangeSession::connectExchange);
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
            FINCON_LOG_WARN("Exchange", "Connection failed for " + name_.toStdString() + ". Retrying in " + std::to_string(FinConNet_Backoff) + "ms");
            FinConNet_ReconnectTimer->start(FinConNet_Backoff);
            FinConNet_Backoff = std::min(FinConNet_Backoff * 2, 30000);
        } else {
            FinConNet_Backoff = 1000;
        }
    }

private:
    QString name_;
    QTimer* FinConNet_ReconnectTimer;
    int FinConNet_Backoff = 1000;
};

class FinConBrokerManager : public QObject {
    Q_OBJECT
public:
    static FinConBrokerManager& instance() {
        static FinConBrokerManager inst;
        return inst;
    }

    void startSession(const QString& brokerName) {
        if (!FinConBroker_Sessions.contains(brokerName)) {
            auto* session = new FinConExchangeSession(brokerName, this);
            FinConBroker_Sessions[brokerName] = session;
            session->start();
        }
    }

private:
    FinConBrokerManager() {}
    QMap<QString, FinConExchangeSession*> FinConBroker_Sessions;
};

}

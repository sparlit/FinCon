#pragma once
#include "core/DomainInterfaces.h"
#include "core/Logger.h"
#include <vector>
#include <QStringList>

namespace FinConCore {

class FinConGenericBroker : public IFinConBroker {
public:
    void placeOrder(const QJsonObject& order) override {
        FINCON_LOG_INFO("Broker", "Placing order: " + order["symbol"].toString().toStdString());
    }
    void cancelOrder(const QString& orderId) override {
        FINCON_LOG_INFO("Broker", "Cancelling order: " + orderId.toStdString());
    }
};

class FinConPersonaAgent : public IFinConAgent {
public:
    FinConPersonaAgent(const QString& name) : name_(name) {}
    void runAnalysis(const QString& prompt) override {
        FINCON_LOG_INFO("Agent", name_.toStdString() + " analyzing: " + prompt.toStdString());
    }
    QString personaName() const override { return name_; }
private:
    QString name_;
};

class FinConDomainRegistry {
public:
    static QStringList agents() {
        return {
            "Buffett", "Graham", "Lynch", "Munger", "Klarman", "Marks",
            "Bridgewater", "Citadel", "Renaissance", "Two Sigma", "D.E. Shaw", "Elliott", "Pershing Square", "AQR",
            "Geo-US", "Geo-China", "Geo-EU", "Geo-Russia", "Geo-India", "Geo-UK", "Geo-Japan", "Geo-Brazil",
            "Geo-MiddleEast", "Geo-ASEAN", "Geo-Africa", "Geo-NATO", "Geo-OPEC", "Geo-UN", "Geo-G7", "Geo-G20",
            "Geo-Intelligence", "Geo-Maritime", "Geo-Trade", "Macro-Econ"
        };
    }

    static QStringList brokers() {
        return {
            "Zerodha", "Angel One", "Upstox", "Fyers", "Dhan", "Groww", "Kotak", "IIFL",
            "5paisa", "AliceBlue", "Shoonya", "IBKR", "Alpaca", "Tradier", "Saxo Bank", "Generic REST"
        };
    }
};

}

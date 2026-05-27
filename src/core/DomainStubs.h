#pragma once
#include "core/DomainInterfaces.h"
#include "core/Logger.h"
#include <vector>
#include <QStringList>

namespace FinConCore {

class FinConGenericBroker : public IFinConBroker {
public:
    void placeOrder(const QJsonObject& FinConObj_Order) override {
        FINCON_LOG_INFO("Broker", "Placing order: " + FinConObj_Order["FinConStr_Symbol"].toString().toStdString());
    }
    void cancelOrder(const QString& FinConStr_OrderId) override {
        FINCON_LOG_INFO("Broker", "Cancelling order: " + FinConStr_OrderId.toStdString());
    }
};

class FinConIBKRBroker : public FinConGenericBroker {};
class FinConZerodhaBroker : public FinConGenericBroker {};
class FinConAlpacaBroker : public FinConGenericBroker {};

class FinConBridgewaterAgent : public FinConPersonaAgent { public: FinConBridgewaterAgent() : FinConPersonaAgent("Bridgewater") {} };
class FinConCitadelAgent : public FinConPersonaAgent { public: FinConCitadelAgent() : FinConPersonaAgent("Citadel") {} };
class FinConRenaissanceAgent : public FinConPersonaAgent { public: FinConRenaissanceAgent() : FinConPersonaAgent("Renaissance") {} };
class FinConTwoSigmaAgent : public FinConPersonaAgent { public: FinConTwoSigmaAgent() : FinConPersonaAgent("Two Sigma") {} };
class FinConDEShawAgent : public FinConPersonaAgent { public: FinConDEShawAgent() : FinConPersonaAgent("D.E. Shaw") {} };
class FinConElliottAgent : public FinConPersonaAgent { public: FinConElliottAgent() : FinConPersonaAgent("Elliott") {} };
class FinConPershingSquareAgent : public FinConPersonaAgent { public: FinConPershingSquareAgent() : FinConPersonaAgent("Pershing Square") {} };
class FinConAQRAgent : public FinConPersonaAgent { public: FinConAQRAgent() : FinConPersonaAgent("AQR") {} };

class FinConMacroAgent : public FinConPersonaAgent { public: FinConMacroAgent() : FinConPersonaAgent("Macro Economic") {} };

class FinConPersonaAgent : public IFinConAgent {
public:
    FinConPersonaAgent(const QString& FinConStr_Name) : FinConStr_Name_(FinConStr_Name) {}
    void runAnalysis(const QString& FinConStr_Prompt) override {
        FINCON_LOG_INFO("Agent", FinConStr_Name_.toStdString() + " analyzing: " + FinConStr_Prompt.toStdString());
    }
    QString personaName() const override { return FinConStr_Name_; }
private:
    QString FinConStr_Name_;
};

class FinConBuffettAgent : public FinConPersonaAgent { public: FinConBuffettAgent() : FinConPersonaAgent("Buffett") {} };
class FinConGrahamAgent : public FinConPersonaAgent { public: FinConGrahamAgent() : FinConPersonaAgent("Graham") {} };
class FinConLynchAgent : public FinConPersonaAgent { public: FinConLynchAgent() : FinConPersonaAgent("Lynch") {} };

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

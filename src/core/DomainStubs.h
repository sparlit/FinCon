#include "core/DomainInterfaces.h"
#include "core/Logger.h"

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

}

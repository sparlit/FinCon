#pragma once
#include <QString>
#include <QJsonObject>
#include <vector>

namespace FinConCore {

class IFinConBroker {
public:
    virtual ~IFinConBroker() = default;
    virtual void placeOrder(const QJsonObject& order) = 0;
    virtual void cancelOrder(const QString& orderId) = 0;
};

class IFinConAgent {
public:
    virtual ~IFinConAgent() = default;
    virtual void runAnalysis(const QString& prompt) = 0;
    virtual QString personaName() const = 0;
};

}

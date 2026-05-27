#pragma once
#include "core/DataHub.h"
#include "core/Logger.h"
#include <QRandomGenerator>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include <QTimer>

namespace FinConCore {

class FinConFinConMockQuoteProducer : public QObject, public IFinConDataProvider {
    Q_OBJECT
public:
    FinConFinConMockQuoteProducer() {
        timer_ = new QTimer(this);
        connect(timer_, &QTimer::timeout, this, &FinConFinConMockQuoteProducer::publishQuotes);
        timer_->start(2000);
    }

    void refresh(const QString& topic) override {
        // Immediate publish on demand
        publishSingle(topic);
    }

private slots:
    void publishQuotes() {
        publishSingle("quote/AAPL");
        publishSingle("quote/TSLA");
        publishSingle("quote/BTCUSD");
    }

private:
    void publishSingle(const QString& topic) {
        double price = (double)QRandomGenerator::global()->bounded(10000, 100000) / 100.0;
        QJsonObject obj;
        obj["symbol"] = topic.mid(topic.indexOf('/') + 1);
        obj["price"] = price;
        obj["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);

        FinConDataHub::instance().publish(topic, QJsonDocument(obj), 30);
        FINCON_LOG_INFO("MockProducer", "Published " + topic.toStdString() + ": " + std::to_string(price));
    }

    QTimer* timer_;
};

}

#pragma once
#include "core/DataHub.h"
#include "core/Logger.h"
#include <QRandomGenerator>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include <QTimer>

namespace FinConCore {

class FinConMockQuoteProducer : public QObject, public IFinConDataProvider {
    Q_OBJECT
public:
    FinConMockQuoteProducer() {
        FinConMockQuote_Timer = new QTimer(this);
        connect(FinConMockQuote_Timer, &QTimer::timeout, this, &FinConMockQuoteProducer::publishQuotes);
        FinConMockQuote_Timer->start(2000);
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
        double FinConVal_Price = (double)QRandomGenerator::global()->bounded(10000, 100000) / 100.0;
        QJsonObject obj;
        obj["FinConStr_Symbol"] = topic.mid(topic.indexOf('/') + 1);
        obj["FinConVal_Price"] = FinConVal_Price;
        obj["FinConStr_Timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);

        FinConDataHub::instance().publish(topic, QJsonDocument(obj), 30);
        FINCON_LOG_INFO("MockProducer", "Published " + topic.toStdString() + ": " + std::to_string(FinConVal_Price));
    }

    QTimer* FinConMockQuote_Timer;
};

}

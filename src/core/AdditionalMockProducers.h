#include <QJsonObject>
#include "core/Logger.h"
#pragma once
#include "core/DataHub.h"
#include <QTimer>
#include <QJsonArray>

namespace FinConCore {

class FinConMockNewsProducer : public QObject, public IFinConDataProvider {
    Q_OBJECT
public:
    FinConMockNewsProducer() {
        FinConMockQuote_Timer = new QTimer(this);
        connect(FinConMockQuote_Timer, &QTimer::timeout, this, &FinConMockNewsProducer::publishNews);
        FinConMockQuote_Timer->start(10000); // News every 10 seconds
    }

    void refresh(const QString& topic) override {
        publishNews();
    }

private slots:
    void publishNews() {
        QJsonObject obj;
        obj["headline"] = "Market indices hit record highs on tech rally";
        obj["source"] = "FinCon News Service";
        obj["FinConStr_Timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);

        FinConDataHub::instance().publish("news/top", QJsonDocument(obj), 300);
        FINCON_LOG_INFO("NewsProducer", "Published top news headline");
    }

private:
    QTimer* FinConMockQuote_Timer;
};

class FinConMockEconomicsProducer : public QObject, public IFinConDataProvider {
    Q_OBJECT
public:
    FinConMockEconomicsProducer() {
        FinConMockQuote_Timer = new QTimer(this);
        connect(FinConMockQuote_Timer, &QTimer::timeout, this, &FinConMockEconomicsProducer::publishEconomics);
        FinConMockQuote_Timer->start(30000); // Economics every 30 seconds
    }

    void refresh(const QString& topic) override {
        publishEconomics();
    }

private slots:
    void publishEconomics() {
        QJsonObject obj;
        obj["indicator"] = "US CPI";
        obj["value"] = 3.2;
        obj["forecast"] = 3.1;

        FinConDataHub::instance().publish("economics/cpi", QJsonDocument(obj), 3600);
        FINCON_LOG_INFO("EconProducer", "Published US CPI data");
    }

private:
    QTimer* FinConMockQuote_Timer;
};

}

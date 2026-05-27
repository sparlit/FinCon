#pragma once
#include "core/DataHub.h"
#include <QTimer>
#include <QJsonArray>

namespace FinConCore {

class FinConMockNewsProducer : public QObject, public IFinConDataProvider {
    Q_OBJECT
public:
    FinConMockNewsProducer() {
        timer_ = new QTimer(this);
        connect(timer_, &QTimer::timeout, this, &FinConMockNewsProducer::publishNews);
        timer_->start(10000); // News every 10 seconds
    }

    void refresh(const QString& topic) override {
        publishNews();
    }

private slots:
    void publishNews() {
        QJsonObject obj;
        obj["headline"] = "Market indices hit record highs on tech rally";
        obj["source"] = "FinCon News Service";
        obj["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);

        FinConDataHub::instance().publish("news/top", QJsonDocument(obj), 300);
        FINCON_LOG_INFO("NewsProducer", "Published top news headline");
    }

private:
    QTimer* timer_;
};

class FinConMockEconomicsProducer : public QObject, public IFinConDataProvider {
    Q_OBJECT
public:
    FinConMockEconomicsProducer() {
        timer_ = new QTimer(this);
        connect(timer_, &QTimer::timeout, this, &FinConMockEconomicsProducer::publishEconomics);
        timer_->start(30000); // Economics every 30 seconds
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
    QTimer* timer_;
};

}

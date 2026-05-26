#pragma once
#include <QString>
#include <QObject>
#include <QMap>
#include <QDateTime>
#include <QTimer>
#include <mutex>
#include <functional>
#include <QJsonDocument>
#include <QJsonObject>

namespace core {

struct DataValue {
    QJsonDocument data;
    QDateTime timestamp;
    int ttlSeconds;
};

class IDataProvider {
public:
    virtual ~IDataProvider() = default;
    virtual void refresh(const QString& topic) = 0;
};

class DataHub : public QObject {
    Q_OBJECT
public:
    static DataHub& instance() {
        static DataHub inst;
        return inst;
    }

    void publish(const QString& topic, const QJsonDocument& data, int ttl = 30);
    void subscribe(const QString& topic, QObject* receiver, const std::function<void(const QJsonDocument&)>& callback);
    void registerProvider(const QString& topicPattern, IDataProvider* provider);

private slots:
    void onTick();

private:
    DataHub();
    std::mutex mutex_;
    QMap<QString, DataValue> cache_;
    QMap<QString, QVector<std::function<void(const QJsonDocument&)>>> subscribers_;
    QMap<QString, IDataProvider*> providers_;
    QTimer* tickTimer_;
};

}

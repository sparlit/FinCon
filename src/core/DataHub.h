#pragma once
#include <QString>
#include <QObject>
#include <QMap>
#include <QDateTime>
#include <QTimer>
#include <QReadWriteLock>
#include <functional>
#include <QJsonDocument>
#include <QThread>

namespace FinConCore {

struct FinConDataValue {
    QJsonDocument data;
    QDateTime timestamp;
    int ttlSeconds;
};

class IFinConDataProvider {
public:
    virtual ~IFinConDataProvider() = default;
    virtual void refresh(const QString& topic) = 0;
};

class FinConDataHub : public QObject {
    Q_OBJECT
public:
    static FinConDataHub& instance() {
        static FinConDataHub inst;
        return inst;
    }

    void publish(const QString& topic, const QJsonDocument& data, int ttl = 30);
    void subscribe(const QString& topic, QObject* receiver, const std::function<void(const QJsonDocument&)>& callback);
    void registerProvider(const QString& topicPattern, IFinConDataProvider* provider);

private slots:
    void onTick();

private:
    FinConDataHub();
    ~FinConDataHub();
    QReadWriteLock rwLock_;
    QMap<QString, FinConDataValue> cache_;
    QMap<QString, QVector<std::function<void(const QJsonDocument&)>>> subscribers_;
    QMap<QString, IFinConDataProvider*> providers_;
    QThread* workerThread_;
    QTimer* tickTimer_;
};

}

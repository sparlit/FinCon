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
    QDateTime FinConStr_Timestamp;
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
    QReadWriteLock FinConDataHub_RWLock;
    QMap<QString, FinConDataValue> FinConDataHub_Cache;
    struct Subscriber {
        QObject* receiver;
        std::function<void(const QJsonDocument&)> callback;
    };
    QMap<QString, QVector<Subscriber>> FinConDataHub_Subscribers;
    QMap<QString, IFinConDataProvider*> FinConDataHub_Providers;
    QMap<IFinConDataProvider*, QDateTime> FinConDataHub_LastRefresh;
    QThread* FinConDataHub_WorkerThread;
    QTimer* FinConDataHub_TickTimer;
};

}

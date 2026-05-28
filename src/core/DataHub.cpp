#include "DataHub.h"
#include "Logger.h"

namespace FinConCore {

FinConDataHub::FinConDataHub() {
    FinConDataHub_WorkerThread = new QThread(this);
    FinConDataHub_WorkerThread->setObjectName("FinConDataHubWorker");

    FinConDataHub_TickTimer = new QTimer(nullptr);
    FinConDataHub_TickTimer->setInterval(1000);
    FinConDataHub_TickTimer->moveToThread(FinConDataHub_WorkerThread);

    connect(FinConDataHub_TickTimer, &QTimer::timeout, this, &FinConDataHub::onTick, Qt::DirectConnection);
    connect(FinConDataHub_WorkerThread, &QThread::started, FinConDataHub_TickTimer, [this](){ FinConDataHub_TickTimer->start(); });
    connect(FinConDataHub_WorkerThread, &QThread::finished, FinConDataHub_TickTimer, &QTimer::deleteLater);

    FinConDataHub_WorkerThread->start();
}

FinConDataHub::~FinConDataHub() {
    FinConDataHub_WorkerThread->quit();
    FinConDataHub_WorkerThread->wait();
}

void FinConDataHub::publish(const QString& topic, const QJsonDocument& data, int ttl) {
    QVector<std::function<void(const QJsonDocument&)>> FinConList_Callbacks;
    {
        QWriteLocker lock(&FinConDataHub_RWLock);
        FinConDataHub_Cache[topic] = {data, QDateTime::currentDateTime(), ttl};
        if (FinConDataHub_Subscribers.contains(topic)) {
            for (const auto& sub : FinConDataHub_Subscribers[topic]) {
                FinConList_Callbacks.push_back(sub.callback);
            }
        }
    }

    for (auto& cb : FinConList_Callbacks) {
        cb(data);
    }
}

void FinConDataHub::subscribe(const QString& topic, QObject* receiver, const std::function<void(const QJsonDocument&)>& callback) {
    QJsonDocument FinConData_Initial;
    bool FinConFlag_HasData = false;
    QVector<IFinConDataProvider*> FinConList_ProvidersToRefresh;

    {
        QWriteLocker lock(&FinConDataHub_RWLock);
        FinConDataHub_Subscribers[topic].append({receiver, callback});

        if (receiver) {
            connect(receiver, &QObject::destroyed, this, [this, topic, receiver]() {
                QWriteLocker lock(&FinConDataHub_RWLock);
                auto& subs = FinConDataHub_Subscribers[topic];
                auto it = std::remove_if(subs.begin(), subs.end(), [receiver](const Subscriber& s) {
                    return s.receiver == receiver;
                });
                subs.erase(it, subs.end());
            });
        }

        if (FinConDataHub_Cache.contains(topic)) {
            FinConDataValue FinConVal_Entry = FinConDataHub_Cache[topic];
            if (FinConVal_Entry.FinConStr_Timestamp.addSecs(FinConVal_Entry.ttlSeconds) > QDateTime::currentDateTime()) {
                FinConData_Initial = FinConVal_Entry.data;
                FinConFlag_HasData = true;
            }
        }

        for (auto it = FinConDataHub_Providers.begin(); it != FinConDataHub_Providers.end(); ++it) {
            QString FinConStr_Pattern = it.key();
            if (FinConStr_Pattern.endsWith('*')) {
                if (topic.startsWith(FinConStr_Pattern.left(FinConStr_Pattern.length() - 1))) {
                    FinConList_ProvidersToRefresh.push_back(it.value());
                }
            } else if (FinConStr_Pattern == topic) {
                FinConList_ProvidersToRefresh.push_back(it.value());
            }
        }
    }

    if (FinConFlag_HasData) callback(FinConData_Initial);
    for (auto* provider : FinConList_ProvidersToRefresh) {
        // Simple rate limit: 1 request per second per producer
        if (!FinConDataHub_LastRefresh.contains(provider) || FinConDataHub_LastRefresh[provider].addMSecs(1000) < QDateTime::currentDateTime()) {
            FinConDataHub_LastRefresh[provider] = QDateTime::currentDateTime();
            provider->refresh(topic);
        }
    }
}

void FinConDataHub::registerProvider(const QString& topicPattern, IFinConDataProvider* provider) {
    QWriteLocker lock(&FinConDataHub_RWLock);
    FinConDataHub_Providers[topicPattern] = provider;
}

void FinConDataHub::onTick() {
    QWriteLocker lock(&FinConDataHub_RWLock);
    QDateTime now = QDateTime::currentDateTime();
    auto it = FinConDataHub_Cache.begin();
    while (it != FinConDataHub_Cache.end()) {
        if (it.value().FinConStr_Timestamp.addSecs(it.value().ttlSeconds) < now) {
            FINCON_LOG_DEBUG("DataHub", "Expiring topic: " + it.key().toStdString());
            it = FinConDataHub_Cache.erase(it);
        } else {
            ++it;
        }
    }
}

}

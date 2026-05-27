#include "DataHub.h"
#include "Logger.h"

namespace FinConCore {

FinConDataHub::FinConDataHub() {
    workerThread_ = new QThread(this);
    workerThread_->setObjectName("FinConDataHubWorker");

    tickTimer_ = new QTimer(nullptr);
    tickTimer_->setInterval(1000);
    tickTimer_->moveToThread(workerThread_);

    connect(tickTimer_, &QTimer::timeout, this, &FinConDataHub::onTick, Qt::DirectConnection);
    connect(workerThread_, &QThread::started, tickTimer_, [this](){ tickTimer_->start(); });
    connect(workerThread_, &QThread::finished, tickTimer_, &QTimer::deleteLater);

    workerThread_->start();
}

FinConDataHub::~FinConDataHub() {
    workerThread_->quit();
    workerThread_->wait();
}

void FinConDataHub::publish(const QString& topic, const QJsonDocument& data, int ttl) {
    QVector<std::function<void(const QJsonDocument&)>> callbacks;
    {
        QWriteLocker lock(&rwLock_);
        cache_[topic] = {data, QDateTime::currentDateTime(), ttl};
        if (subscribers_.contains(topic)) {
            callbacks = subscribers_[topic];
        }
    }

    for (auto& cb : callbacks) {
        cb(data);
    }
}

void FinConDataHub::subscribe(const QString& topic, QObject* receiver, const std::function<void(const QJsonDocument&)>& callback) {
    QJsonDocument initialData;
    bool hasData = false;
    QVector<IFinConDataProvider*> providersToRefresh;

    {
        QWriteLocker lock(&rwLock_);
        subscribers_[topic].append(callback);

        if (cache_.contains(topic)) {
            FinConDataValue val = cache_[topic];
            if (val.timestamp.addSecs(val.ttlSeconds) > QDateTime::currentDateTime()) {
                initialData = val.data;
                hasData = true;
            }
        }

        for (auto it = providers_.begin(); it != providers_.end(); ++it) {
            QString pattern = it.key();
            if (pattern.endsWith('*')) {
                if (topic.startsWith(pattern.left(pattern.length() - 1))) {
                    providersToRefresh.push_back(it.value());
                }
            } else if (pattern == topic) {
                providersToRefresh.push_back(it.value());
            }
        }
    }

    if (hasData) callback(initialData);
    for (auto* provider : providersToRefresh) {
        provider->refresh(topic);
    }
}

void FinConDataHub::registerProvider(const QString& topicPattern, IFinConDataProvider* provider) {
    QWriteLocker lock(&rwLock_);
    providers_[topicPattern] = provider;
}

void FinConDataHub::onTick() {
    QWriteLocker lock(&rwLock_);
    QDateTime now = QDateTime::currentDateTime();
    auto it = cache_.begin();
    while (it != cache_.end()) {
        if (it.value().timestamp.addSecs(it.value().ttlSeconds) < now) {
            FINCON_LOG_DEBUG("DataHub", "Expiring topic: " + it.key().toStdString());
            it = cache_.erase(it);
        } else {
            ++it;
        }
    }
}

}

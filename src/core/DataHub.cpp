#include "DataHub.h"
#include "Logger.h"

namespace core {

DataHub::DataHub() {
    tickTimer_ = new QTimer(this);
    connect(tickTimer_, &QTimer::timeout, this, &DataHub::onTick);
    tickTimer_->start(1000);
}

void DataHub::publish(const QString& topic, const QJsonDocument& data, int ttl) {
    std::lock_guard<std::mutex> lock(mutex_);
    cache_[topic] = {data, QDateTime::currentDateTime(), ttl};

    if (subscribers_.contains(topic)) {
        for (auto& cb : subscribers_[topic]) {
            cb(data);
        }
    }
}

void DataHub::subscribe(const QString& topic, QObject* receiver, const std::function<void(const QJsonDocument&)>& callback) {
    std::lock_guard<std::mutex> lock(mutex_);
    subscribers_[topic].append(callback);

    if (cache_.contains(topic)) {
        DataValue val = cache_[topic];
        if (val.timestamp.addSecs(val.ttlSeconds) > QDateTime::currentDateTime()) {
            callback(val.data);
        }
    }

    // Trigger refresh if provider exists
    for (auto it = providers_.begin(); it != providers_.end(); ++it) {
        if (topic.startsWith(it.key().left(it.key().indexOf('*')))) {
            it.value()->refresh(topic);
        }
    }
}

void DataHub::registerProvider(const QString& topicPattern, IDataProvider* provider) {
    std::lock_guard<std::mutex> lock(mutex_);
    providers_[topicPattern] = provider;
}

void DataHub::onTick() {
    std::lock_guard<std::mutex> lock(mutex_);
    QDateTime now = QDateTime::currentDateTime();
    auto it = cache_.begin();
    while (it != cache_.end()) {
        if (it.value().timestamp.addSecs(it.value().ttlSeconds) < now) {
            LOG_DEBUG("DataHub", "Expiring topic: " + it.key().toStdString());
            it = cache_.erase(it);
        } else {
            ++it;
        }
    }
}

}

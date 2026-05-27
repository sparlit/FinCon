#include "DataHub.h"
#include "Logger.h"

namespace FinConCore {

FinConDataHub::FinConDataHub() {
    tickTimer_ = new QTimer(this);
    connect(tickTimer_, &QTimer::timeout, this, &FinConDataHub::onTick);
    tickTimer_->start(1000);
}

void FinConDataHub::publish(const QString& topic, const QJsonDocument& data, int ttl) {
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    cache_[topic] = {data, QDateTime::currentDateTime(), ttl};

    if (subscribers_.contains(topic)) {
        for (auto& cb : subscribers_[topic]) {
            cb(data);
        }
    }
}

void FinConDataHub::subscribe(const QString& topic, QObject* receiver, const std::function<void(const QJsonDocument&)>& callback) {
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    subscribers_[topic].append(callback);

    if (cache_.contains(topic)) {
        FinConDataValue val = cache_[topic];
        if (val.timestamp.addSecs(val.ttlSeconds) > QDateTime::currentDateTime()) {
            callback(val.data);
        }
    }

    for (auto it = providers_.begin(); it != providers_.end(); ++it) {
        QString pattern = it.key();
        if (pattern.endsWith('*')) {
            if (topic.startsWith(pattern.left(pattern.length() - 1))) {
                it.value()->refresh(topic);
            }
        } else if (pattern == topic) {
            it.value()->refresh(topic);
        }
    }
}

void FinConDataHub::registerProvider(const QString& topicPattern, IFinConDataProvider* provider) {
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    providers_[topicPattern] = provider;
}

void FinConDataHub::onTick() {
    std::lock_guard<std::recursive_mutex> lock(mutex_);
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

#pragma once
#include <QObject>
#include <QString>
#include "core/Logger.h"

namespace FinConServices {

class FinConNotificationManager : public QObject {
    Q_OBJECT
public:
    static FinConNotificationManager& instance() {
        static FinConNotificationManager inst;
        return inst;
    }

    void notify(const QString& title, const QString& message, const QString& level = "INFO") {
        FINCON_LOG_INFO("Notification", "[" + title.toStdString() + "] " + message.toStdString());
        // Toast logic stub
        emit newNotification(title, message, level);
    }

    void sendSlack(const QString& msg) {
        FINCON_LOG_INFO("SlackStub", "Sent: " + msg.toStdString());
    }

    void sendDiscord(const QString& msg) {
        FINCON_LOG_INFO("DiscordStub", "Sent: " + msg.toStdString());
    }

signals:
    void newNotification(const QString& title, const QString& message, const QString& level);

private:
    FinConNotificationManager() {}
};

}

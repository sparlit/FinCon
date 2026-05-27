#pragma once
#include <QObject>
#include <QString>
#include <QDateTime>
#include <functional>
#include "core/Result.h"

namespace FinConServices {

class FinConAuthService : public QObject {
    Q_OBJECT
public:
    static FinConAuthService& instance() {
        static FinConAuthService inst;
        return inst;
    }

    void login(const QString& email, const QString& password, std::function<void(const FinConCore::FinConResult<bool>&)> callback);
    bool isAuthenticated() const { return FinConAuth_Authenticated; }
    QString username() const { return "User"; }

    void setPin(const QString& pin) { FinConStr_PinHash = pin; } // Mock PBKDF2
    bool verifyPin(const QString& pin) { return pin == FinConStr_PinHash; }
    void updateLastActivity() { FinConStr_LastActivity = QDateTime::currentDateTime(); }
    bool isLocked() const { return FinConStr_LastActivity.secsTo(QDateTime::currentDateTime()) > 1800; }

private:
    FinConAuthService() : FinConAuth_Authenticated(false), FinConStr_PinHash("1234") {
        FinConStr_LastActivity = QDateTime::currentDateTime();
    }
    bool FinConAuth_Authenticated;
    QString FinConStr_PinHash;
    QDateTime FinConStr_LastActivity;
};

}

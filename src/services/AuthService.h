#pragma once
#include <QObject>
#include <QString>
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

private:
    FinConAuthService() : FinConAuth_Authenticated(false) {}
    bool FinConAuth_Authenticated;
};

}

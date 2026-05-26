#pragma once
#include <QObject>
#include <QString>
#include <functional>
#include "core/Result.h"

namespace services {

class AuthService : public QObject {
    Q_OBJECT
public:
    static AuthService& instance() {
        static AuthService inst;
        return inst;
    }

    void login(const QString& email, const QString& password, std::function<void(const core::Result<bool>&)> callback);
    bool isAuthenticated() const { return authenticated_; }
    QString username() const { return "User"; }

private:
    AuthService() : authenticated_(false) {}
    bool authenticated_;
};

}

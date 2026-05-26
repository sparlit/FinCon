#include "AuthService.h"
#include <QTimer>

namespace services {

void AuthService::login(const QString& email, const QString& password, std::function<void(const core::Result<bool>&)> callback) {
    // Mock login
    QTimer::singleShot(500, [this, email, callback]() {
        if (!email.isEmpty()) {
            authenticated_ = true;
            callback(core::Result<bool>(true));
        } else {
            callback(core::Result<bool>(std::string("Invalid credentials")));
        }
    });
}

}

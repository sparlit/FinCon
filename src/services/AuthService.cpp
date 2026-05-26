#include "AuthService.h"
#include <QTimer>

namespace FinConServices {

void FinConAuthService::login(const QString& email, const QString& password, std::function<void(const FinConCore::FinConResult<bool>&)> callback) {
    QTimer::singleShot(500, [this, email, callback]() {
        if (!email.isEmpty()) {
            authenticated_ = true;
            callback(FinConCore::FinConResult<bool>(true));
        } else {
            callback(FinConCore::FinConResult<bool>(std::string("Invalid credentials")));
        }
    });
}

}

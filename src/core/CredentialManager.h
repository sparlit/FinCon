#pragma once
#include <QString>
#include "Result.h"

namespace core {

class CredentialManager {
public:
    static Result<bool> storePassword(const QString& service, const QString& account, const QString& password);
    static Result<QString> getPassword(const QString& service, const QString& account);
};

}

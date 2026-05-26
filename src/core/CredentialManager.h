#pragma once
#include <QString>
#include "Result.h"

namespace FinConCore {

class FinConCredentialManager {
public:
    static FinConResult<bool> storePassword(const QString& service, const QString& account, const QString& password);
    static FinConResult<QString> getPassword(const QString& service, const QString& account);
};

}

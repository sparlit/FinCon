#include "CredentialManager.h"
#ifdef __linux__
#undef signals
#include <libsecret/secret.h>
#endif

#ifdef _WIN32
#include <windows.h>
#include <wincrypt.h>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#endif

#ifdef __APPLE__
#include <Security/Security.h>
#endif

namespace FinConCore {

FinConResult<bool> FinConCredentialManager::storePassword(const QString& service, const QString& account, const QString& password) {
#ifdef __linux__
    GError* error = nullptr;
    secret_password_store_sync(
        SECRET_SCHEMA_COMPAT_NETWORK,
        SECRET_COLLECTION_DEFAULT,
        (service + " " + account).toUtf8().constData(),
        password.toUtf8().constData(),
        nullptr, &error,
        "user", account.toUtf8().constData(),
        "domain", service.toUtf8().constData(),
        nullptr
    );
    if (error) {
        std::string msg = error->message;
        g_error_free(error);
        return FinConResult<bool>(msg);
    }
    return FinConResult<bool>(true);
#elif defined(_WIN32)
    DATA_BLOB dataIn;
    DATA_BLOB dataOut;
    QByteArray pwd = password.toUtf8();
    dataIn.pbData = (BYTE*)pwd.data();
    dataIn.cbData = pwd.size();

    if (CryptProtectData(&dataIn, L"Terminal Password", NULL, NULL, NULL, 0, &dataOut)) {
        QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/secrets/";
        QDir().mkpath(path);
        QFile file(path + service + "_" + account + ".bin");
        if (file.open(QIODevice::WriteOnly)) {
            file.write((const char*)dataOut.pbData, dataOut.cbData);
            file.close();
            LocalFree(dataOut.pbData);
            return FinConResult<bool>(true);
        }
        LocalFree(dataOut.pbData);
    }
    return FinConResult<bool>(std::string("Win32 CryptProtectData failed"));
#elif defined(__APPLE__)
    OSStatus status = SecKeychainAddGenericPassword(
        NULL,
        service.length(), service.toUtf8().constData(),
        account.length(), account.toUtf8().constData(),
        password.length(), password.toUtf8().constData(),
        NULL
    );
    if (status != errSecSuccess) return FinConResult<bool>(std::string("macOS Keychain error"));
    return FinConResult<bool>(true);
#else
    return FinConResult<bool>(true);
#endif
}

FinConResult<QString> FinConCredentialManager::getPassword(const QString& service, const QString& account) {
#ifdef __linux__
    GError* error = nullptr;
    char* password = secret_password_lookup_sync(
        SECRET_SCHEMA_COMPAT_NETWORK,
        nullptr, &error,
        "user", account.toUtf8().constData(),
        "domain", service.toUtf8().constData(),
        nullptr
    );
    if (error) {
        std::string msg = error->message;
        g_error_free(error);
        return FinConResult<QString>(msg);
    }
    if (!password) return FinConResult<QString>(QString(""));
    QString FinConRes = QString::fromUtf8(password);
    secret_password_free(password);
    return FinConResult<QString>(FinConRes);
#elif defined(_WIN32)
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/secrets/";
    QFile file(path + service + "_" + account + ".bin");
    if (!file.open(QIODevice::ReadOnly)) return FinConResult<QString>(QString(""));

    QByteArray cipherText = file.readAll();
    file.close();

    DATA_BLOB dataIn, dataOut;
    dataIn.pbData = (BYTE*)cipherText.data();
    dataIn.cbData = cipherText.size();

    if (CryptUnprotectData(&dataIn, NULL, NULL, NULL, NULL, 0, &dataOut)) {
        QString result = QString::fromUtf8((const char*)dataOut.pbData, dataOut.cbData);
        LocalFree(dataOut.pbData);
        return FinConResult<QString>(result);
    }
    return FinConResult<QString>(std::string("Win32 CryptUnprotectData failed"));
#elif defined(__APPLE__)
    void* passwordData = nullptr;
    UInt32 passwordLength = 0;
    OSStatus status = SecKeychainFindGenericPassword(
        NULL,
        service.length(), service.toUtf8().constData(),
        account.length(), account.toUtf8().constData(),
        &passwordLength, &passwordData,
        NULL
    );
    if (status == errSecSuccess) {
        QString result = QString::fromUtf8((const char*)passwordData, passwordLength);
        SecKeychainItemFreeContent(NULL, passwordData);
        return FinConResult<QString>(result);
    }
    return FinConResult<QString>(QString(""));
#else
    return FinConResult<QString>(QString(""));
#endif
}

}

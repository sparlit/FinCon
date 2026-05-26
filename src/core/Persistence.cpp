#include "Persistence.h"
#include "Logger.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>

namespace core {

Persistence::Persistence() {
    db_ = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    db_.setDatabaseName(path + "/terminal.db");
}

bool Persistence::init() {
    if (!db_.open()) {
        LOG_ERROR("DB", "Failed to open database: " + db_.lastError().text().toStdString());
        return false;
    }

    QSqlQuery query;
    query.exec("PRAGMA journal_mode=WAL;");

    runMigrations();
    return true;
}

void Persistence::runMigrations() {
    QSqlQuery query;
    // Simple migration table
    query.exec("CREATE TABLE IF NOT EXISTS migrations (id INTEGER PRIMARY KEY, version INTEGER)");

    query.exec("SELECT MAX(version) FROM migrations");
    int currentVersion = 0;
    if (query.next()) {
        currentVersion = query.value(0).toInt();
    }

    if (currentVersion < 1) {
        LOG_INFO("DB", "Running migration 1");
        query.exec("CREATE TABLE users (id INTEGER PRIMARY KEY, username TEXT, session_token TEXT)");
        query.exec("INSERT INTO migrations (version) VALUES (1)");
    }
    // ... add more migrations as needed
}

}

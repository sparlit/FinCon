#include "Persistence.h"
#include "Logger.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>

namespace FinConCore {

FinConPersistence::FinConPersistence() {
    FinConPersistence_Db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    FinConPersistence_Db.setDatabaseName(path + "/terminal.db");
}

bool FinConPersistence::init() {
    if (!FinConPersistence_Db.open()) {
        FINCON_LOG_ERROR("DB", "Failed to open database: " + FinConPersistence_Db.lastError().text().toStdString());
        return false;
    }

    QSqlQuery query;
    query.exec("PRAGMA journal_mode=WAL;");

    runMigrations();
    return true;
}

void FinConPersistence::runMigrations() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS migrations (id INTEGER PRIMARY KEY, version INTEGER)");

    query.exec("SELECT MAX(version) FROM migrations");
    int currentVersion = 0;
    if (query.next()) {
        currentVersion = query.value(0).toInt();
    }

    if (currentVersion < 1) {
        FINCON_LOG_INFO("DB", "Running migration 1");
        query.exec("CREATE TABLE users (id INTEGER PRIMARY KEY, username TEXT, session_token TEXT)");
        query.exec("INSERT INTO migrations (version) VALUES (1)");
    }
    if (currentVersion < 2) {
        FINCON_LOG_INFO("DB", "Running migration 2");
        query.exec("CREATE TABLE watchlists (id INTEGER PRIMARY KEY, name TEXT, FinConStr_Symbols TEXT)");
        query.exec("CREATE TABLE portfolios (id INTEGER PRIMARY KEY, name TEXT, account_id TEXT)");
        query.exec("CREATE TABLE orders (id INTEGER PRIMARY KEY, FinConStr_Symbol TEXT, qty REAL, side TEXT, status TEXT)");
        query.exec("INSERT INTO migrations (version) VALUES (2)");
    }
}

}

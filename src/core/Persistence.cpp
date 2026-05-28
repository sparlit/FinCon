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

    for (int v = currentVersion + 1; v <= 20; ++v) {
        FINCON_LOG_INFO("DB", "Running migration " + std::to_string(v));
        switch(v) {
            case 1: query.exec("CREATE TABLE users (id INTEGER PRIMARY KEY, username TEXT, session_token TEXT)"); break;
            case 2: query.exec("CREATE TABLE watchlists (id INTEGER PRIMARY KEY, name TEXT, FinConStr_Symbols TEXT)");
                    query.exec("CREATE TABLE portfolios (id INTEGER PRIMARY KEY, name TEXT, account_id TEXT)");
                    query.exec("CREATE TABLE orders (id INTEGER PRIMARY KEY, FinConStr_Symbol TEXT, qty REAL, side TEXT, status TEXT)"); break;
            case 3: query.exec("CREATE TABLE chat_history (id INTEGER PRIMARY KEY, role TEXT, content TEXT, timestamp DATETIME)"); break;
            case 4: query.exec("CREATE TABLE news_cache (id INTEGER PRIMARY KEY, title TEXT, content TEXT, source TEXT, sentiment REAL)"); break;
            case 5: query.exec("CREATE TABLE workflows (id INTEGER PRIMARY KEY, name TEXT, definition_json TEXT)"); break;
            case 6: query.exec("CREATE TABLE settings (key TEXT PRIMARY KEY, value TEXT)"); break;
            case 7: query.exec("CREATE TABLE llm_configs (id INTEGER PRIMARY KEY, provider TEXT, api_key_ref TEXT, model_name TEXT)"); break;
            case 8: query.exec("CREATE TABLE agent_runs (id INTEGER PRIMARY KEY, agent_id TEXT, input TEXT, output TEXT, duration REAL)"); break;
            case 9: query.exec("CREATE TABLE econ_data (id INTEGER PRIMARY KEY, indicator TEXT, country TEXT, value REAL, date DATE)"); break;
            case 10: query.exec("CREATE TABLE broker_accounts (id INTEGER PRIMARY KEY, broker_name TEXT, account_type TEXT, balance REAL)"); break;
            case 11: query.exec("CREATE TABLE market_cache (id INTEGER PRIMARY KEY, symbol TEXT, price REAL, timestamp DATETIME)"); break;
            case 12: query.exec("CREATE TABLE notifications (id INTEGER PRIMARY KEY, title TEXT, body TEXT, read_flag INTEGER)"); break;
            case 13: query.exec("CREATE TABLE data_mappings (id INTEGER PRIMARY KEY, source_field TEXT, target_field TEXT)"); break;
            case 14: query.exec("CREATE TABLE file_manager_metadata (id INTEGER PRIMARY KEY, path TEXT, tags TEXT)"); break;
            case 15: query.exec("CREATE TABLE relationship_nodes (id INTEGER PRIMARY KEY, source TEXT, target TEXT, relation_type TEXT)"); break;
            case 16: query.exec("CREATE TABLE algo_results (id INTEGER PRIMARY KEY, strategy_id TEXT, net_pnl REAL)"); break;
            case 17: query.exec("CREATE TABLE backtest_runs (id INTEGER PRIMARY KEY, config_json TEXT, metrics_json TEXT)"); break;
            case 18: query.exec("CREATE TABLE quant_snapshots (id INTEGER PRIMARY KEY, tool_name TEXT, result_json TEXT)"); break;
            case 19: query.exec("CREATE TABLE geo_events (id INTEGER PRIMARY KEY, region TEXT, event_type TEXT, severity INTEGER)"); break;
            case 20: query.exec("CREATE TABLE user_prefs (key TEXT PRIMARY KEY, val TEXT)"); break;
        }
        query.exec("INSERT INTO migrations (version) VALUES (" + QString::number(v) + ")");
    }
}

}

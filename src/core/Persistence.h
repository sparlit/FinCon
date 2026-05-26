#pragma once
#include <QSqlDatabase>
#include <QString>

namespace FinConCore {

class FinConPersistence {
public:
    static FinConPersistence& instance() {
        static FinConPersistence inst;
        return inst;
    }

    bool init();
    void runMigrations();

    QSqlDatabase db() { return db_; }

private:
    FinConPersistence();
    QSqlDatabase db_;
};

}

#pragma once
#include <QSqlDatabase>
#include <QString>
#include <QVariantMap>

namespace core {

class Persistence {
public:
    static Persistence& instance() {
        static Persistence inst;
        return inst;
    }

    bool init();
    void runMigrations();

    QSqlDatabase db() { return db_; }

private:
    Persistence();
    QSqlDatabase db_;
};

}

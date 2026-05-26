#pragma once
#include <QDockWidget>
#include <QListWidget>

namespace ui {

class Sidebar : public QDockWidget {
    Q_OBJECT
public:
    Sidebar(QWidget* parent = nullptr);

signals:
    void screenRequested(const QString& name);

private:
    QListWidget* list_;
};

}

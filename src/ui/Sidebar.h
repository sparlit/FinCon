#pragma once
#include <QDockWidget>
#include <QListWidget>

namespace FinConUI {

class FinConSidebar : public QDockWidget {
    Q_OBJECT
public:
    FinConSidebar(QWidget* parent = nullptr);

signals:
    void screenRequested(const QString& name);

private:
    QListWidget* FinConSidebar_List;
};

}

#include "Sidebar.h"

namespace FinConUI {

FinConSidebar::FinConSidebar(QWidget* parent) : QDockWidget("Navigation", parent) {
    list_ = new QListWidget(this);
    QStringList screens = {
        "Dashboard", "Markets", "AI Chat", "Node Editor", "QuantLib Suite", "Watchlist", "News"
    };
    list_->addItems(screens);
    setWidget(list_);

    connect(list_, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
        emit screenRequested(item->text());
    });
}

}

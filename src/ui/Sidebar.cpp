#include "Sidebar.h"

namespace FinConUI {

FinConSidebar::FinConSidebar(QWidget* parent) : QDockWidget("Navigation", parent) {
    FinConSidebar_List = new QListWidget(this);
    QStringList screens = {
        "Dashboard", "Markets", "Watchlist", "News", "Crypto Trading",
        "Equity Trading", "Algo Trading", "Backtesting", "Trade Visualization",
        "Portfolio", "Equity Research", "Derivatives", "QuantLib Suite",
        "AI Quant Lab", "Alpha Arena", "Agent Config", "MCP Servers",
        "AI Chat", "Economics", "DBnomics", "AkShare", "Asia Markets",
        "Geopolitics", "Government Data", "Maritime", "Prediction Markets",
        "Relationship Map", "Node Editor", "Code Editor", "Excel Grid",
        "Report Builder", "Data Sources", "Data Mapping", "File Manager",
        "Notes", "Forum", "Profile", "Settings", "Support", "Docs", "About"
    };
    FinConSidebar_List->addItems(screens);
    setWidget(FinConSidebar_List);

    connect(FinConSidebar_List, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
        emit screenRequested(item->text());
    });
}

}

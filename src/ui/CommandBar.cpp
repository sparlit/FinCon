#include "CommandBar.h"
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QVector>
#include <algorithm>
#include <utility>

namespace FinConUI {

FinConCommandBar::FinConCommandBar(QWidget* parent) : QWidget(parent, Qt::FramelessWindowHint | Qt::Popup) {
    auto FinConLayout = new QVBoxLayout(this);
    FinConCommand_Input = new QLineEdit(this);
    FinConCommand_Input->setPlaceholderText("Search screens or actions (Ctrl+K)...");

    FinConCommand_Results = new QListWidget(this);

    FinConLayout->addWidget(FinConCommand_Input);
    FinConLayout->addWidget(FinConCommand_Results);

    setFixedSize(600, 400);

    FinConCommand_Input->installEventFilter(this);

    FinConCommand_Actions = {
        "Dashboard", "Markets", "Watchlist", "News", "Crypto Trading",
        "Equity Trading", "Algo Trading", "Backtesting", "Trade Visualization",
        "Portfolio", "Equity Research", "Derivatives", "QuantLib Suite",
        "AI Quant Lab", "Alpha Arena", "Agent Config", "MCP Servers",
        "AI Chat", "Economics", "DBnomics", "AkShare", "Asia Markets",
        "Geopolitics", "Government Data", "Maritime", "Prediction Markets",
        "Relationship Map", "Node Editor", "Code Editor", "Excel Grid",
        "Report Builder", "Data Sources", "Data Mapping", "File Manager",
        "Notes", "Forum", "Profile", "Settings", "Support", "Docs", "About", "Logout"
    };

    connect(FinConCommand_Input, &QLineEdit::textChanged, this, &FinConCommandBar::onTextChanged);
    connect(FinConCommand_Results, &QListWidget::itemActivated, this, &FinConCommandBar::onItemActivated);
    connect(FinConCommand_Results, &QListWidget::itemClicked, this, &FinConCommandBar::onItemActivated);
}

void FinConCommandBar::onTextChanged(const QString& text) {
    FinConCommand_Results->clear();
    if (text.isEmpty()) return;

    QVector<std::pair<int, QString>> matches;
    for (const auto& action : FinConCommand_Actions) {
        int score = 0;
        if (action.startsWith(text, Qt::CaseInsensitive)) score += 100;
        else if (action.contains(text, Qt::CaseInsensitive)) score += 50;

        if (score > 0) {
            matches.push_back({score, action});
        }
    }

    std::sort(matches.begin(), matches.end(), [](const auto& a, const auto& b) {
        return a.first > b.first;
    });

    for (const auto& match : matches) {
        FinConCommand_Results->addItem(match.second);
    }
}

void FinConCommandBar::onItemActivated(QListWidgetItem* item) {
    emit actionTriggered(item->text());
    hide();
}

bool FinConCommandBar::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Escape) {
            hide();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

}

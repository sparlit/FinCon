#include "Screens.h"
#include "core/ThemeManager.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include "core/DataHub.h"
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

namespace FinConScreens {

FinConDashboardScreen::FinConDashboardScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QGridLayout(this);
    FinConLayout->setSpacing(8);

    auto createWidget = [this](const QString& title, FinConCore::FinConThemeFlavor FinConEnum_Flavor) {
        auto w = new QWidget(this);
        w->setStyleSheet(FinConCore::FinConThemeManager::generateStyleSheet(FinConEnum_Flavor));
        auto l = new QVBoxLayout(w);
        auto lbl = new QLabel(title, w);
        lbl->setObjectName("heading");
        l->addWidget(lbl);
        l->addWidget(new QLabel("Real-time data streaming...", w));
        return w;
    };

    FinConLayout->addWidget(createWidget("Trading Activity", FinConCore::FinConThemeFlavor::Trading), 0, 0);
    FinConLayout->addWidget(createWidget("Analytics Insights", FinConCore::FinConThemeFlavor::Analytics), 0, 1);
    FinConLayout->addWidget(createWidget("Market Data", FinConCore::FinConThemeFlavor::Data), 1, 0);
    FinConLayout->addWidget(createWidget("AI Agent Status", FinConCore::FinConThemeFlavor::AI), 1, 1);
}

FinConMarketsScreen::FinConMarketsScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QVBoxLayout(this);
    FinConLayout->addWidget(new QLabel("Global Markets Overview", this));

    FinConNode_View = new QTableView(this);
    model_ = new FinConCore::FinConMarketModel(this);
    FinConNode_View->setModel(model_);
    FinConLayout->addWidget(FinConNode_View);

    FinConCore::FinConDataHub::instance().subscribe("quote/*", this, [this](const QJsonDocument& doc) {
        model_->updateQuote(doc.object());
    });
}

FinConAIChatScreen::FinConAIChatScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QVBoxLayout(this);
    auto chatArea = new QTextEdit(this);
    chatArea->setReadOnly(true);
    auto input = new QLineEdit(this);
    auto send = new QPushButton("Send", this);

    FinConLayout->addWidget(chatArea);
    auto hLayout = new QHBoxLayout();
    hLayout->addWidget(input);
    hLayout->addWidget(send);
    FinConLayout->addLayout(hLayout);
}

FinConEquityResearchScreen::FinConEquityResearchScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QGridLayout(this);
    FinConLayout->setSpacing(4);

    auto fPanel = new QTableWidget(5, 2, this);
    fPanel->setHorizontalHeaderLabels({"Fundamentals", "Value"});
    fPanel->setItem(0, 0, new QTableWidgetItem("P/E Ratio")); fPanel->setItem(0, 1, new QTableWidgetItem("28.4"));
    fPanel->setItem(1, 0, new QTableWidgetItem("Market Cap")); fPanel->setItem(1, 1, new QTableWidgetItem("2.8T"));
    fPanel->setItem(2, 0, new QTableWidgetItem("EPS")); fPanel->setItem(2, 1, new QTableWidgetItem("6.15"));
    FinConLayout->addWidget(fPanel, 0, 0);

    auto tPanel = new QLabel("Technicals: RSI(14): 58.2 | MACD: Bullish Cross", this);
    tPanel->setAlignment(Qt::AlignCenter);
    FinConLayout->addWidget(tPanel, 0, 1);

    auto pPanel = new QTableWidget(5, 3, this);
    pPanel->setHorizontalHeaderLabels({"Peer", "Price", "Cap"});
    pPanel->setItem(0, 0, new QTableWidgetItem("MSFT")); pPanel->setItem(0, 1, new QTableWidgetItem("420.10"));
    pPanel->setItem(1, 0, new QTableWidgetItem("GOOGL")); pPanel->setItem(1, 1, new QTableWidgetItem("175.40"));
    FinConLayout->addWidget(pPanel, 1, 0);

    auto sPanel = new QLabel("Sentiment: 82% Positive (Top News: Strong Earnings Beat)", this);
    sPanel->setAlignment(Qt::AlignCenter);
    FinConLayout->addWidget(sPanel, 1, 1);
}

FinConPortfolioScreen::FinConPortfolioScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QVBoxLayout(this);
    auto FinConTable = new QTableWidget(10, 5, this);
    FinConTable->setHorizontalHeaderLabels({"Holding", "Qty", "Avg Price", "Current", "P&L"});
    FinConLayout->addWidget(FinConTable);
}

FinConNewsScreen::FinConNewsScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QVBoxLayout(this);
    auto newsList = new QListWidget(this);
    newsList->addItem("09:45 - US Tech rally continues on strong earnings");
    newsList->addItem("09:30 - Markets open higher across all major indices");
    newsList->addItem("09:00 - Central Bank hints at potential rate cuts in Q4");
    FinConLayout->addWidget(newsList);
}

FinConTradingScreen::FinConTradingScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QGridLayout(this);
    FinConLayout->addWidget(new QLabel("Symbol:"), 0, 0);
    FinConLayout->addWidget(new QLineEdit("AAPL", this), 0, 1);
    FinConLayout->addWidget(new QLabel("Quantity:"), 1, 0);
    FinConLayout->addWidget(new QLineEdit("100", this), 1, 1);
    FinConLayout->addWidget(new QPushButton("Buy", this), 2, 0);
    FinConLayout->addWidget(new QPushButton("Sell", this), 2, 1);
}

FinConExcelScreen::FinConExcelScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QVBoxLayout(this);
    auto FinConTable = new QTableWidget(50, 26, this);
    FinConLayout->addWidget(FinConTable);
}

FinConCodeEditorScreen::FinConCodeEditorScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QVBoxLayout(this);
    auto editor = new QTextEdit(this);
    editor->setPlaceholderText("// Write your custom analytics script here (C++/Python)");
    FinConLayout->addWidget(editor);
}

FinConAboutScreen::FinConAboutScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QVBoxLayout(this);
    FinConLayout->addWidget(new QLabel("FinCon Terminal v4.0.3", this));
    FinConLayout->addWidget(new QLabel("Professional-grade financial desktop platform.", this));
    FinConLayout->addWidget(new QLabel("© 2026 FinCon Corporation. All rights reserved.", this));
}

}

FinConCryptoTradingScreen::FinConCryptoTradingScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QVBoxLayout(this);
    FinConLayout->addWidget(new QLabel("Crypto Trading Hub - Connect to Kraken/HyperLiquid", this));
    auto FinConTable = new QTableWidget(5, 3, this);
    FinConTable->setHorizontalHeaderLabels({"Pair", "Bid", "Ask"});
    FinConLayout->addWidget(FinConTable);
}

FinConAlgoTradingScreen::FinConAlgoTradingScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QVBoxLayout(this);
    FinConLayout->addWidget(new QLabel("Algo Trading Dashboard", this));
    auto FinConTable = new QTableWidget(5, 4, this);
    FinConTable->setHorizontalHeaderLabels({"Strategy", "Status", "PnL", "Logs"});
    FinConLayout->addWidget(FinConTable);
}

FinConEconomicsScreen::FinConEconomicsScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QVBoxLayout(this);
    FinConLayout->addWidget(new QLabel("Global Economic Indicators", this));
    auto FinConTable = new QTableWidget(10, 3, this);
    FinConTable->setHorizontalHeaderLabels({"Indicator", "Value", "Release Date"});
    FinConLayout->addWidget(FinConTable);
}

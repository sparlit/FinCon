#include "Screens.h"
#include "core/DataHub.h"
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

namespace FinConScreens {

FinConDashboardScreen::FinConDashboardScreen(QWidget* parent) : IFinConScreen(parent) {
    auto layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Dashboard Widget Grid (Customizable)", this));
    auto table = new QTableWidget(5, 3, this);
    table->setHorizontalHeaderLabels({"Asset", "Price", "Change"});
    table->setItem(0, 0, new QTableWidgetItem("BTC/USD"));
    table->setItem(0, 1, new QTableWidgetItem("65000.00"));
    layout->addWidget(table);
}

FinConMarketsScreen::FinConMarketsScreen(QWidget* parent) : IFinConScreen(parent) {
    auto layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Global Markets Overview", this));

    view_ = new QTableView(this);
    model_ = new FinConCore::FinConMarketModel(this);
    view_->setModel(model_);
    layout->addWidget(view_);

    FinConCore::FinConDataHub::instance().subscribe("quote/*", this, [this](const QJsonDocument& doc) {
        model_->updateQuote(doc.object());
    });
}

FinConAIChatScreen::FinConAIChatScreen(QWidget* parent) : IFinConScreen(parent) {
    auto layout = new QVBoxLayout(this);
    auto chatArea = new QTextEdit(this);
    chatArea->setReadOnly(true);
    auto input = new QLineEdit(this);
    auto send = new QPushButton("Send", this);

    layout->addWidget(chatArea);
    auto hLayout = new QHBoxLayout();
    hLayout->addWidget(input);
    hLayout->addWidget(send);
    layout->addLayout(hLayout);
}

}

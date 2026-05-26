#include "Screens.h"
#include <QVBoxLayout>
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
    auto table = new QTableWidget(10, 4, this);
    table->setHorizontalHeaderLabels({"Market", "Last", "Change", "% Change"});
    layout->addWidget(table);
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

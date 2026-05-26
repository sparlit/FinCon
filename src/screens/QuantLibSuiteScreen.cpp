#include "QuantLibSuiteScreen.h"
#include <QVBoxLayout>
#include <QLabel>

namespace FinConScreens {

FinConQuantLibSuiteScreen::FinConQuantLibSuiteScreen(QWidget* parent) : IFinConScreen(parent) {
    auto layout = new QVBoxLayout(this);

    toolSelector_ = new QComboBox(this);
    toolSelector_->addItems({
        "Yield Curves", "Black-Scholes", "Binomial Trees", "Monte Carlo",
        "VaR", "CVaR", "Duration", "Convexity", "Volatility Surface",
        "OAS", "Efficient Frontier", "Bond Pricing", "Swap Valuation",
        "Credit Default Swaps", "Option Greeks", "Heston Model",
        "CAPM", "Black-Litterman"
    });

    layout->addWidget(new QLabel("Select Analytics Tool:", this));
    layout->addWidget(toolSelector_);

    resultsTable_ = new QTableWidget(10, 2, this);
    resultsTable_->setHorizontalHeaderLabels({"Parameter", "Value"});
    layout->addWidget(resultsTable_);

    connect(toolSelector_, qOverload<int>(&QComboBox::currentIndexChanged), this, &FinConQuantLibSuiteScreen::onToolChanged);
    onToolChanged(0);
}

void FinConQuantLibSuiteScreen::onToolChanged(int index) {
    resultsTable_->clearContents();
    QString tool = toolSelector_->itemText(index);

    if (tool == "Black-Scholes") {
        resultsTable_->setItem(0, 0, new QTableWidgetItem("Call Price"));
        resultsTable_->setItem(0, 1, new QTableWidgetItem("5.42"));
    }
}

}

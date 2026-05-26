#include "QuantLibSuiteScreen.h"
#include <QVBoxLayout>
#include <QLabel>

namespace screens {

QuantLibSuiteScreen::QuantLibSuiteScreen(QWidget* parent) : IScreen(parent) {
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

    connect(toolSelector_, qOverload<int>(&QComboBox::currentIndexChanged), this, &QuantLibSuiteScreen::onToolChanged);
    onToolChanged(0);
}

void QuantLibSuiteScreen::onToolChanged(int index) {
    resultsTable_->clearContents();
    QString tool = toolSelector_->itemText(index);

    if (tool == "Black-Scholes") {
        resultsTable_->setItem(0, 0, new QTableWidgetItem("Call Price"));
        resultsTable_->setItem(0, 1, new QTableWidgetItem("5.42"));
        resultsTable_->setItem(1, 0, new QTableWidgetItem("Delta"));
        resultsTable_->setItem(1, 1, new QTableWidgetItem("0.65"));
        resultsTable_->setItem(2, 0, new QTableWidgetItem("Gamma"));
        resultsTable_->setItem(2, 1, new QTableWidgetItem("0.02"));
    } else if (tool == "Yield Curves") {
        resultsTable_->setItem(0, 0, new QTableWidgetItem("1Y"));
        resultsTable_->setItem(0, 1, new QTableWidgetItem("4.5%"));
        resultsTable_->setItem(1, 0, new QTableWidgetItem("5Y"));
        resultsTable_->setItem(1, 1, new QTableWidgetItem("4.2%"));
        resultsTable_->setItem(2, 0, new QTableWidgetItem("10Y"));
        resultsTable_->setItem(2, 1, new QTableWidgetItem("4.0%"));
    }
    // ... further mock values for other tools
}

}

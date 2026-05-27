#include "QuantLibSuiteScreen.h"
#include <QVBoxLayout>
#include <QLabel>

namespace FinConScreens {

FinConQuantLibSuiteScreen::FinConQuantLibSuiteScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QVBoxLayout(this);

    FinConQuant_ToolSelector = new QComboBox(this);
    FinConQuant_ToolSelector->addItems({
        "Yield Curves", "Black-Scholes", "Binomial Trees", "Monte Carlo",
        "VaR", "CVaR", "Duration", "Convexity", "Volatility Surface",
        "OAS", "Efficient Frontier", "Bond Pricing", "Swap Valuation",
        "Credit Default Swaps", "Option Greeks", "Heston Model",
        "CAPM", "Black-Litterman"
    });

    FinConLayout->addWidget(new QLabel("Select Analytics Tool:", this));
    FinConLayout->addWidget(FinConQuant_ToolSelector);

    FinConQuant_ResultsTable = new QTableWidget(10, 2, this);
    FinConQuant_ResultsTable->setHorizontalHeaderLabels({"Parameter", "Value"});
    FinConLayout->addWidget(FinConQuant_ResultsTable);

    connect(FinConQuant_ToolSelector, qOverload<int>(&QComboBox::currentIndexChanged), this, &FinConQuantLibSuiteScreen::onToolChanged);
    onToolChanged(0);
}

void FinConQuantLibSuiteScreen::onToolChanged(int FinConIdx_General) {
    FinConQuant_ResultsTable->clearContents();
    QString FinConStr_Tool = FinConQuant_ToolSelector->itemText(FinConIdx_General);

    if (FinConStr_Tool == "Black-Scholes") {
        FinConQuant_ResultsTable->setItem(0, 0, new QTableWidgetItem("Call Price"));
        FinConQuant_ResultsTable->setItem(0, 1, new QTableWidgetItem("5.42"));
    }
}

}

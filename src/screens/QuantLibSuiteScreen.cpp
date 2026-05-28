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

    auto setRow = [&](int row, const QString& param, const QString& val) {
        FinConQuant_ResultsTable->setItem(row, 0, new QTableWidgetItem(param));
        FinConQuant_ResultsTable->setItem(row, 1, new QTableWidgetItem(val));
    };

    if (FinConStr_Tool == "Yield Curves") {
        setRow(0, "10Y Treasury", "4.25%"); setRow(1, "2Y Treasury", "4.62%"); setRow(2, "Spread (10Y-2Y)", "-0.37%");
    } else if (FinConStr_Tool == "Black-Scholes") {
        setRow(0, "Call Price", "5.42"); setRow(1, "Delta", "0.65"); setRow(2, "Gamma", "0.04"); setRow(3, "Vega", "0.12");
    } else if (FinConStr_Tool == "Binomial Trees") {
        setRow(0, "Price (Steps=100)", "5.41"); setRow(1, "Convergence Error", "0.002");
    } else if (FinConStr_Tool == "Monte Carlo") {
        setRow(0, "Price (Paths=100k)", "5.43"); setRow(1, "Std Error", "0.005");
    } else if (FinConStr_Tool == "VaR") {
        setRow(0, "95% VaR (1D)", "$2.4M"); setRow(1, "99% VaR (1D)", "$3.8M");
    } else if (FinConStr_Tool == "CVaR") {
        setRow(0, "95% Expected Shortfall", "$3.1M");
    } else if (FinConStr_Tool == "Duration") {
        setRow(0, "Macaulay Duration", "7.2 Yrs"); setRow(1, "Modified Duration", "6.8%");
    } else if (FinConStr_Tool == "Convexity") {
        setRow(0, "Portfolio Convexity", "0.45");
    } else if (FinConStr_Tool == "Volatility Surface") {
        setRow(0, "ATM Vol (1M)", "18.2%"); setRow(1, "Skew (25D)", "2.1%");
    } else if (FinConStr_Tool == "OAS") {
        setRow(0, "Option Adjusted Spread", "125 bps");
    } else if (FinConStr_Tool == "Efficient Frontier") {
        setRow(0, "Max Sharpe Return", "12.4%"); setRow(1, "Max Sharpe Risk", "8.2%");
    } else {
        setRow(0, "Status", "Engine Initialized");
        setRow(1, "Result", "Mock Data Ready");
    }
}

}

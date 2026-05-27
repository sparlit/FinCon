#pragma once
#include "IScreen.h"
#include <QTableWidget>
#include <QTableView>
#include "core/MarketModel.h"

namespace FinConScreens {

class FinConDashboardScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConDashboardScreen(QWidget* parent = nullptr);
};

class FinConMarketsScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConMarketsScreen(QWidget* parent = nullptr);
private:
    QTableView* view_;
    FinConCore::FinConMarketModel* model_;
};

class FinConAIChatScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConAIChatScreen(QWidget* parent = nullptr);
};

class FinConEquityResearchScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConEquityResearchScreen(QWidget* parent = nullptr);
};

class FinConPortfolioScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConPortfolioScreen(QWidget* parent = nullptr);
};

}

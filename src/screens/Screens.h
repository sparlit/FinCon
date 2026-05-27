#pragma once
#include "IScreen.h"
#include <QTableWidget>
#include <QTableView>
#include "core/FinConMarketModel.h"

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
    FinConCore::FinConFinConMarketModel* model_;
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

class FinConNewsScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConNewsScreen(QWidget* parent = nullptr);
};

class FinConTradingScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConTradingScreen(QWidget* parent = nullptr);
};

class FinConExcelScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConExcelScreen(QWidget* parent = nullptr);
};

class FinConCodeEditorScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConCodeEditorScreen(QWidget* parent = nullptr);
};

class FinConAboutScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConAboutScreen(QWidget* parent = nullptr);
};

}

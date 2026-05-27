#pragma once
#include "IScreen.h"
#include <QTableWidget>
#include <QTableView>
#include "core/FinConMarketModel.h"

namespace FinConScreens {

class FinConDashboardScreen : public FinConScreens::IFinConScreen {
    Q_OBJECT
public:
    FinConDashboardScreen(QWidget* parent = nullptr);
};

class FinConMarketsScreen : public FinConScreens::IFinConScreen {
    Q_OBJECT
public:
    FinConMarketsScreen(QWidget* parent = nullptr);
private:
    QTableView* FinConNode_View;
    FinConCore::FinConMarketModel* model_;
};

class FinConAIChatScreen : public FinConScreens::IFinConScreen {
    Q_OBJECT
public:
    FinConAIChatScreen(QWidget* parent = nullptr);
};

class FinConEquityResearchScreen : public FinConScreens::IFinConScreen {
    Q_OBJECT
public:
    FinConEquityResearchScreen(QWidget* parent = nullptr);
};

class FinConPortfolioScreen : public FinConScreens::IFinConScreen {
    Q_OBJECT
public:
    FinConPortfolioScreen(QWidget* parent = nullptr);
};

class FinConNewsScreen : public FinConScreens::IFinConScreen {
    Q_OBJECT
public:
    FinConNewsScreen(QWidget* parent = nullptr);
};

class FinConTradingScreen : public FinConScreens::IFinConScreen {
    Q_OBJECT
public:
    FinConTradingScreen(QWidget* parent = nullptr);
};

class FinConExcelScreen : public FinConScreens::IFinConScreen {
    Q_OBJECT
public:
    FinConExcelScreen(QWidget* parent = nullptr);
};

class FinConCodeEditorScreen : public FinConScreens::IFinConScreen {
    Q_OBJECT
public:
    FinConCodeEditorScreen(QWidget* parent = nullptr);
};

class FinConAboutScreen : public FinConScreens::IFinConScreen {
    Q_OBJECT
public:
    FinConAboutScreen(QWidget* parent = nullptr);
};

class FinConCryptoTradingScreen : public FinConScreens::IFinConScreen {
    Q_OBJECT
public:
    FinConCryptoTradingScreen(QWidget* parent = nullptr);
};

class FinConAlgoTradingScreen : public FinConScreens::IFinConScreen {
    Q_OBJECT
public:
    FinConAlgoTradingScreen(QWidget* parent = nullptr);
};

class FinConEconomicsScreen : public FinConScreens::IFinConScreen {
    Q_OBJECT
public:
    FinConEconomicsScreen(QWidget* parent = nullptr);
};

}

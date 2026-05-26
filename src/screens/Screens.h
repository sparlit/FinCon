#pragma once
#include "IScreen.h"
#include <QTableWidget>

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
};

class FinConAIChatScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConAIChatScreen(QWidget* parent = nullptr);
};

}

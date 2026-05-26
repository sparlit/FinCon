#pragma once
#include "IScreen.h"
#include <QTableWidget>

namespace screens {

class DashboardScreen : public IScreen {
    Q_OBJECT
public:
    DashboardScreen(QWidget* parent = nullptr);
};

class MarketsScreen : public IScreen {
    Q_OBJECT
public:
    MarketsScreen(QWidget* parent = nullptr);
};

class AIChatScreen : public IScreen {
    Q_OBJECT
public:
    AIChatScreen(QWidget* parent = nullptr);
};

// ... more screens
}

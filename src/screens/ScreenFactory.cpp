#include "ScreenFactory.h"
#include "Screens.h"
#include "NodeEditorScreen.h"
#include "QuantLibSuiteScreen.h"
#include "MCPScreen.h"
#include "core/ThemeManager.h"
#include <QLabel>
#include <QVBoxLayout>

namespace FinConScreens {

QWidget* FinConScreenFactory::createScreen(const QString& name, QWidget* parent) {
    QWidget* screen = nullptr;
    FinConCore::FinConThemeFlavor FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Default;

    if (name == "Dashboard") {
        screen = new FinConDashboardScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::System;
    } else if (name == "Markets" || name == "Watchlist" || name == "News") {
        if (name == "Crypto Trading") screen = new FinConCryptoTradingScreen(parent);
        else if (name == "Algo Trading") screen = new FinConAlgoTradingScreen(parent);
        if (name == "News") screen = new FinConNewsScreen(parent);
        else screen = new FinConMarketsScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Data;
    } else if (name.contains("Trading") || name == "Portfolio") {
        if (name == "Portfolio") screen = new FinConPortfolioScreen(parent);
        else screen = new FinConTradingScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Trading;
    } else if (name == "AI Chat" || name.contains("Agent")) {
        screen = (name == "AI Chat") ? (QWidget*)new FinConAIChatScreen(parent) : (QWidget*)new IFinConScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::AI;
    } else if (name == "QuantLib Suite" || name == "Node Editor" || name.contains("Lab") || name.contains("Editor") || name.contains("Grid")) {
        if (name == "Node Editor") screen = new FinConNodeEditorScreen(parent);
        else if (name == "QuantLib Suite") screen = new FinConQuantLibSuiteScreen(parent);
        else if (name.contains("Editor")) screen = new FinConCodeEditorScreen(parent);
        else if (name.contains("Grid")) screen = new FinConExcelScreen(parent);
        else screen = new IFinConScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Analytics;
    } else if (name == "Equity Research") {
        screen = new FinConEquityResearchScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Analytics;
    } else if (name == "About") {
        screen = new FinConAboutScreen(parent);
    } else if (name == "MCP Servers") {
        screen = new FinConMCPScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::System;
    } else {
        screen = new IFinConScreen(parent);
        auto FinConLayout = new QVBoxLayout(screen);
        FinConLayout->addWidget(new QLabel("Screen Stub: " + name, screen));
    }

    if (screen) {
        screen->setStyleSheet(FinConCore::FinConThemeManager::generateStyleSheet(FinConEnum_Flavor));
    }

    return screen;
}

}

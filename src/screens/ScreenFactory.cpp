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
        if (name == "News") screen = new FinConNewsScreen(parent);
        else screen = new FinConMarketsScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Data;
    } else if (name == "Crypto Trading") {
        screen = new FinConCryptoTradingScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Trading;
    } else if (name == "Algo Trading") {
        screen = new FinConAlgoTradingScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Trading;
    } else if (name == "Economics") {
        screen = new FinConEconomicsScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Data;
    } else if (name == "Portfolio") {
        screen = new FinConPortfolioScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Trading;
    } else if (name == "AI Chat") {
        screen = new FinConAIChatScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::AI;
    } else if (name == "Node Editor") {
        screen = new FinConNodeEditorScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Analytics;
    } else if (name == "QuantLib Suite") {
        screen = new FinConQuantLibSuiteScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Analytics;
    } else if (name == "Equity Research") {
        screen = new FinConEquityResearchScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Analytics;
    } else if (name == "MCP Servers") {
        screen = new FinConMCPScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::System;
    } else if (name == "Excel Grid") {
        screen = new FinConExcelScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Analytics;
    } else if (name == "Code Editor") {
        screen = new FinConCodeEditorScreen(parent);
        FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Analytics;
    } else if (name == "About") {
        screen = new FinConAboutScreen(parent);
    } else {
        // Handle the remaining ~25 screens via Generic Data Screen
        QString topic = "data/" + name.toLower().replace(" ", "_");
        screen = new FinConGenericDataScreen(name, topic, parent);
        if (name.contains("Market") || name.contains("Data") || name == "Maritime" || name == "Geopolitics")
            FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Data;
        else if (name.contains("Agent") || name.contains("Lab") || name == "Alpha Arena")
            FinConEnum_Flavor = FinConCore::FinConThemeFlavor::AI;
        else
            FinConEnum_Flavor = FinConCore::FinConThemeFlavor::Default;
    }

    if (screen) {
        screen->setStyleSheet(FinConCore::FinConThemeManager::generateStyleSheet(FinConEnum_Flavor));
    }

    return screen;
}

}

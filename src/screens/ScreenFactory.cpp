#include "ScreenFactory.h"
#include "Screens.h"
#include "NodeEditorScreen.h"
#include "QuantLibSuiteScreen.h"
#include <QLabel>
#include <QVBoxLayout>

namespace FinConScreens {

QWidget* FinConScreenFactory::createScreen(const QString& name, QWidget* parent) {
    if (name == "Dashboard") return new FinConDashboardScreen(parent);
    if (name == "Markets") return new FinConMarketsScreen(parent);
    if (name == "AI Chat") return new FinConAIChatScreen(parent);
    if (name == "Node Editor") return new FinConNodeEditorScreen(parent);
    if (name == "QuantLib Suite") return new FinConQuantLibSuiteScreen(parent);
    if (name == "Equity Research") return new FinConEquityResearchScreen(parent);
    if (name == "Portfolio") return new FinConPortfolioScreen(parent);

    auto screen = new IFinConScreen(parent);
    auto layout = new QVBoxLayout(screen);
    layout->addWidget(new QLabel("Screen Stub: " + name, screen));
    return screen;
}

}

#include "ScreenFactory.h"
#include "Screens.h"
#include "NodeEditorScreen.h"
#include "QuantLibSuiteScreen.h"
#include <QLabel>
#include <QVBoxLayout>

namespace screens {

QWidget* ScreenFactory::createScreen(const QString& name, QWidget* parent) {
    if (name == "Dashboard") return new DashboardScreen(parent);
    if (name == "Markets") return new MarketsScreen(parent);
    if (name == "AI Chat") return new AIChatScreen(parent);
    if (name == "Node Editor") return new NodeEditorScreen(parent);
    if (name == "QuantLib Suite") return new QuantLibSuiteScreen(parent);

    // Generic stub for others
    auto screen = new IScreen(parent);
    auto layout = new QVBoxLayout(screen);
    layout->addWidget(new QLabel("Screen: " + name, screen));
    return screen;
}

}

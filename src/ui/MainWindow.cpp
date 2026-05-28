#include "MainWindow.h"
#include "screens/ScreenFactory.h"
#include <QVBoxLayout>
#include <QShortcut>
#include <QKeySequence>
#include <QAction>

namespace FinConUI {

FinConMainWindow::FinConMainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUi();
}

void FinConMainWindow::setupUi() {
    FinConMain_DockManager = new ads::CDockManager(this);

    FinConMain_NavBar = new FinConNavigationBar(this);
    setMenuWidget(FinConMain_NavBar);

    FinConMain_Sidebar = new FinConSidebar(this);
    addDockWidget(Qt::LeftDockWidgetArea, FinConMain_Sidebar);

    FinConMain_StatusBar = new FinConStatusBar(this);
    setStatusBar(FinConMain_StatusBar);

    FinConMain_WorkspaceToolBar = new QToolBar("Workspace", this);
    auto* appleAction = FinConMain_WorkspaceToolBar->addAction("Pin AAPL");
    auto* teslaAction = FinConMain_WorkspaceToolBar->addAction("Pin TSLA");
    FinConMain_WorkspaceToolBar->addSeparator();
    FinConMain_WorkspaceToolBar->addAction("Default Layout");
    FinConMain_WorkspaceToolBar->addAction("Compact Layout");
    addToolBar(Qt::TopToolBarArea, FinConMain_WorkspaceToolBar);

    FinConMain_CommandBar = new FinConCommandBar(this);
    FinConMain_CommandBar->hide();

    connect(FinConMain_Sidebar, &FinConSidebar::screenRequested, this, &FinConMainWindow::onScreenRequested);
    connect(FinConMain_CommandBar, &FinConCommandBar::actionTriggered, this, &FinConMainWindow::onScreenRequested);

    connect(appleAction, &QAction::triggered, [this](){ onScreenRequested("Markets"); });
    connect(teslaAction, &QAction::triggered, [this](){ onScreenRequested("Markets"); });

    new QShortcut(QKeySequence("Ctrl+K"), this, SLOT(showCommandBar()));
}

void FinConMainWindow::onScreenRequested(const QString& screenName) {
    QWidget* screen = FinConScreens::FinConScreenFactory::createScreen(screenName, this);
    if (screen) {
        ads::CDockWidget* dockWidget = new ads::CDockWidget(screenName);
        dockWidget->setWidget(screen);
        FinConMain_DockManager->addDockWidget(ads::CenterDockWidgetArea, dockWidget);
    }
}

void FinConMainWindow::showCommandBar() {
    FinConMain_CommandBar->show();
    FinConMain_CommandBar->setFocus();
}

}

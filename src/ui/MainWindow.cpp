#include "MainWindow.h"
#include "screens/ScreenFactory.h"
#include <QVBoxLayout>
#include <QShortcut>
#include <QKeySequence>

namespace ui {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUi();
}

void MainWindow::setupUi() {
    dockManager_ = new ads::CDockManager(this);

    navBar_ = new NavigationBar(this);
    setMenuWidget(navBar_);

    sidebar_ = new Sidebar(this);
    addDockWidget(Qt::LeftDockWidgetArea, sidebar_);

    statusBar_ = new StatusBar(this);
    setStatusBar(statusBar_);

    commandBar_ = new CommandBar(this);
    commandBar_->hide();

    connect(sidebar_, &Sidebar::screenRequested, this, &MainWindow::onScreenRequested);

    new QShortcut(QKeySequence("Ctrl+K"), this, SLOT(showCommandBar()));
}

void MainWindow::onScreenRequested(const QString& screenName) {
    QWidget* screen = screens::ScreenFactory::createScreen(screenName, this);
    if (screen) {
        ads::CDockWidget* dockWidget = new ads::CDockWidget(screenName);
        dockWidget->setWidget(screen);
        dockManager_->addDockWidget(ads::CenterDockWidgetArea, dockWidget);
    }
}

void MainWindow::showCommandBar() {
    commandBar_->show();
    commandBar_->setFocus();
}

}

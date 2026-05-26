#include "MainWindow.h"
#include "screens/ScreenFactory.h"
#include <QVBoxLayout>
#include <QShortcut>
#include <QKeySequence>

namespace FinConUI {

FinConMainWindow::FinConMainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUi();
}

void FinConMainWindow::setupUi() {
    dockManager_ = new ads::CDockManager(this);

    navBar_ = new FinConNavigationBar(this);
    setMenuWidget(navBar_);

    sidebar_ = new FinConSidebar(this);
    addDockWidget(Qt::LeftDockWidgetArea, sidebar_);

    statusBar_ = new FinConStatusBar(this);
    setStatusBar(statusBar_);

    commandBar_ = new FinConCommandBar(this);
    commandBar_->hide();

    connect(sidebar_, &FinConSidebar::screenRequested, this, &FinConMainWindow::onScreenRequested);

    new QShortcut(QKeySequence("Ctrl+K"), this, SLOT(showCommandBar()));
}

void FinConMainWindow::onScreenRequested(const QString& screenName) {
    QWidget* screen = FinConScreens::FinConScreenFactory::createScreen(screenName, this);
    if (screen) {
        ads::CDockWidget* dockWidget = new ads::CDockWidget(screenName);
        dockWidget->setWidget(screen);
        dockManager_->addDockWidget(ads::CenterDockWidgetArea, dockWidget);
    }
}

void FinConMainWindow::showCommandBar() {
    commandBar_->show();
    commandBar_->setFocus();
}

}

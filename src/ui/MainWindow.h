#pragma once
#include <QMainWindow>
#include <DockManager.h>
#include "NavigationBar.h"
#include "Sidebar.h"
#include "StatusBar.h"
#include "CommandBar.h"

namespace FinConUI {

class FinConMainWindow : public QMainWindow {
    Q_OBJECT
public:
    FinConMainWindow(QWidget* parent = nullptr);

private slots:
    void onScreenRequested(const QString& screenName);
    void showCommandBar();

private:
    void setupUi();
    ads::CDockManager* dockManager_;
    FinConNavigationBar* navBar_;
    FinConSidebar* sidebar_;
    FinConStatusBar* statusBar_;
    FinConCommandBar* commandBar_;
};

}

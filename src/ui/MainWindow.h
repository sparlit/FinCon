#pragma once
#include <QMainWindow>
#include <DockManager.h>
#include <QToolBar>
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
    ads::CDockManager* FinConMain_DockManager;
    FinConNavigationBar* FinConMain_NavBar;
    FinConSidebar* FinConMain_Sidebar;
    FinConStatusBar* FinConMain_StatusBar;
    FinConCommandBar* FinConMain_CommandBar;
    QToolBar* FinConMain_WorkspaceToolBar;
};

}

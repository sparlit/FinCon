#pragma once
#include <QMainWindow>
#include <DockManager.h>
#include "NavigationBar.h"
#include "Sidebar.h"
#include "StatusBar.h"
#include "CommandBar.h"

namespace ui {

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void onScreenRequested(const QString& screenName);
    void showCommandBar();

private:
    void setupUi();
    ads::CDockManager* dockManager_;
    NavigationBar* navBar_;
    Sidebar* sidebar_;
    StatusBar* statusBar_;
    CommandBar* commandBar_;
};

}

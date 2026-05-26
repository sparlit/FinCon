#include <QApplication>
#include <QDir>
#include "ui/MainWindow.h"
#include "core/ThemeManager.h"
#include "core/CrashHandler.h"
#include "core/Persistence.h"
#include "core/Logger.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "services/AuthService.h"

int main(int argc, char *argv[]) {
    core::CrashHandler::install();

    QApplication app(argc, argv);
    app.setApplicationName("FinCon Terminal");
    app.setOrganizationName("FinCon");

    if (!core::Persistence::instance().init()) {
        return 1;
    }

    app.setStyleSheet(core::ThemeManager::generateStyleSheet());

    // Login Dialog
    QDialog loginDlg;
    loginDlg.setWindowTitle("FinCon Terminal - Login");
    auto layout = new QVBoxLayout(&loginDlg);
    auto email = new QLineEdit(&loginDlg);
    email->setPlaceholderText("Email");
    auto password = new QLineEdit(&loginDlg);
    password->setEchoMode(QLineEdit::Password);
    password->setPlaceholderText("Password");
    auto loginBtn = new QPushButton("Login", &loginDlg);
    layout->addWidget(new QLabel("Welcome to FinCon Terminal"));
    layout->addWidget(email);
    layout->addWidget(password);
    layout->addWidget(loginBtn);

    QObject::connect(loginBtn, &QPushButton::clicked, [&]() {
        services::AuthService::instance().login(email->text(), password->text(), [&](auto res) {
            if (res) loginDlg.accept();
            else LOG_ERROR("Auth", "Login failed");
        });
    });

    if (loginDlg.exec() != QDialog::Accepted) {
        return 0;
    }

    ui::MainWindow w;
    w.showMaximized();
    return app.exec();
}

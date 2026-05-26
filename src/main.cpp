#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "ui/MainWindow.h"
#include "core/ThemeManager.h"
#include "core/CrashHandler.h"
#include "core/Persistence.h"
#include "core/Logger.h"
#include "services/AuthService.h"

int main(int argc, char *argv[]) {
    FinConCore::FinConCrashHandler::install();

    QApplication app(argc, argv);
    app.setApplicationName("FinCon Terminal");
    app.setOrganizationName("FinCon");

    if (!FinConCore::FinConPersistence::instance().init()) {
        return 1;
    }

    app.setStyleSheet(FinConCore::FinConThemeManager::generateStyleSheet());

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
        FinConServices::FinConAuthService::instance().login(email->text(), password->text(), [&](auto res) {
            if (res) loginDlg.accept();
        });
    });

    if (loginDlg.exec() != QDialog::Accepted) {
        return 0;
    }

    FinConUI::FinConMainWindow w;
    w.showMaximized();
    return app.exec();
}

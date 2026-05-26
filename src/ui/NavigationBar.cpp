#include "NavigationBar.h"
#include <QDateTime>
#include <QTimer>
#include <QPushButton>
#include "services/AuthService.h"

namespace FinConUI {

FinConNavigationBar::FinConNavigationBar(QWidget* parent) : QWidget(parent) {
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 5, 10, 5);

    QLabel* logo = new QLabel("FINCON TERMINAL", this);
    logo->setObjectName("title");
    layout->addWidget(logo);

    layout->addStretch();

    clockLabel_ = new QLabel(this);
    layout->addWidget(clockLabel_);

    userLabel_ = new QLabel(FinConServices::FinConAuthService::instance().username(), this);
    layout->addWidget(userLabel_);

    QPushButton* logout = new QPushButton("Logout", this);
    layout->addWidget(logout);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FinConNavigationBar::updateTime);
    timer->start(1000);
    updateTime();
}

void FinConNavigationBar::updateTime() {
    clockLabel_->setText(QDateTime::currentDateTime().toString("HH:mm:ss"));
}

}

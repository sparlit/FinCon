#include "NavigationBar.h"
#include <QDateTime>
#include <QTimer>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include "services/AuthService.h"

namespace FinConUI {

FinConNavigationBar::FinConNavigationBar(QWidget* parent) : QWidget(parent) {
    auto FinConLayout = new QHBoxLayout(this);
    FinConLayout->setContentsMargins(10, 5, 10, 5);

    QLabel* logo = new QLabel("FINCON TERMINAL", this);
    logo->setObjectName("title");
    FinConLayout->addWidget(logo);

    FinConLayout->addStretch();

    FinConNav_ClockLabel = new QLabel(this);
    FinConLayout->addWidget(FinConNav_ClockLabel);

    FinConNav_UserLabel = new QLabel(FinConServices::FinConAuthService::instance().username(), this);
    FinConLayout->addWidget(FinConNav_UserLabel);

    QPushButton* logout = new QPushButton("Logout", this);
    FinConLayout->addWidget(logout);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FinConNavigationBar::updateTime);
    timer->start(1000);
    updateTime();
}

void FinConNavigationBar::updateTime() {
    FinConNav_ClockLabel->setText(QDateTime::currentDateTime().toString("HH:mm:ss"));
}

}

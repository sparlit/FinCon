#pragma once
#include <QStatusBar>
#include <QLabel>

namespace ui {

class StatusBar : public QStatusBar {
    Q_OBJECT
public:
    StatusBar(QWidget* parent = nullptr);

private:
    QLabel* symbolLabel_;
    QLabel* statusLabel_;
};

}

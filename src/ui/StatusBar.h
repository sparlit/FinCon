#pragma once
#include <QStatusBar>
#include <QLabel>

namespace FinConUI {

class FinConStatusBar : public QStatusBar {
    Q_OBJECT
public:
    FinConStatusBar(QWidget* parent = nullptr);

private:
    QLabel* symbolLabel_;
    QLabel* statusLabel_;
};

}

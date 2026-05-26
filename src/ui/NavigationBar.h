#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

namespace FinConUI {

class FinConNavigationBar : public QWidget {
    Q_OBJECT
public:
    FinConNavigationBar(QWidget* parent = nullptr);

private slots:
    void updateTime();

private:
    QLabel* clockLabel_;
    QLabel* userLabel_;
};

}

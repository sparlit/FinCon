#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace ui {

class NavigationBar : public QWidget {
    Q_OBJECT
public:
    NavigationBar(QWidget* parent = nullptr);

private slots:
    void updateTime();

private:
    QLabel* clockLabel_;
    QLabel* userLabel_;
};

}

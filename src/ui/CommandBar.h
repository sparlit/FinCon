#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>

namespace FinConUI {

class FinConCommandBar : public QWidget {
    Q_OBJECT
public:
    FinConCommandBar(QWidget* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QLineEdit* input_;
    QListWidget* results_;
};

}

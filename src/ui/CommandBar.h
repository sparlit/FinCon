#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>

namespace ui {

class CommandBar : public QWidget {
    Q_OBJECT
public:
    CommandBar(QWidget* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QLineEdit* input_;
    QListWidget* results_;
};

}

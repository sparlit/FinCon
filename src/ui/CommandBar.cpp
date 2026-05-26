#include "CommandBar.h"
#include <QVBoxLayout>
#include <QKeyEvent>

namespace ui {

CommandBar::CommandBar(QWidget* parent) : QWidget(parent, Qt::FramelessWindowHint | Qt::Popup) {
    auto layout = new QVBoxLayout(this);
    input_ = new QLineEdit(this);
    input_->setPlaceholderText("Search screens or actions (Ctrl+K)...");

    results_ = new QListWidget(this);

    layout->addWidget(input_);
    layout->addWidget(results_);

    setFixedSize(600, 400);

    input_->installEventFilter(this);
}

bool CommandBar::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Escape) {
            hide();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

}

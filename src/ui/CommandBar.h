#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>

namespace FinConUI {

class FinConCommandBar : public QWidget {
    Q_OBJECT
public:
    FinConCommandBar(QWidget* parent = nullptr);

signals:
    void actionTriggered(const QString& action);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void onTextChanged(const QString& text);
    void onItemActivated(QListWidgetItem* item);

private:
    QLineEdit* FinConCommand_Input;
    QListWidget* FinConCommand_Results;
    QStringList FinConCommand_Actions;
};

}

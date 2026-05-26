#pragma once
#include <QString>
#include <QWidget>

namespace FinConScreens {

class FinConScreenFactory {
public:
    static QWidget* createScreen(const QString& name, QWidget* parent = nullptr);
};

}

#pragma once
#include <QString>
#include <QWidget>

namespace screens {

class ScreenFactory {
public:
    static QWidget* createScreen(const QString& name, QWidget* parent = nullptr);
};

}

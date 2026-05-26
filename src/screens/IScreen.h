#pragma once
#include <QWidget>
#include <QJsonObject>

namespace screens {

class IScreen : public QWidget {
    Q_OBJECT
public:
    explicit IScreen(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual ~IScreen();
    virtual QJsonObject saveState() const { return {}; }
    virtual void restoreState(const QJsonObject& state) {}
};

}

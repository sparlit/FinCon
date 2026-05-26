#pragma once
#include <QWidget>
#include <QJsonObject>

namespace FinConScreens {

class IFinConScreen : public QWidget {
    Q_OBJECT
public:
    explicit IFinConScreen(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual ~IFinConScreen();
    virtual QJsonObject saveState() const { return {}; }
    virtual void restoreState(const QJsonObject& state) {}
};

}

#pragma once
#include "IScreen.h"
#include <QGraphicsView>
#include <QGraphicsScene>

namespace FinConScreens {

class FinConNodeEditorScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConNodeEditorScreen(QWidget* parent = nullptr);

private:
    QGraphicsView* view_;
    QGraphicsScene* scene_;
};

}

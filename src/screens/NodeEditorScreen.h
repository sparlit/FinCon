#pragma once
#include "IScreen.h"
#include <QGraphicsView>
#include <QGraphicsScene>

namespace screens {

class NodeEditorScreen : public IScreen {
    Q_OBJECT
public:
    NodeEditorScreen(QWidget* parent = nullptr);

private:
    QGraphicsView* view_;
    QGraphicsScene* scene_;
};

}

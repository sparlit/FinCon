#pragma once
#include "IScreen.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>

namespace FinConScreens {

class FinConNodeEditorScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConNodeEditorScreen(QWidget* parent = nullptr);

private slots:
    void onExecuteWorkflow();

private:
    QGraphicsView* FinConNode_View;
    QGraphicsScene* FinConNode_Scene;
    QPushButton* FinConBtn_Execute;
};

}

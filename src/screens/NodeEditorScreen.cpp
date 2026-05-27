#include "core/Logger.h"
#include "NodeEditorScreen.h"
#include "core/DataHub.h"
#include <QVBoxLayout>

namespace FinConScreens {

FinConNodeEditorScreen::FinConNodeEditorScreen(QWidget* parent) : IFinConScreen(parent) {
    auto FinConLayout = new QVBoxLayout(this);
    FinConNode_Scene = new QGraphicsScene(this);
    FinConNode_View = new QGraphicsView(FinConNode_Scene, this);
    FinConNode_View->setRenderHint(QPainter::Antialiasing);

    FinConBtn_Execute = new QPushButton("Execute Workflow (DAG)", this);
    connect(FinConBtn_Execute, &QPushButton::clicked, this, &FinConNodeEditorScreen::onExecuteWorkflow);

    FinConLayout->addWidget(FinConNode_View);
    FinConLayout->addWidget(FinConBtn_Execute);

    FinConNode_Scene->addText("FinCon Node Editor - Construct DAGs here");
}

void FinConNodeEditorScreen::onExecuteWorkflow() {
    FINCON_LOG_INFO("NodeEditor", "Executing Workflow... Validating DAG");
    // Mock execution
    QJsonObject res;
    res["status"] = "success";
    res["output"] = "Strategy execution triggered via DataHub";
    FinConCore::FinConDataHub::instance().publish("agent/workflow/run", QJsonDocument(res), 60);
}

}

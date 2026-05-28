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

    // Audit Trail Logging
    QJsonObject audit;
    audit["timestamp"] = QDateTime::currentDateTime().toString();
    audit["user"] = "admin";
    audit["inputs"] = QJsonObject{{"market", "NYSE"}, {"strategy", "VWAP"}};

    // Mock execution
    QJsonObject res;
    res["status"] = "success";
    res["output"] = "Strategy execution triggered via DataHub";
    res["audit_trail"] = audit;

    FINCON_LOG_INFO("NodeEditor", "Workflow Audit: " + QJsonDocument(audit).toJson(QJsonDocument::Compact).toStdString());

    FinConCore::FinConDataHub::instance().publish("agent/workflow/run", QJsonDocument(res), 60);
}

}

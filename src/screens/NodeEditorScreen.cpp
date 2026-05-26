#include "NodeEditorScreen.h"
#include <QVBoxLayout>

namespace screens {

NodeEditorScreen::NodeEditorScreen(QWidget* parent) : IScreen(parent) {
    auto layout = new QVBoxLayout(this);
    scene_ = new QGraphicsScene(this);
    view_ = new QGraphicsView(scene_, this);
    view_->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(view_);

    scene_->addText("Node Editor - Drag & Drop nodes to create workflows");
}

}

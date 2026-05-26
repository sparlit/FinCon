#include "NodeEditorScreen.h"
#include <QVBoxLayout>

namespace FinConScreens {

FinConNodeEditorScreen::FinConNodeEditorScreen(QWidget* parent) : IFinConScreen(parent) {
    auto layout = new QVBoxLayout(this);
    scene_ = new QGraphicsScene(this);
    view_ = new QGraphicsView(scene_, this);
    view_->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(view_);

    scene_->addText("FinCon Node Editor");
}

}

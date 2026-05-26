#include "StatusBar.h"

namespace ui {

StatusBar::StatusBar(QWidget* parent) : QStatusBar(parent) {
    symbolLabel_ = new QLabel("Current Symbol: NONE", this);
    statusLabel_ = new QLabel("Data: LIVE", this);

    addPermanentWidget(symbolLabel_);
    addPermanentWidget(statusLabel_);
}

}

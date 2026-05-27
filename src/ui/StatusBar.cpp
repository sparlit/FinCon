#include "StatusBar.h"
#include <QJsonObject>
#include "core/DataHub.h"
#include <QJsonDocument>
#include <QJsonObject>

namespace FinConUI {

FinConStatusBar::FinConStatusBar(QWidget* parent) : QStatusBar(parent) {
    symbolLabel_ = new QLabel("Last Tick: NONE", this);
    statusLabel_ = new QLabel("DataHub: IDLE", this);

    addPermanentWidget(symbolLabel_);
    addPermanentWidget(statusLabel_);

    FinConCore::FinConDataHub::instance().subscribe("quote/*", this, [this](const QJsonDocument& doc) {
        QString symbol = doc.object()["symbol"].toString();
        double price = doc.object()["price"].toDouble();
        symbolLabel_->setText(QString("Last Tick: %1 @ %2").arg(symbol).arg(price, 0, 'f', 2));
        statusLabel_->setText("DataHub: ACTIVE");
    });
}

}

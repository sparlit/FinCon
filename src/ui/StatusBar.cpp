#include "StatusBar.h"
#include <QJsonObject>
#include "core/DataHub.h"
#include <QJsonDocument>
#include <QJsonObject>

namespace FinConUI {

FinConStatusBar::FinConStatusBar(QWidget* parent) : QStatusBar(parent) {
    FinConStatus_SymbolLabel = new QLabel("Last Tick: NONE", this);
    FinConStatus_StatusLabel = new QLabel("DataHub: IDLE", this);

    addPermanentWidget(FinConStatus_SymbolLabel);
    addPermanentWidget(FinConStatus_StatusLabel);

    FinConCore::FinConDataHub::instance().subscribe("quote/*", this, [this](const QJsonDocument& doc) {
        QString FinConStr_Symbol = doc.object()["FinConStr_Symbol"].toString();
        double FinConVal_Price = doc.object()["FinConVal_Price"].toDouble();
        FinConStatus_SymbolLabel->setText(QString("Last Tick: %1 @ %2").arg(FinConStr_Symbol).arg(FinConVal_Price, 0, 'f', 2));
        FinConStatus_StatusLabel->setText("DataHub: ACTIVE");
    });
}

}

#pragma once
#include "IScreen.h"
#include <QTableWidget>
#include <QComboBox>

namespace FinConScreens {

class FinConQuantLibSuiteScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConQuantLibSuiteScreen(QWidget* parent = nullptr);

private slots:
    void onToolChanged(int FinConIdx_General);

private:
    QComboBox* FinConQuant_ToolSelector;
    QTableWidget* FinConQuant_ResultsTable;
};

}

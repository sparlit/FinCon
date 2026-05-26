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
    void onToolChanged(int index);

private:
    QComboBox* toolSelector_;
    QTableWidget* resultsTable_;
};

}

#pragma once
#include "IScreen.h"
#include <QTableWidget>
#include <QComboBox>

namespace screens {

class QuantLibSuiteScreen : public IScreen {
    Q_OBJECT
public:
    QuantLibSuiteScreen(QWidget* parent = nullptr);

private slots:
    void onToolChanged(int index);

private:
    QComboBox* toolSelector_;
    QTableWidget* resultsTable_;
};

}

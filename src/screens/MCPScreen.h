#pragma once
#include "IScreen.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QLabel>

namespace FinConScreens {

class FinConMCPScreen : public IFinConScreen {
    Q_OBJECT
public:
    FinConMCPScreen(QWidget* parent = nullptr) : IFinConScreen(parent) {
        auto FinConLayout = new QVBoxLayout(this);
        auto FinConTable = new QTableWidget(10, 3, this);
        FinConTable->setHorizontalHeaderLabels({"Server/Skill", "Provider", "Status"});

        QStringList skills = {
            "react-best-practices", "next-best-practices", "web-design-guidelines",
            "vercel-deploy", "building-secure-contracts", "semgrep-rule-creator",
            "static-analysis", "hugging-face-cli", "sentry-code-review", "stripe-payments"
        };

        for(int i=0; i<skills.size(); ++i) {
            FinConTable->setItem(i, 0, new QTableWidgetItem(skills[i]));
            FinConTable->setItem(i, 1, new QTableWidgetItem("MCP Market"));
            FinConTable->setItem(i, 2, new QTableWidgetItem("Available"));
        }

        FinConLayout->addWidget(new QLabel("MCP Servers & Agent Skills (from mcpmarket.com)"));
        FinConLayout->addWidget(FinConTable);
    }
};

}

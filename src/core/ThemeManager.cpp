#include "ThemeManager.h"

namespace FinConCore {

FinConThemeTokens FinConThemeManager::tokens() {
    return FinConThemeTokens();
}

QString FinConThemeManager::generateStyleSheet() {
    FinConThemeTokens t = tokens();
    QString qss = R"(
        QWidget {
            background-color: %bg_base%;
            color: %text_primary%;
            font-family: 'Consolas', 'Courier New', monospace;
            font-size: %base_fs%px;
        }
        QMainWindow, QDialog {
            background-color: %bg_base%;
        }
        QMenuBar, QMenu {
            background-color: %bg_surface%;
            color: %text_primary%;
        }
        QMenuBar::item:selected, QMenu::item:selected {
            background-color: %bg_raised%;
        }
        QPushButton {
            background-color: %bg_raised%;
            border: 1px solid %bg_raised%;
            padding: 4px 8px;
            color: %text_primary%;
        }
        QPushButton:hover {
            background-color: %bg_surface%;
        }
        QLineEdit, QTextEdit {
            background-color: %bg_surface%;
            border: 1px solid %bg_raised%;
            color: %text_primary%;
        }
        QHeaderView::section {
            background-color: %bg_surface%;
            color: %text_secondary%;
            padding: 4px;
            border: 1px solid %bg_raised%;
        }
        QTableWidget {
            gridline-color: %bg_raised%;
            background-color: %bg_base%;
        }
        QStatusBar {
            background-color: %bg_surface%;
            color: %text_secondary%;
        }
        QLabel#title { font-size: %title_fs%px; font-weight: bold; }
        QLabel#heading { font-size: %heading_fs%px; font-weight: bold; }
        QLabel#caption { font-size: %caption_fs%px; color: %text_secondary%; }

        /* ADS Specific overrides */
        ads--CDockContainerWidget {
            background-color: %bg_base%;
        }
        ads--CDockWidget {
            background-color: %bg_surface%;
        }
        ads--CDockAreaWidget {
            background-color: %bg_base%;
        }
        ads--CDockAreaTitleBar {
            background-color: %bg_raised%;
        }
    )";
    return qss
        .replace("%bg_base%", t.bg_base)
        .replace("%bg_surface%", t.bg_surface)
        .replace("%bg_raised%", t.bg_raised)
        .replace("%text_primary%", t.text_primary)
        .replace("%text_secondary%", t.text_secondary)
        .replace("%accent_amber%", t.accent_amber)
        .replace("%positive_green%", t.positive_green)
        .replace("%negative_red%", t.negative_red)
        .replace("%base_fs%", QString::number(t.font_size_base))
        .replace("%title_fs%", QString::number(t.font_size_title))
        .replace("%heading_fs%", QString::number(t.font_size_heading))
        .replace("%caption_fs%", QString::number(t.font_size_caption));
}

}

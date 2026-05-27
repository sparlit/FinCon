#include "ThemeManager.h"

namespace FinConCore {

FinConThemeTokens FinConThemeManager::tokens(FinConThemeFlavor flavor, FinConThemeDensity density) {
    FinConThemeTokens t;
    switch(flavor) {
        case FinConThemeFlavor::Trading:   t.accent_amber = "#3b82f6"; break;
        case FinConThemeFlavor::Analytics: t.accent_amber = "#8b5cf6"; break;
        case FinConThemeFlavor::Data:      t.accent_amber = "#06b6d4"; break;
        case FinConThemeFlavor::System:    t.accent_amber = "#f43f5e"; break;
        case FinConThemeFlavor::AI:        t.accent_amber = "#ec4899"; break;
        default: break;
    }
    return t;
}

QString FinConThemeManager::generateStyleSheet(FinConThemeFlavor flavor, FinConThemeDensity density) {
    FinConThemeTokens t = tokens(flavor, density);
    int padding = 4;
    if (density == FinConThemeDensity::Compact) padding = 2;
    if (density == FinConThemeDensity::Comfortable) padding = 8;

    QString qss = R"(
        QWidget {
            background-color: %bg_base%;
            color: %text_primary%;
            font-family: 'Noto Sans Mono', 'DejaVu Sans Mono', 'Consolas', monospace;
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
            border: 2px solid %accent_amber%;
            border-radius: 4px;
            padding: %padding%px %padding_double%px;
            color: %text_primary%;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: %accent_amber%;
            color: #000000;
        }
        QLineEdit, QTextEdit {
            background-color: %bg_surface%;
            border: 1px solid %bg_raised%;
            border-radius: 2px;
            color: %text_primary%;
            padding: %padding%px;
        }
        QHeaderView::section {
            background-color: %bg_surface%;
            color: %accent_amber%;
            padding: %padding%px;
            border: 1px solid %bg_raised%;
            font-weight: bold;
        }
        QTableWidget, QTableView {
            gridline-color: %bg_raised%;
            background-color: %bg_base%;
            alternate-background-color: #121212;
            selection-background-color: %accent_amber%;
            selection-color: #000000;
        }
        QStatusBar {
            background-color: %bg_surface%;
            color: %text_secondary%;
        }
        QLabel#title { font-size: %title_fs%px; font-weight: bold; color: %accent_amber%; }
        QLabel#heading { font-size: %heading_fs%px; font-weight: bold; color: %text_primary%; border-bottom: 2px solid %accent_amber%; }
        QLabel#caption { font-size: %caption_fs%px; color: %text_secondary%; }

        ads--CDockContainerWidget { background-color: %bg_base%; }
        ads--CDockWidget { background-color: %bg_surface%; }
        ads--CDockAreaWidget { background-color: %bg_base%; border: 1px solid %bg_raised%; }
        ads--CDockAreaTitleBar { background-color: %bg_raised%; }
        ads--CDockWidgetTab { background-color: %bg_surface%; border-top: 2px solid transparent; }
        ads--CDockWidgetTab[active="true"] { border-top: 2px solid %accent_amber%; background-color: %bg_raised%; }
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
        .replace("%caption_fs%", QString::number(t.font_size_caption))
        .replace("%padding%", QString::number(padding))
        .replace("%padding_double%", QString::number(padding * 2));
}

}

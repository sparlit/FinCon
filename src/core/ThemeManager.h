#pragma once
#include <QString>

namespace FinConCore {

struct FinConThemeTokens {
    QString bg_base = "#080808";
    QString bg_surface = "#1a1a1a";
    QString bg_raised = "#2a2a2a";
    QString text_primary = "#e8e8e8";
    QString text_secondary = "#a0a0a0";
    QString accent_amber = "#fbbf24";
    QString positive_green = "#10b981";
    QString negative_red = "#ef4444";
    int font_size_base = 14;
    int font_size_title = 20;
    int font_size_heading = 16;
    int font_size_caption = 12;
};

enum class FinConThemeDensity { Compact, Default, Comfortable };
enum class FinConThemeFlavor {
    Default,
    Trading,
    Analytics,
    Data,
    System,
    AI
};

class FinConThemeManager {
public:
    static QString generateStyleSheet(FinConThemeFlavor flavor = FinConThemeFlavor::Default, FinConThemeDensity density = FinConThemeDensity::Default);
    static FinConThemeTokens tokens(FinConThemeFlavor flavor = FinConThemeFlavor::Default, FinConThemeDensity density = FinConThemeDensity::Default);
};

}

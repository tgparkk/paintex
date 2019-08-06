#include "pch.h"
#include "ToolValues.h"

COLORREF ToolValues::FgColor = RGB(0, 0, 0);
COLORREF ToolValues::BgColor = RGB(255, 255, 255);
int ToolValues::LineWidth = 1;
FIGURETYPE ToolValues::FigureType = BORDERONLY;
int ToolValues::FontSize = 100;
int ToolValues::FontMode = TRANSPARENT;

ToolValues::ToolValues(void) {}
ToolValues::~ToolValues(void) {}
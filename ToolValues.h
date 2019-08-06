#pragma once
#include "DrawObject.h"
class ToolValues
{
public:
	ToolValues(void);
	~ToolValues(void);

	static COLORREF FgColor;
	static COLORREF BgColor;
	static int LineWidth;
	static FIGURETYPE FigureType;
	static int FontSize;
	static CString FontName;
	static int FontMode;
};


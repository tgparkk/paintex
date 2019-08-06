#pragma once
#include "DrawObject.h"
class CEllipseDraw :public CDrawObject
{
private:
	CPoint m_topLeft;
	CPoint m_bottomRight;

	FIGURETYPE m_type;
	int m_Thickness;
	COLORREF m_lineColor;
	COLORREF m_fillColor;

public:
	CEllipseDraw(void);
	virtual ~CEllipseDraw(void);
	void draw(CDC* pDc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void setRect(CPoint& topLeft, CPoint& bottomRight);
	void setCircle(CPoint& center, int radius);
	void setProps(FIGURETYPE type, int& lineWidth, COLORREF& lineColor, COLORREF& fillColor);
};


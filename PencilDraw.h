#pragma once
#include "DrawObject.h"
#include <afxtempl.h>
#include <atltypes.h>
#include <afxwin.h>

class CDC;
class CPencilDraw :public CDrawObject
{
private:
	CList<CPoint, CPoint> m_points;
	int m_Thickness;
	COLORREF m_color;

public:
	CPencilDraw();
	virtual ~CPencilDraw();
	void draw(CDC* pDc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void addPoint(CPoint& point);
	void setPencil(int nWidth, COLORREF rgbColor);
};


#include "pch.h"
#include "BeeLineDraw.h"

CBeeLineDraw::CBeeLineDraw() {}

CBeeLineDraw::~CBeeLineDraw() {}

void CBeeLineDraw::draw(CDC* pDc) {
	CPen pen(PS_SOLID, m_lineThickness, m_color);
	CPen* oldPen = pDc->SelectObject(&pen);

	pDc->MoveTo(m_start);
	pDc->LineTo(m_end);

	pDc->SelectObject(oldPen);
}

int CBeeLineDraw::drawType(void) {
	return BEELINE;
}
void CBeeLineDraw::setPoint(CPoint& start, CPoint& end)
{
	m_start = start;
	m_end = end;
}

void CBeeLineDraw::setBeeLine(int& lineThickness, COLORREF& color) {
	m_lineThickness = lineThickness;
	m_color = color;
}

void CBeeLineDraw::serialize(CArchive& ar) {
	ar << drawType();
	ar << m_start << m_end << m_lineThickness << m_color;
}

void CBeeLineDraw::deserialize(CArchive& ar) {
	ar >> m_start >> m_end >> m_lineThickness >> m_color;
}

// Window.h : header file
//

#pragma once
#include <vector>
#include "helper.h"
#include <iostream>

// Window dialog
class Window : public CDialogEx
{
// Construction
public:
	Window(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ICG_LAB_II_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	vector<MyPoint> points;
	vector<MySegment> segments;
	vector<MyPoint> CH;
	vector<pair<int, int>> diagonals;
	vector<MyPoint> intersectionPoints;
	bool second_click = false;
	bool polygonVisible = false;
	bool hullVisible = false;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CRect GetDrawableArea() const;
	bool IsPointDrawable(CPoint) const;
	void ClearScreen();
	void DrawDiagonal(CDC&, const pair<int, int>&);
	void handleIntersection(MySegment*, MySegment*, std::set<MySegment*, ActiveSegmentsTree>&, std::priority_queue<pair<MyPoint, pair<MySegment*, MySegment*>>, vector<pair<MyPoint, pair<MySegment*, MySegment*>>>, EventsX>&);
	
	CButton CButtonSimplePolygon;
	CButton CButtonSegmentsIntersect;
	CButton CButtonGiftWrapping;
	CButton CButtonGraham;
	CButton CButtonIncremental;
	CEdit CEditNumPoints;
	CButton CButtonGeneratePoints;
	CButton CButtonDrawTangents;
	CButton CButtonPointInCH;
	CButton CButtonAddSegment;
	CButton CButtonAddPoint;
	CButton CButtonAddPolygon;
	CButton CButtonClear;
	CButton CButtonGenerateHVSegments;
	CButton CButtonIntersectHVSegments;
	CButton CButtonTriangulate;
	CButton CButtonGenerateArbitrarySegments;
	CButton CButtonIntersectArbitrarySegments;

	afx_msg void OnBnClickedSimplePolygon();
	afx_msg void OnBnClickedSegmentsIntersect();
	afx_msg void OnBnClickedGiftWrapping();
	afx_msg void OnBnClickedGraham();
	afx_msg void OnBnClickedIncremental();
	afx_msg void OnBnClickedGenerateArbitrarySegments();
	afx_msg void OnBnClickedIntersectArbitrarySegments();
	afx_msg void OnBnClickedTriangulate();
	afx_msg void OnBnClickedGenerateHvSegments();
	afx_msg void OnBnClickedIntersectHvSegments();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedGeneratePoints();
};

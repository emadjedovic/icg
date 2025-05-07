
// Window.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ICG_lab_II.h"
#include "Window.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Window dialog



Window::Window(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ICG_LAB_II_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Window::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLEAR, CButtonClear);
	DDX_Control(pDX, IDC_SIMPLE_POLYGON, CButtonSimplePolygon);
	DDX_Control(pDX, IDC_SEGMENTS_INTERSECT, CButtonSegmentsIntersect);
	DDX_Control(pDX, IDC_GIFT_WRAPPING, CButtonGiftWrapping);
	DDX_Control(pDX, IDC_GRAHAM, CButtonGraham);
	DDX_Control(pDX, IDC_INCREMENTAL, CButtonIncremental);
	DDX_Control(pDX, IDC_GENERATE_POINTS, CButtonGeneratePoints);
	DDX_Control(pDX, IDC_NUM_POINTS, CEditNumPoints);
	DDX_Control(pDX, IDC_DRAW_TANGENTS, CButtonDrawTangents);
	DDX_Control(pDX, IDC_POINT_IN_CH, CButtonPointInCH);
	DDX_Control(pDX, IDC_ADD_SEGMENT, CButtonAddSegment);
	DDX_Control(pDX, IDC_ADD_POINT, CButtonAddPoint);
}

BEGIN_MESSAGE_MAP(Window, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CLEAR, &Window::OnBnClickedClear)
	ON_BN_CLICKED(IDC_SIMPLE_POLYGON, &Window::OnBnClickedSimplePolygon)
	ON_BN_CLICKED(IDC_SEGMENTS_INTERSECT, &Window::OnBnClickedSegmentsIntersect)
	ON_BN_CLICKED(IDC_GIFT_WRAPPING, &Window::OnBnClickedGiftWrapping)
	ON_BN_CLICKED(IDC_GRAHAM, &Window::OnBnClickedGraham)
	ON_BN_CLICKED(IDC_INCREMENTAL, &Window::OnBnClickedIncremental)
	ON_BN_CLICKED(IDC_GENERATE_POINTS, &Window::OnBnClickedGeneratePoints)
END_MESSAGE_MAP()


// Window message handlers

BOOL Window::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// Returns the drawable area as a CRect with proper margins
CRect Window::GetDrawableArea() const
{
	CRect rect;
	GetClientRect(&rect);

	int width = rect.Width();
	int height = rect.Height();

	int marginLeft = static_cast<int>(width * 0.05);
	int marginRight = static_cast<int>(width * 0.25);
	int marginTop = static_cast<int>(height * 0.10);
	int marginBottom = static_cast<int>(height * 0.20);

	int left = rect.left + marginLeft;
	int top = rect.top + marginTop;
	int right = rect.right - marginRight;
	int bottom = rect.bottom - marginBottom;

	return CRect(left, top, right, bottom);
}

bool Window::IsPointDrawable(CPoint pt) const
{
	return GetDrawableArea().PtInRect(pt);
}

void Window::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		for (const auto& pt : points)
		{
			pt.Draw(dc);
		}

		if (polygonVisible && points.size() >= 3)
			DrawPolygon(dc, points);

		CDialogEx::OnPaint();
	}
}

HCURSOR Window::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Window::AddPoint(int x, int y)
{
	CPoint pt(x, y);
	if (IsPointDrawable(pt))
	{
		points.emplace_back(x, y);
		Invalidate();
	}
}

void Window::OnLButtonDown(UINT nFlags, CPoint point)
{
	AddPoint(point.x, point.y);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void Window::ClearScreen()
{
	points.clear();
	polygonVisible = false;
	Invalidate();
}

void Window::OnBnClickedClear()
{
	ClearScreen();
}

void Window::OnBnClickedGeneratePoints()
{
	ClearScreen();
	CRect drawable = GetDrawableArea();
	int width = drawable.Width();
	int height = drawable.Height();

	CString str;
	CEditNumPoints.GetWindowText(str);
	int n = _ttoi(str);

	for (int i = 0; i < n; i++)
	{
		int x = drawable.left + rand() % width;
		int y = drawable.top + rand() % height;
		AddPoint(x, y);
	}
}


void Window::OnBnClickedSimplePolygon()
{
	if (points.size() < 3) {
		std::cout << "Less than three points.";
		return;
	}

	for (int i = 1; i < points.size(); i++) {
		if (points[i] < points[0]) {
			std::swap(points[i], points[0]);
		}
	}

	MyPoint leftmost(points[0]);
	sort(points.begin() + 1, points.end(), [leftmost](MyPoint A, MyPoint B) {
		return Orientation(leftmost, A, B) < 0;
		});

	polygonVisible = true; // optional: add a flag if needed
	Invalidate(); // triggers OnPaint()
}


void Window::OnBnClickedSegmentsIntersect()
{
	// TODO: Add your control notification handler code here
}

void Window::OnBnClickedGiftWrapping()
{
	// TODO: Add your control notification handler code here
}

void Window::OnBnClickedGraham()
{
	// TODO: Add your control notification handler code here
}

void Window::OnBnClickedIncremental()
{
	// TODO: Add your control notification handler code here
}



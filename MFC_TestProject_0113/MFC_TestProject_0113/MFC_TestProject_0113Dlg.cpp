// MFC_TestProject_0113Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_TestProject_0113.h"
#include "MFC_TestProject_0113Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCTestProject0113Dlg 대화 상자



CMFCTestProject0113Dlg::CMFCTestProject0113Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_TESTPROJECT_0113_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CMFCTestProject0113Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCTestProject0113Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CMFCTestProject0113Dlg::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_IMAGE, &CMFCTestProject0113Dlg::OnBnClickedButtonImage)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CMFCTestProject0113Dlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_RANDOM_POS, &CMFCTestProject0113Dlg::OnBnClickedButtonRandomPos)
END_MESSAGE_MAP()


// CMFCTestProject0113Dlg 메시지 처리기

BOOL CMFCTestProject0113Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	CEdit* nOutLine = (CEdit*)GetDlgItem(IDC_EDIT_OUTLINE);
	if (nOutLine != nullptr)
	{
		nOutLine->SetWindowText(_T("3"));
	}


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCTestProject0113Dlg::CreateImage(int nWidth, int nHeight, int nBpp)
{
	if (m_image.IsNull())
	{
		m_image.Create(nWidth, -nHeight, nBpp);
	}
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
	UpdateDisplay();
}

void CMFCTestProject0113Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCTestProject0113Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCTestProject0113Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCTestProject0113Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_idxNum >= 3) {
		m_idxNum = 0;
	}
	if (isCircle) {
		CreateImage(m_Width, m_Height, m_Bpp);
		isCircle = false;
	}
	int Errorrange = 40;
	CString strPos;
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	strPos.Format(_T("X : %d   Y : %d"), point.x, point.y - Errorrange);

	if (mPosVec.size() < 3) {
		mPosVec.emplace_back(std::make_unique<CStatic>());
		mClickPoints.emplace_back((Pos{ point.x, point.y - Errorrange }));
	}
	else
	{
		mPosVec[m_idxNum].reset();
		mPosVec[m_idxNum] = (std::make_unique<CStatic>());
		DrawCircle(fm, mClickPoints[m_idxNum].x, mClickPoints[m_idxNum].y - Errorrange, 40, 25, 255, 255, true);
		UpdateDisplay();
	}

	if (mPosVec[m_idxNum]->Create(strPos, WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(point.x, point.y, point.x + 100, point.y + 20), this))
	{
		CFont font;
		font.CreatePointFont(80, _T("Arial")); // 글꼴 크기 8포인트 설정

		mPosVec[m_idxNum]->SetFont(&font);
		mClickPoints[m_idxNum] = (Pos{point.x, point.y - Errorrange });

		// 좌표 텍스트 설정
		mPosVec[m_idxNum]->SetWindowText(strPos);
		DrawCircle(fm, point.x, point.y - Errorrange, 20, 10, 255, 0, true);
		UpdateDisplay();
	}

	m_idxNum++;

	// 부모 클래스의 기본 처리 호출
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCTestProject0113Dlg::OnBnClickedButtonDraw()
{
	isCircle = true;
	int centerX, centerY, radius;

	// // Edit Control의 값을 가져와 thickness 정수로 변환하는 코드
	CEdit* pEditControl = (CEdit*)GetDlgItem(IDC_EDIT_OUTLINE);
	if (pEditControl != nullptr) {
		CString strValue;
		pEditControl->GetWindowText(strValue); 

		int thickness = _ttoi(strValue);

		if (thickness > 0) {
			m_Thickness = thickness;
		}
		else {
			// 기본값 3 유지
			m_Thickness = 3; 
		}
	}
	
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	
	if (CalculateCircleFromPoints(mClickPoints, centerX, centerY, radius))
	{
		DrawCircle(fm, centerX, centerY, radius, m_Thickness, 0, 255, false);
		UpdateDisplay();
	}
}

bool CMFCTestProject0113Dlg::CalculateCircleFromPoints(std::vector <Pos> points, int& centerX, int& centerY, int& radius)
{
    size_t count = points.size();

	// 세 점의 좌표 가져오기
	double x1 = points[0].x, y1 = points[0].y;
	double x2 = points[1].x, y2 = points[1].y;
	double x3 = points[2].x, y3 = points[2].y;

	// 세 점이 일직선인지 확인 (행렬식 계산)
	double det = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
	if (fabs(det) < 1e-10) {
		return false; // 세 점이 일직선 상에 있음
	}

	// 중심 계산 (행렬 방식)
	double A = x1 * (y2 - y3) - y1 * (x2 - x3) + (x2 * y3 - x3 * y2);
	double B = (x1 * x1 + y1 * y1) * (y3 - y2) + (x2 * x2 + y2 * y2) * (y1 - y3) + (x3 * x3 + y3 * y3) * (y2 - y1);
	double C = (x1 * x1 + y1 * y1) * (x2 - x3) + (x2 * x2 + y2 * y2) * (x3 - x1) + (x3 * x3 + y3 * y3) * (x1 - x2);

	double cx = -B / (2 * A);
	double cy = -C / (2 * A);

	// 반지름 계산
	double r = sqrt(pow(cx - x1, 2) + pow(cy - y1, 2));

	centerX = static_cast<int>(cx);
	centerY = static_cast<int>(cy);
	radius = static_cast<int>(r);

	return true;
}

void CMFCTestProject0113Dlg::DrawCircle(unsigned char* fm, int x, int y, int nRadius, int nThickness, int nInColor, int nOutColor, bool bDrawOutline)
{
	int nCenterX = x;
	int nCenterY = y;
	int nPitch = abs(m_image.GetPitch()); // 음수일 수 있으므로 절대값 사용

	// 이미지 크기 가져오기
	int nImageWidth = m_image.GetWidth();
	int nImageHeight = m_image.GetHeight();

	// 원의 범위 내에서만 그리기
	for (int j = nCenterY - nRadius; j <= nCenterY + nRadius; j++) {
		if (j < 0 || j >= nImageHeight) // Y 범위 초과 방지
			continue;

		for (int i = nCenterX - nRadius; i <= nCenterX + nRadius; i++) {
			if (i < 0 || i >= nImageWidth) // X 범위 초과 방지
				continue;

			// 중심으로부터의 거리 계산
			double dDist = sqrt(pow(i - nCenterX, 2) + pow(j - nCenterY, 2));

			// 외곽선 영역
			if (dDist >= nRadius - nThickness && dDist <= nRadius) {
				fm[j * nPitch + i] = nInColor;
			}
			// 내부 영역
			else if (dDist < nRadius - nThickness && bDrawOutline) {
				fm[j * nPitch + i] = nOutColor;
			}
		}
	}
}


void CMFCTestProject0113Dlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 10, 50);

}

void CMFCTestProject0113Dlg::OnBnClickedButtonImage()
{
	CreateImage(m_Width, m_Height, m_Bpp);
}


void CMFCTestProject0113Dlg::OnBnClickedButtonReset()
{
	CreateImage(m_Width, m_Height, m_Bpp);
	// 여태 받은 vertex 초기화 
	mClickPoints.clear();
}


void CMFCTestProject0113Dlg::OnBnClickedButtonRandomPos()
{
	AfxBeginThread([](LPVOID pParam) -> UINT {
		auto* pDlg = reinterpret_cast<CMFCTestProject0113Dlg*>(pParam);

		for (int i = 0; i < 10; ++i) { // 총 10번 반복
			Sleep(500); // 초당 2회 실행

			int width = 910;
			int height = 420;

			for (auto& point : pDlg->mClickPoints) {
				point.x = rand() % (width - 40);
				point.y = rand() % (height - 40);
			}

			pDlg->UpdateDrawing();
		}

		return 0;
		}, this);
}

void CMFCTestProject0113Dlg::UpdateDrawing()
{
	CreateImage(m_Width, m_Height, m_Bpp);
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	for (const auto& point : mClickPoints) {
		DrawCircle(fm, point.x, point.y, 15, 8, 0, 0, true); // 점 그리기
		UpdateDisplay();
	}

	if (mClickPoints.size() == 3) {
		int centerX, centerY, radius;
		if (CalculateCircleFromPoints(mClickPoints, centerX, centerY, radius)) {
			DrawCircle(fm, centerX, centerY, radius, 3, 0, 255, false); // 정원 그리기
			UpdateDisplay();
		}
	}

	UpdateDisplay();
}

// MFC_TestProject_0113Dlg.h: 헤더 파일
//


#pragma once


#include <memory>
#include <vector>

typedef struct Pos {
	int x = 0, y = 0;
} Pos;


// CMFCTestProject0113Dlg 대화 상자
class CMFCTestProject0113Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCTestProject0113Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	bool CalculateCircleFromPoints(std::vector <Pos> points, int& centerX, int& centerY, int& radius);
	void UpdateDisplay();

public:
	std::vector <Pos> mClickPoints;
	// 디버깅용 배열
	std::vector<std::unique_ptr <CStatic>> mPosVec;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_TESTPROJECT_0113_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	bool isCircle = false;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	void CreateImage(int nWidth, int nHeight, int nBpp);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

private:
	CImage m_image;

	int m_Width = 910;
	int m_Height = 420;
	int m_Bpp = 8;

	int m_Thickness = 3;

	int m_idxNum = 0;

	void DrawCircle(unsigned char* fm, int x, int y, int nRadius, int nThickness, int nInColor, int nOutColor, bool bDrawOutline);
	void UpdateDrawing();
public:
	afx_msg void OnBnClickedButtonDraw();
	afx_msg void OnBnClickedButtonImage();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonRandomPos();
};

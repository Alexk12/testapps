//
// DecodeBase64Dlg.cpp
//
#include "stdafx.h"
#include <string>
#include <assert.h>
#include <Utils\Utils.h>
#include <base64.h>
#include "framework.h"
#include "DecodeBase64.h"
#include "DecodeBase64Dlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

std::string formatDataAsHex(const std::vector<unsigned char>& _data, bool _upperCaseHexChars = false);

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
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

CDecodeBase64Dlg::CDecodeBase64Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DECODEBASE64, pParent)
{
	m_hIcon = AfxGetApp()->LoadIconW(IDR_MAINFRAME);
	m_strEncodedData = L"CQD2/wEBCwCg/ORBoFLfQSCN2kGA7t5BIC/hQQ==";
	m_strDecodedData = L"";
}

void CDecodeBase64Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ENCODED_DATA, m_strEncodedData);
	DDX_Control(pDX, IDC_BUTTON_DECODE, m_btnDecode);
	DDX_Text(pDX, IDC_EDIT_DECODED_DATA, m_strDecodedData);
}

BEGIN_MESSAGE_MAP(CDecodeBase64Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DECODE, &CDecodeBase64Dlg::OnBnClickedButtonDecode)
END_MESSAGE_MAP()

BOOL CDecodeBase64Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr) {
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenuW(MF_SEPARATOR);
			pSysMenu->AppendMenuW(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	updateUI();
	return TRUE;
}

void CDecodeBase64Dlg::updateUI()
{
	UpdateData();
	m_btnDecode.EnableWindow(!m_strEncodedData.IsEmpty() ? TRUE : FALSE);
}

void CDecodeBase64Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CDecodeBase64Dlg::OnPaint()
{
	if (IsIconic()) {
		CPaintDC dc(this);
		SendMessageW(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags the minimized window.
HCURSOR CDecodeBase64Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

std::string formatDataAsHex(const std::vector<unsigned char>& _data, bool _upperCaseHexChars /*= false*/)
{
	std::string fmt = _upperCaseHexChars ? "%02X" : "%02x";
	std::string dataStr;
	for (const auto& it : _data) {
		const char& ch = it;
		std::string str;
		str_FormatA(str, fmt.c_str(), (BYTE)ch);
		dataStr += str;
		dataStr += " ";
	}
	str_TrimRightA(dataStr);
	return dataStr;
}

void CDecodeBase64Dlg::OnBnClickedButtonDecode()
{
	UpdateData();
	std::string encodedString = UnicodeToUTF8(LPCWSTR(m_strEncodedData));
	if (encodedString.empty()) {
		assert(false);
		return;
	}
	std::vector<unsigned char> decodedData;
	base64_decode(encodedString, decodedData);
	std::string dataStr = formatDataAsHex(decodedData, true);
	m_strDecodedData = UTF8ToUnicode(dataStr.c_str()).c_str();
	std::wstring str;
	str_Format(str, L"\r\n\r\nКоличество байт: %i\r\n", (int)decodedData.size());
	m_strDecodedData += str.c_str();
	UpdateData(FALSE);
	updateUI();
}


//
// DecodeBase64Dlg.h
//
#pragma once
#include <vector>

class CDecodeBase64Dlg : public CDialogEx
{
public:
	CDecodeBase64Dlg(CWnd* pParent = nullptr);
	enum { IDD = IDD_DECODEBASE64 };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	void updateUI();
protected:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonDecode();
	DECLARE_MESSAGE_MAP()
protected:
	HICON m_hIcon;
protected:
	CString m_strEncodedData;
	CString m_strDecodedData;
	CButton m_btnDecode;
};

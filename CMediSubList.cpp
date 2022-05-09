#include "pch.h"
#include "CMediSubList.h"

BOOL CMediSubListDAO::DeleteAllMediSubList()
{
	CString strSQL = _T("DELETE FROM �������������");

	try {
		m_db.BeginTrans();
		m_db.ExecuteSQL(strSQL.GetBuffer());
		m_db.CommitTrans();
	}
	catch (const CException* pEx) {
		m_db.Rollback();
		TCHAR szErr[100];
		pEx->GetErrorMessage(szErr, sizeof(szErr));
		AfxMessageBox(szErr);
		return FALSE;
	}

	return TRUE;
}

BOOL CMediSubListDAO::InsertMediSubList(CMediSubListPtr pMediSubList)
{
	CString strSQL;
	strSQL.Format(_T("INSERT INTO ������������� (��ȣ, ��������ڵ�) VALUES ('%s','%s')"),
		pMediSubList->strHospitalNo.GetBuffer(),
		pMediSubList->strTreatCode.GetBuffer());

	try {
		m_db.BeginTrans();
		m_db.ExecuteSQL(strSQL.GetBuffer());
		m_db.CommitTrans();
	}
	catch (const CException* pEx) {
		m_db.Rollback();
		TCHAR szErr[100];
		pEx->GetErrorMessage(szErr, sizeof(szErr));
		AfxMessageBox(szErr);
		return FALSE;
	}

	return TRUE;
}
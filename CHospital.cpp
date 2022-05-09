#include "pch.h"
#include "CHospital.h"

vector<CHospitalPtr> CHospitalDAO::GetListHospital()
{
	vector<CHospitalPtr> resultList;

	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly,
		/*_T("SELECT h.��ȣ, \
		TO_DATE(h.���㰡����, 'YYYY-MM-DD') ���㰡����, \
		hs.�������¸�, h.�󼼿��������ڵ�, h.�󼼿������¸�, \
		h.��������ȭ, h.�����������ȣ, h.��������ü�ּ�, \
		h.���θ���ü�ּ�, h.���θ�����ȣ, h.������, h.���±��и�, h.�Ƿ���������, \
		h.�Ƿ��μ�, h.�Կ��Ǽ�, h.�����, h.������񳻿�� \
		FROM ���� h, ������������ hs \
		WHERE h.��ȣ < 50"));*/
		/*_T("SELECT h.��ȣ, \
		TO_DATE(h.���㰡����, 'YYYY-MM-DD') ���㰡����, \
		h.�������¸�, h.�󼼿��������ڵ�, h.�󼼿������¸�, \
		h.��������ȭ, h.�����������ȣ, h.��������ü�ּ�, \
		h.���θ���ü�ּ�, h.���θ�����ȣ, h.������, h.���±��и�, h.�Ƿ���������, \
		h.�Ƿ��μ�, h.�Կ��Ǽ�, h.�����, h.������񳻿�� \
		FROM ���� h \
		WHERE h.��ȣ < 50"));*/
		_T("SELECT h.��ȣ, \
			TO_DATE(h.���㰡����, 'YYYY-MM-DD') AS ���㰡����,\
			hs.�������¸�, h.�󼼿��������ڵ�, h.�󼼿������¸�,\
			h.��������ȭ, h.�����������ȣ, h.��������ü�ּ�,\
			h.���θ���ü�ּ�, h.���θ�����ȣ, h.������, h.���±��и�, h.�Ƿ���������,\
			h.�Ƿ��μ�, h.�Կ��Ǽ�, h.�����, h.������񳻿��\
			FROM ���� h, ������������ hs\
			WHERE h.�������¸� = hs.�������°�\
			AND h.��ȣ < 50\
			GROUP BY h.��ȣ,\
			h.���㰡����, \
			hs.�������¸�, h.�󼼿��������ڵ�, h.�󼼿������¸�,\
			h.��������ȭ, h.�����������ȣ, h.��������ü�ּ�,\
			h.���θ���ü�ּ�, h.���θ�����ȣ, h.������, h.���±��и�, h.�Ƿ���������,\
			h.�Ƿ��μ�, h.�Կ��Ǽ�, h.�����, h.������񳻿��\
			ORDER BY h.��ȣ"));
		/*_T("SELECT h.��ȣ, TO_DATE(h.���㰡����, 'YYYY-MM-DD') AS ���㰡����, s.�������¸�, h.�󼼿��������ڵ�, h.�󼼿������¸�, \
			h.��������ȭ, h.�����������ȣ, h.��������ü�ּ�, h.���θ���ü�ּ�, h.���θ�����ȣ, \
			h.������, h.���±��и�, h.�Ƿ���������, \
			h.�Ƿ��μ�, h.�Կ��Ǽ�, h.�����, h.������񳻿��, \
			LISTAGG(d.��������, ',') WITHIN GROUP(ORDER BY d.��������), \
			LISTAGG(dl.��������ڵ�, ',') \
			FROM ���� h, ������������� dl, ����������� d, ������������ s \
			WHERE h.��ȣ = dl.��ȣ \
			AND d.��������ڵ� = dl.��������ڵ� \
			AND h.�������¸� = �������°� \
			GROUP BY h.��ȣ, h.���㰡����, s.�������¸�, h.�󼼿��������ڵ�, h.�󼼿������¸�, \
			h.��������ȭ, h.�����������ȣ, h.��������ü�ּ�, h.���θ���ü�ּ�, h.���θ�����ȣ, \
			h.������, h.���±��и�, h.�Ƿ���������, \
			h.�Ƿ��μ�, h.�Կ��Ǽ�, h.�����, h.������񳻿��"));*/

	while (!rs.IsEOF()) {
		CHospitalPtr pHospital = make_shared<CHospital>();
		if (pHospital == nullptr) return vector<CHospitalPtr>();

		rs.GetFieldValue(_T("��ȣ"), pHospital->strHospitalNo);
		rs.GetFieldValue(_T("���㰡����"), pHospital->strAuthDate);
		rs.GetFieldValue(_T("�������¸�"), pHospital->strStatusName);
		rs.GetFieldValue(_T("�󼼿��������ڵ�"), pHospital->strStatusCode);
		rs.GetFieldValue(_T("�󼼿������¸�"), pHospital->strDetaileStatusName);
		rs.GetFieldValue(_T("��������ȭ"), pHospital->strPhone);
		rs.GetFieldValue(_T("�����������ȣ"), pHospital->strPostCode);
		rs.GetFieldValue(_T("��������ü�ּ�"), pHospital->strAddress);
		rs.GetFieldValue(_T("���θ���ü�ּ�"), pHospital->strRoadAddress);
		rs.GetFieldValue(_T("���θ�����ȣ"), pHospital->strRoadPostCode);
		rs.GetFieldValue(_T("������"), pHospital->strHospitalName);
		rs.GetFieldValue(_T("���±��и�"), pHospital->strBusinessName);
		rs.GetFieldValue(_T("�Ƿ���������"), pHospital->strBusinessNickName);
		rs.GetFieldValue(_T("�Ƿ��μ�"), pHospital->strWorkerNum);
		rs.GetFieldValue(_T("�Կ��Ǽ�"), pHospital->strRoomNum);
		rs.GetFieldValue(_T("�����"), pHospital->strBedNum);
		rs.GetFieldValue(_T("������񳻿��"), pHospital->strTreatmentSubject);

		rs.MoveNext();

		resultList.push_back(pHospital);
	}
	rs.Close();

	return resultList;
}

CHospitalPtr CHospitalDAO::GetDetailHospital(CString strHospitalNo)
{
	// ����Ʈ �����͸� �̿��Ͽ� ��ü ���� 
	CHospitalPtr pHospital = make_shared<CHospital>();
	//if (pHospital == nullptr) return CHospitalPtr();

	// SQL ���� ���� 
	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, /*_T("SELECT * FROM ���� WHERE ��ȣ < 50 AND ��ȣ = ") + strHospitalNo);*/

		/*_T("SELECT h.��ȣ, \
		TO_DATE(h.���㰡����, 'YYYY-MM-DD') ���㰡����, \
		hs.�������¸�, h.�󼼿��������ڵ�, h.�󼼿������¸�, \
		h.��������ȭ, h.�����������ȣ, h.��������ü�ּ�, \
		h.���θ���ü�ּ�, h.���θ�����ȣ, h.������, h.���±��и�, h.�Ƿ���������, \
		h.�Ƿ��μ�, h.�Կ��Ǽ�, h.�����, h.������񳻿�� \
		FROM ���� h, ������������ hs") + strHospitalNo);*/

		/*_T("SELECT h.��ȣ, \
		TO_DATE(h.���㰡����, 'YYYY-MM-DD') ���㰡����, \
		h.�������¸�, h.�󼼿��������ڵ�, h.�󼼿������¸�, \
		h.��������ȭ, h.�����������ȣ, h.��������ü�ּ�, \
		h.���θ���ü�ּ�, h.���θ�����ȣ, h.������, h.���±��и�, h.�Ƿ���������, \
		h.�Ƿ��μ�, h.�Կ��Ǽ�, h.�����, h.������񳻿�� \
		FROM ���� h") + strHospitalNo);*/

	/*_T("SELECT h.��ȣ, \
			TO_DATE(h.���㰡����, 'YYYY-MM-DD') AS ���㰡����, \
			s.�������¸�, h.�󼼿��������ڵ�, h.�󼼿������¸�, \
			h.��������ȭ, h.�����������ȣ, h.��������ü�ּ�, h.���θ���ü�ּ�, h.���θ�����ȣ, \
			h.������, h.���±��и�, h.�Ƿ���������, \
			h.�Ƿ��μ�, h.�Կ��Ǽ�, h.�����, h.������񳻿��, \
			FROM ���� h, ������������� dl, ����������� d, ������������ s \
			WHERE h.��ȣ = dl.��ȣ \
			AND d.��������ڵ� = dl.��������ڵ� \
			AND h.�������¸� = �������°� \
			AND h.��ȣ = ") + strHospitalNo);*/

		_T("SELECT h.��ȣ, TO_DATE(h.���㰡����, 'YYYY-MM-DD') AS ���㰡����, s.�������¸�, h.�󼼿��������ڵ�, h.�󼼿������¸�, \
			h.��������ȭ, h.�����������ȣ, h.��������ü�ּ�, h.���θ���ü�ּ�, h.���θ�����ȣ, \
			h.������, h.���±��и�, h.�Ƿ���������, \
			h.�Ƿ��μ�, h.�Կ��Ǽ�, h.�����, h.������񳻿��, \
			LISTAGG(DISTINCT d.��������, ',') WITHIN GROUP(ORDER BY d.��������), \
			LISTAGG(DISTINCT dl.��������ڵ�, ',') \
			FROM ���� h, ������������� dl, ����������� d, ������������ s \
			WHERE h.��ȣ = dl.��ȣ \
			AND d.��������ڵ� = dl.��������ڵ� \
			AND h.�������¸� = �������°� \
			GROUP BY h.��ȣ, h.���㰡����, s.�������¸�, h.�󼼿��������ڵ�, h.�󼼿������¸�, \
			h.��������ȭ, h.�����������ȣ, h.��������ü�ּ�, h.���θ���ü�ּ�, h.���θ�����ȣ, \
			h.������, h.���±��и�, h.�Ƿ���������, \
			h.�Ƿ��μ�, h.�Կ��Ǽ�, h.�����, h.������񳻿�� \
			HAVING h.��ȣ = ") + strHospitalNo);


	// SQL ���� ���� ��� ��� 
	if (!rs.IsEOF()) {
		rs.GetFieldValue(_T("��ȣ"), pHospital->strHospitalNo);
		rs.GetFieldValue(_T("���㰡����"), pHospital->strAuthDate);
		rs.GetFieldValue(_T("�������¸�"), pHospital->strStatusName);
		rs.GetFieldValue(_T("�󼼿��������ڵ�"), pHospital->strStatusCode);
		rs.GetFieldValue(_T("�󼼿������¸�"), pHospital->strDetaileStatusName);
		rs.GetFieldValue(_T("��������ȭ"), pHospital->strPhone);
		rs.GetFieldValue(_T("�����������ȣ"), pHospital->strPostCode);
		rs.GetFieldValue(_T("��������ü�ּ�"), pHospital->strAddress);
		rs.GetFieldValue(_T("���θ���ü�ּ�"), pHospital->strRoadAddress);
		rs.GetFieldValue(_T("���θ�����ȣ"), pHospital->strRoadPostCode);
		rs.GetFieldValue(_T("������"), pHospital->strHospitalName);
		rs.GetFieldValue(_T("���±��и�"), pHospital->strBusinessName);
		rs.GetFieldValue(_T("�Ƿ���������"), pHospital->strBusinessNickName);
		rs.GetFieldValue(_T("�Ƿ��μ�"), pHospital->strWorkerNum);
		rs.GetFieldValue(_T("�Կ��Ǽ�"), pHospital->strRoomNum);
		rs.GetFieldValue(_T("�����"), pHospital->strBedNum);
		rs.GetFieldValue(_T("������񳻿��"), pHospital->strTreatmentSubject);
	}
	rs.Close();
	return pHospital;
}

BOOL CHospitalDAO::UpdateHospital(CHospitalPtr pHospital)
{
	// SQL ���� ����
	CString strSQL;
	strSQL.Format(_T("UPDATE ���� SET \
		���㰡����=TO_DATE('%s', 'YYYY-MM-DD'),\
		�������¸�='%s', �󼼿��������ڵ�='%s', �󼼿������¸�='%s', \
		��������ȭ='%s', \
		�����������ȣ='%s', ��������ü�ּ�='%s', ���θ���ü�ּ�='%s', ���θ�����ȣ='%s',\
		������='%s', \
		���±��и�='%s', �Ƿ���������='%s', \
		�Ƿ��μ�='%s', �Կ��Ǽ�='%s', �����='%s', \
		������񳻿��='%s' \
		WHERE ��ȣ='%s'"),
		pHospital->strAuthDate.GetBuffer(),
		pHospital->strStatusName.GetBuffer(),
		pHospital->strStatusCode.GetBuffer(),
		pHospital->strDetaileStatusName.GetBuffer(),
		pHospital->strPhone.GetBuffer(),
		pHospital->strPostCode.GetBuffer(),
		pHospital->strAddress.GetBuffer(),
		pHospital->strRoadAddress.GetBuffer(),
		pHospital->strRoadPostCode.GetBuffer(),
		pHospital->strHospitalName.GetBuffer(),
		pHospital->strBusinessName.GetBuffer(),
		pHospital->strBusinessNickName.GetBuffer(),
		pHospital->strWorkerNum.GetBuffer(),
		pHospital->strRoomNum.GetBuffer(),
		pHospital->strBedNum.GetBuffer(),
		pHospital->strTreatmentSubject.GetBuffer(),
		pHospital->strHospitalNo.GetBuffer());
	AfxMessageBox(pHospital->strHospitalNo);
	AfxMessageBox(strSQL);

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


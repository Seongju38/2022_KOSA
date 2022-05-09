#include "pch.h"
#include "CHospital.h"

vector<CHospitalPtr> CHospitalDAO::GetListHospital()
{
	vector<CHospitalPtr> resultList;

	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly,
		_T("SELECT h.��ȣ, \
		TO_DATE(h.���㰡����, 'YYYY-MM-DD') ���㰡����, \
		hs.�������¸�, h.�󼼿��������ڵ�, h.�󼼿������¸�, \
		h.��������ȭ, h.�����������ȣ, h.��������ü�ּ�, \
		h.���θ���ü�ּ�, h.���θ�����ȣ, h.������, h.���±��и�, h.�Ƿ���������, \
		h.�Ƿ��μ�, h.�Կ��Ǽ�, h.�����, h.������񳻿�� \
		FROM ���� h, ������������ hs \
		WHERE h.�������¸� = hs.�������°�"));

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

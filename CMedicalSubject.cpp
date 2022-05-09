
// �����������

#include "pch.h"
#include "CMedicalSubject.h"

vector<CMedicalSubjectPtr> CMedicalSubjectDAO::GetListMedicalSubject()
{
	vector<CMedicalSubjectPtr> resultList;

	// SQL ���� ���� 
	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("SELECT * FROM �����������"));

	// SQL ���� ���� ��� ��� 
	while (!rs.IsEOF()) {
		// ����Ʈ �����͸� �̿��Ͽ� ��ü ����
		CMedicalSubjectPtr pMedicalSubject = make_shared<CMedicalSubject>();
		if (pMedicalSubject == nullptr) return vector<CMedicalSubjectPtr>();

		// DB���� ��ȸ�� Hospital 1���� pHospital ��ü�� �����ϴ� �κ�  
		rs.GetFieldValue((short)0, pMedicalSubject->strTreatCode);
		rs.GetFieldValue(1, pMedicalSubject->strTreatName);

		rs.MoveNext();

		// �迭�� ����Ʈ ������ ��ü(pMedicalSubject)�� �߰��Ѵ� 
		resultList.push_back(pMedicalSubject);
	}
	rs.Close();


	return resultList;
}

map<CString, CString> CMedicalSubjectDAO::GetMapMedicalSubject()
{
	map<CString, CString> resultMap;

	// SQL ���� ���� 
	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("SELECT * FROM �����������"));

	// SQL ���� ���� ��� ��� 
	CString strTreatCode;
	CString strTreatName;

	while (!rs.IsEOF()) {
		// DB���� ��ȸ�� Hospital 1���� pHospital ��ü�� �����ϴ� �κ�  
		rs.GetFieldValue((short)0, strTreatCode);
		rs.GetFieldValue(1, strTreatName);

		rs.MoveNext();

		// �迭�� ����Ʈ ������ ��ü(pMedicalSubject)�� �߰��Ѵ� 
		resultMap[strTreatName] = strTreatCode;
	}
	rs.Close();

	return resultMap;
}
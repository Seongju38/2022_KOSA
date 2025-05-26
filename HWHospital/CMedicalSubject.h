
// �����������

#pragma once
class CMedicalSubject
{
public:
	CString strTreatCode;
	CString strTreatName;
};
using CMedicalSubjectPtr = shared_ptr<CMedicalSubject>;

class CMedicalSubjectDAO
{
private:
	CDatabase& m_db;
public:
	CMedicalSubjectDAO(CDatabase& db) : m_db(db) {
	}

	vector<CMedicalSubjectPtr> GetListMedicalSubject();
	map<CString, CString> GetMapMedicalSubject();

};



/*
// ������ȣ�� ���� �������� �Ʒ��� �ϳ��� ���

CMedicalSubjectDAO medicalSubjectDAO(m_db);
map<CString, CString> mapMedicalSubject = medicalSubjectDAO.GetMapMedicalSubject();


// ������������� ��ü ���� 
CMediSubListDAO mediSubListDAO(m_db);
mediSubListDAO.DeleteAllMediSubList();
CMediSubListPtr pMediSubList = make_shared<CMediSubList>();

int nPos = 0;
for (const auto& pHospital : HList) {
	// ������������� ���ڿ� ������ ���
	LPTSTR lpszMediSubject = pHospital->strTreatmentSubject.GetBuffer();
	LPTSTR lpszToken = NULL;
	LPTSTR lpszNextToken = NULL;

	lpszToken = _tcstok_s(lpszMediSubject, _T(",�� "), &lpszNextToken);
	while (lpszToken) {
		m_listView.InsertItem(nPos, pHospital->strHospitalNo.GetBuffer(), 0);
		// , . ���� �и��� ���ڿ� ��� 
		m_listView.SetItemText(nPos, 16, lpszToken);

		// ����������� ���� �ڵ� ã��
		// ã�� �ڵ�� ���� ��ȣ�� �̿��Ͽ� DB(������������� ���̺�)�� �߰� 
		pMediSubList->strHospitalNo = pHospital->strHospitalNo;
		pMediSubList->strTreatCode = mapMedicalSubject[lpszToken];
		if (!pMediSubList->strTreatCode.IsEmpty()) {
			mediSubListDAO.InsertMediSubList(pMediSubList);
		}

		nPos++;
		lpszToken = _tcstok_s(NULL, _T(",�� "), &lpszNextToken);
	}
}
*/


// 병원진료과목

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
// 병원번호에 따른 진료과목명 아래로 하나씩 출력

CMedicalSubjectDAO medicalSubjectDAO(m_db);
map<CString, CString> mapMedicalSubject = medicalSubjectDAO.GetMapMedicalSubject();


// 병원진료과목목록 전체 삭제 
CMediSubListDAO mediSubListDAO(m_db);
mediSubListDAO.DeleteAllMediSubList();
CMediSubListPtr pMediSubList = make_shared<CMediSubList>();

int nPos = 0;
for (const auto& pHospital : HList) {
	// 병원진료과목목록 문자열 포인터 얻기
	LPTSTR lpszMediSubject = pHospital->strTreatmentSubject.GetBuffer();
	LPTSTR lpszToken = NULL;
	LPTSTR lpszNextToken = NULL;

	lpszToken = _tcstok_s(lpszMediSubject, _T(",· "), &lpszNextToken);
	while (lpszToken) {
		m_listView.InsertItem(nPos, pHospital->strHospitalNo.GetBuffer(), 0);
		// , . 으로 분리한 문자열 출력 
		m_listView.SetItemText(nPos, 16, lpszToken);

		// 병원진료과목에 대한 코드 찾기
		// 찾은 코드와 병원 번호를 이용하여 DB(병원진료과목목록 테이블)에 추가 
		pMediSubList->strHospitalNo = pHospital->strHospitalNo;
		pMediSubList->strTreatCode = mapMedicalSubject[lpszToken];
		if (!pMediSubList->strTreatCode.IsEmpty()) {
			mediSubListDAO.InsertMediSubList(pMediSubList);
		}

		nPos++;
		lpszToken = _tcstok_s(NULL, _T(",· "), &lpszNextToken);
	}
}
*/

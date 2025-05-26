
// 병원진료과목

#include "pch.h"
#include "CMedicalSubject.h"

vector<CMedicalSubjectPtr> CMedicalSubjectDAO::GetListMedicalSubject()
{
	vector<CMedicalSubjectPtr> resultList;

	// SQL 구문 실행 
	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("SELECT * FROM 병원진료과목"));

	// SQL 구문 실행 결과 얻기 
	while (!rs.IsEOF()) {
		// 스마트 포인터를 이용하여 객체 생성
		CMedicalSubjectPtr pMedicalSubject = make_shared<CMedicalSubject>();
		if (pMedicalSubject == nullptr) return vector<CMedicalSubjectPtr>();

		// DB에서 조회된 Hospital 1건을 pHospital 객체로 설정하는 부분  
		rs.GetFieldValue((short)0, pMedicalSubject->strTreatCode);
		rs.GetFieldValue(1, pMedicalSubject->strTreatName);

		rs.MoveNext();

		// 배열에 스마트 포인터 객체(pMedicalSubject)를 추가한다 
		resultList.push_back(pMedicalSubject);
	}
	rs.Close();


	return resultList;
}

map<CString, CString> CMedicalSubjectDAO::GetMapMedicalSubject()
{
	map<CString, CString> resultMap;

	// SQL 구문 실행 
	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("SELECT * FROM 병원진료과목"));

	// SQL 구문 실행 결과 얻기 
	CString strTreatCode;
	CString strTreatName;

	while (!rs.IsEOF()) {
		// DB에서 조회된 Hospital 1건을 pHospital 객체로 설정하는 부분  
		rs.GetFieldValue((short)0, strTreatCode);
		rs.GetFieldValue(1, strTreatName);

		rs.MoveNext();

		// 배열에 스마트 포인터 객체(pMedicalSubject)를 추가한다 
		resultMap[strTreatName] = strTreatCode;
	}
	rs.Close();

	return resultMap;
}
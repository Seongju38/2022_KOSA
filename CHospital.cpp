#include "pch.h"
#include "CHospital.h"

vector<CHospitalPtr> CHospitalDAO::GetListHospital()
{
	vector<CHospitalPtr> resultList;

	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly,
		/*_T("SELECT h.번호, \
		TO_DATE(h.인허가일자, 'YYYY-MM-DD') 인허가일자, \
		hs.영업상태명, h.상세영업상태코드, h.상세영업상태명, \
		h.소재지전화, h.소재지우편번호, h.소재지전체주소, \
		h.도로명전체주소, h.도로명우편번호, h.사업장명, h.업태구분명, h.의료기관종별명, \
		h.의료인수, h.입원실수, h.병상수, h.진료과목내용명 \
		FROM 병원 h, 병원영업상태 hs \
		WHERE h.번호 < 50"));*/
		/*_T("SELECT h.번호, \
		TO_DATE(h.인허가일자, 'YYYY-MM-DD') 인허가일자, \
		h.영업상태명, h.상세영업상태코드, h.상세영업상태명, \
		h.소재지전화, h.소재지우편번호, h.소재지전체주소, \
		h.도로명전체주소, h.도로명우편번호, h.사업장명, h.업태구분명, h.의료기관종별명, \
		h.의료인수, h.입원실수, h.병상수, h.진료과목내용명 \
		FROM 병원 h \
		WHERE h.번호 < 50"));*/
		_T("SELECT h.번호, \
			TO_DATE(h.인허가일자, 'YYYY-MM-DD') AS 인허가일자,\
			hs.영업상태명, h.상세영업상태코드, h.상세영업상태명,\
			h.소재지전화, h.소재지우편번호, h.소재지전체주소,\
			h.도로명전체주소, h.도로명우편번호, h.사업장명, h.업태구분명, h.의료기관종별명,\
			h.의료인수, h.입원실수, h.병상수, h.진료과목내용명\
			FROM 병원 h, 병원영업상태 hs\
			WHERE h.영업상태명 = hs.영업상태값\
			AND h.번호 < 50\
			GROUP BY h.번호,\
			h.인허가일자, \
			hs.영업상태명, h.상세영업상태코드, h.상세영업상태명,\
			h.소재지전화, h.소재지우편번호, h.소재지전체주소,\
			h.도로명전체주소, h.도로명우편번호, h.사업장명, h.업태구분명, h.의료기관종별명,\
			h.의료인수, h.입원실수, h.병상수, h.진료과목내용명\
			ORDER BY h.번호"));
		/*_T("SELECT h.번호, TO_DATE(h.인허가일자, 'YYYY-MM-DD') AS 인허가일자, s.영업상태명, h.상세영업상태코드, h.상세영업상태명, \
			h.소재지전화, h.소재지우편번호, h.소재지전체주소, h.도로명전체주소, h.도로명우편번호, \
			h.사업장명, h.업태구분명, h.의료기관종별명, \
			h.의료인수, h.입원실수, h.병상수, h.진료과목내용명, \
			LISTAGG(d.진료과목명, ',') WITHIN GROUP(ORDER BY d.진료과목명), \
			LISTAGG(dl.진료과목코드, ',') \
			FROM 병원 h, 병원진료과목목록 dl, 병원진료과목 d, 병원영업상태 s \
			WHERE h.번호 = dl.번호 \
			AND d.진료과목코드 = dl.진료과목코드 \
			AND h.영업상태명 = 영업상태값 \
			GROUP BY h.번호, h.인허가일자, s.영업상태명, h.상세영업상태코드, h.상세영업상태명, \
			h.소재지전화, h.소재지우편번호, h.소재지전체주소, h.도로명전체주소, h.도로명우편번호, \
			h.사업장명, h.업태구분명, h.의료기관종별명, \
			h.의료인수, h.입원실수, h.병상수, h.진료과목내용명"));*/

	while (!rs.IsEOF()) {
		CHospitalPtr pHospital = make_shared<CHospital>();
		if (pHospital == nullptr) return vector<CHospitalPtr>();

		rs.GetFieldValue(_T("번호"), pHospital->strHospitalNo);
		rs.GetFieldValue(_T("인허가일자"), pHospital->strAuthDate);
		rs.GetFieldValue(_T("영업상태명"), pHospital->strStatusName);
		rs.GetFieldValue(_T("상세영업상태코드"), pHospital->strStatusCode);
		rs.GetFieldValue(_T("상세영업상태명"), pHospital->strDetaileStatusName);
		rs.GetFieldValue(_T("소재지전화"), pHospital->strPhone);
		rs.GetFieldValue(_T("소재지우편번호"), pHospital->strPostCode);
		rs.GetFieldValue(_T("소재지전체주소"), pHospital->strAddress);
		rs.GetFieldValue(_T("도로명전체주소"), pHospital->strRoadAddress);
		rs.GetFieldValue(_T("도로명우편번호"), pHospital->strRoadPostCode);
		rs.GetFieldValue(_T("사업장명"), pHospital->strHospitalName);
		rs.GetFieldValue(_T("업태구분명"), pHospital->strBusinessName);
		rs.GetFieldValue(_T("의료기관종별명"), pHospital->strBusinessNickName);
		rs.GetFieldValue(_T("의료인수"), pHospital->strWorkerNum);
		rs.GetFieldValue(_T("입원실수"), pHospital->strRoomNum);
		rs.GetFieldValue(_T("병상수"), pHospital->strBedNum);
		rs.GetFieldValue(_T("진료과목내용명"), pHospital->strTreatmentSubject);

		rs.MoveNext();

		resultList.push_back(pHospital);
	}
	rs.Close();

	return resultList;
}

CHospitalPtr CHospitalDAO::GetDetailHospital(CString strHospitalNo)
{
	// 스마트 포인터를 이용하여 객체 생성 
	CHospitalPtr pHospital = make_shared<CHospital>();
	//if (pHospital == nullptr) return CHospitalPtr();

	// SQL 구문 실행 
	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, /*_T("SELECT * FROM 병원 WHERE 번호 < 50 AND 번호 = ") + strHospitalNo);*/

		/*_T("SELECT h.번호, \
		TO_DATE(h.인허가일자, 'YYYY-MM-DD') 인허가일자, \
		hs.영업상태명, h.상세영업상태코드, h.상세영업상태명, \
		h.소재지전화, h.소재지우편번호, h.소재지전체주소, \
		h.도로명전체주소, h.도로명우편번호, h.사업장명, h.업태구분명, h.의료기관종별명, \
		h.의료인수, h.입원실수, h.병상수, h.진료과목내용명 \
		FROM 병원 h, 병원영업상태 hs") + strHospitalNo);*/

		/*_T("SELECT h.번호, \
		TO_DATE(h.인허가일자, 'YYYY-MM-DD') 인허가일자, \
		h.영업상태명, h.상세영업상태코드, h.상세영업상태명, \
		h.소재지전화, h.소재지우편번호, h.소재지전체주소, \
		h.도로명전체주소, h.도로명우편번호, h.사업장명, h.업태구분명, h.의료기관종별명, \
		h.의료인수, h.입원실수, h.병상수, h.진료과목내용명 \
		FROM 병원 h") + strHospitalNo);*/

	/*_T("SELECT h.번호, \
			TO_DATE(h.인허가일자, 'YYYY-MM-DD') AS 인허가일자, \
			s.영업상태명, h.상세영업상태코드, h.상세영업상태명, \
			h.소재지전화, h.소재지우편번호, h.소재지전체주소, h.도로명전체주소, h.도로명우편번호, \
			h.사업장명, h.업태구분명, h.의료기관종별명, \
			h.의료인수, h.입원실수, h.병상수, h.진료과목내용명, \
			FROM 병원 h, 병원진료과목목록 dl, 병원진료과목 d, 병원영업상태 s \
			WHERE h.번호 = dl.번호 \
			AND d.진료과목코드 = dl.진료과목코드 \
			AND h.영업상태명 = 영업상태값 \
			AND h.번호 = ") + strHospitalNo);*/

		_T("SELECT h.번호, TO_DATE(h.인허가일자, 'YYYY-MM-DD') AS 인허가일자, s.영업상태명, h.상세영업상태코드, h.상세영업상태명, \
			h.소재지전화, h.소재지우편번호, h.소재지전체주소, h.도로명전체주소, h.도로명우편번호, \
			h.사업장명, h.업태구분명, h.의료기관종별명, \
			h.의료인수, h.입원실수, h.병상수, h.진료과목내용명, \
			LISTAGG(DISTINCT d.진료과목명, ',') WITHIN GROUP(ORDER BY d.진료과목명), \
			LISTAGG(DISTINCT dl.진료과목코드, ',') \
			FROM 병원 h, 병원진료과목목록 dl, 병원진료과목 d, 병원영업상태 s \
			WHERE h.번호 = dl.번호 \
			AND d.진료과목코드 = dl.진료과목코드 \
			AND h.영업상태명 = 영업상태값 \
			GROUP BY h.번호, h.인허가일자, s.영업상태명, h.상세영업상태코드, h.상세영업상태명, \
			h.소재지전화, h.소재지우편번호, h.소재지전체주소, h.도로명전체주소, h.도로명우편번호, \
			h.사업장명, h.업태구분명, h.의료기관종별명, \
			h.의료인수, h.입원실수, h.병상수, h.진료과목내용명 \
			HAVING h.번호 = ") + strHospitalNo);


	// SQL 구문 실행 결과 얻기 
	if (!rs.IsEOF()) {
		rs.GetFieldValue(_T("번호"), pHospital->strHospitalNo);
		rs.GetFieldValue(_T("인허가일자"), pHospital->strAuthDate);
		rs.GetFieldValue(_T("영업상태명"), pHospital->strStatusName);
		rs.GetFieldValue(_T("상세영업상태코드"), pHospital->strStatusCode);
		rs.GetFieldValue(_T("상세영업상태명"), pHospital->strDetaileStatusName);
		rs.GetFieldValue(_T("소재지전화"), pHospital->strPhone);
		rs.GetFieldValue(_T("소재지우편번호"), pHospital->strPostCode);
		rs.GetFieldValue(_T("소재지전체주소"), pHospital->strAddress);
		rs.GetFieldValue(_T("도로명전체주소"), pHospital->strRoadAddress);
		rs.GetFieldValue(_T("도로명우편번호"), pHospital->strRoadPostCode);
		rs.GetFieldValue(_T("사업장명"), pHospital->strHospitalName);
		rs.GetFieldValue(_T("업태구분명"), pHospital->strBusinessName);
		rs.GetFieldValue(_T("의료기관종별명"), pHospital->strBusinessNickName);
		rs.GetFieldValue(_T("의료인수"), pHospital->strWorkerNum);
		rs.GetFieldValue(_T("입원실수"), pHospital->strRoomNum);
		rs.GetFieldValue(_T("병상수"), pHospital->strBedNum);
		rs.GetFieldValue(_T("진료과목내용명"), pHospital->strTreatmentSubject);
	}
	rs.Close();
	return pHospital;
}

BOOL CHospitalDAO::UpdateHospital(CHospitalPtr pHospital)
{
	// SQL 수정 구문
	CString strSQL;
	strSQL.Format(_T("UPDATE 병원 SET \
		인허가일자=TO_DATE('%s', 'YYYY-MM-DD'),\
		영업상태명='%s', 상세영업상태코드='%s', 상세영업상태명='%s', \
		소재지전화='%s', \
		소재지우편번호='%s', 소재지전체주소='%s', 도로명전체주소='%s', 도로명우편번호='%s',\
		사업장명='%s', \
		업태구분명='%s', 의료기관종별명='%s', \
		의료인수='%s', 입원실수='%s', 병상수='%s', \
		진료과목내용명='%s' \
		WHERE 번호='%s'"),
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


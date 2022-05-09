#include "pch.h"
#include "CHospital.h"

vector<CHospitalPtr> CHospitalDAO::GetListHospital()
{
	vector<CHospitalPtr> resultList;

	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly,
		_T("SELECT h.번호, \
		TO_DATE(h.인허가일자, 'YYYY-MM-DD') 인허가일자, \
		hs.영업상태명, h.상세영업상태코드, h.상세영업상태명, \
		h.소재지전화, h.소재지우편번호, h.소재지전체주소, \
		h.도로명전체주소, h.도로명우편번호, h.사업장명, h.업태구분명, h.의료기관종별명, \
		h.의료인수, h.입원실수, h.병상수, h.진료과목내용명 \
		FROM 병원 h, 병원영업상태 hs \
		WHERE h.영업상태명 = hs.영업상태값"));

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

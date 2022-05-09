
// 병원영업상태

#include "pch.h"
#include "CHospitalStatus.h"

vector<CHospitalStatusPtr> CHospitalStatusDAO::GetListHospitalStatus()
{
	vector<CHospitalStatusPtr> resultList;

	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("SELECT * FROM 병원영업상태"));

	while (!rs.IsEOF()) {
		CHospitalStatusPtr pHospitalStatus = make_shared<CHospitalStatus>();
		if (pHospitalStatus == nullptr) return vector<CHospitalStatusPtr>();

		rs.GetFieldValue((short)0, pHospitalStatus->strStatusValue);
		rs.GetFieldValue(1, pHospitalStatus->strStatusName);

		rs.MoveNext();

		resultList.push_back(pHospitalStatus);
	}
	rs.Close();

	return resultList;
}

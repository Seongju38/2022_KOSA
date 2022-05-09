#pragma once
class CMediSubList
{
public:
	CString strHospitalNo;
	CString strTreatCode;
};
using CMediSubListPtr = shared_ptr<CMediSubList>;

class CMediSubListDAO
{
private:
	CDatabase& m_db;
public:
	CMediSubListDAO(CDatabase& db) : m_db(db) {
	}

	// 전체 자료 삭제 
	BOOL DeleteAllMediSubList();
	BOOL InsertMediSubList(CMediSubListPtr pMediSubList);

};


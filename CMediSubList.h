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

	// ��ü �ڷ� ���� 
	BOOL DeleteAllMediSubList();
	BOOL InsertMediSubList(CMediSubListPtr pMediSubList);

};


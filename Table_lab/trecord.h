#pragma once
#include <iostream>
typedef std::string TKey;
class TTabRecord 
{

protected:
	TKey Key;
	int* pValue;
public:
	TTabRecord(TKey k = "", int* pVal = NULL)
	{
		Key = k; pValue = pVal;
	}

	void SetKey(TKey k) {Key = k;}
	TKey GetKey(void) { return Key; }
	void SetValuePtr(int* p) { pValue = p; }
	int* GetValuePtr(void) { return pValue; }

	TTabRecord& operator=(TTabRecord tr)
	{
		Key = tr.Key; pValue = tr.pValue;
		return *this;
	}
	virtual int operator==(const TTabRecord &tr) { return Key == tr.Key; }
	virtual int operator< (const TTabRecord &tr) { return Key > tr.Key; }
	virtual int operator> (const TTabRecord &tr) { return Key < tr.Key; }
protected:
	void PrintRec(std::ostream& os) { os << Key << " " << *pValue; }

friend class TArrayTable;
friend class TScanTable;
friend class TSortTable;
friend class TTreeNode;
friend class TTreeTable;
friend class TArrayhash;
friend class THashTable;
};
typedef TTabRecord* PTTabRecord;
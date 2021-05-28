#pragma once
#include "arraytab.h"
class TScanTable : public TArrayTable
{
protected:
	int SortID = 0;
public:
	TScanTable(int Size = TabMaxSize) : TArrayTable(Size) {};
	virtual int* FindRecord(TKey k);
	virtual void InsRecord(TKey k, int* pVal);
	virtual void DelRecord(TKey k);
	void SetSortID(int ID) { SortID = ID; }
};
#include "arrhash.h"

TArrayHash :: TArrayHash (int _choose, int Size , int Step) : THashTable() 
{
	choose = _choose;
	pRecs = new PTTabRecord[Size]; 
	TabSize = Size; 
	HashStep = Step;
	for (int i = 0; i < TabSize; i++) pRecs[i] = NULL;
	pMark = new TTabRecord(std::string(""), NULL);
}

TArrayHash :: ~TArrayHash () 
{
	for (int i = 0; i < TabSize; i++)
		if ((pRecs[i] != NULL) && (pRecs[i] != pMark)) delete pRecs[i];
	delete[] pRecs;
	delete pMark;
}

int* TArrayHash::FindRecord(TKey k)
{
	int* pValue = NULL;
	FreePos = -1;
	CurrPos = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; i++)
	{
		Efficiency++;
		if (pRecs[CurrPos] == NULL) break;
		else if (pRecs[CurrPos] == pMark)
		{
			if (FreePos == -1) FreePos = CurrPos;
		}
		else if (pRecs[CurrPos]->GetKey() == k)
		{
			pValue = pRecs[CurrPos]->GetValuePtr();
			break;
		}
		CurrPos = GetNextPos(CurrPos);
	}
	if (pValue == NULL) 
		return NULL;
	return pValue;
}

void TArrayHash::InsRecord(TKey k, int* pVal)
{
	if (!IsFull())
	{
		int* temp = FindRecord(k);
		if (temp == NULL)
		{
			if (FreePos != -1) CurrPos = FreePos;
			pRecs[CurrPos] = new TTabRecord(k, pVal);
			DataCount++;
		}
	}
}

void TArrayHash::DelRecord(TKey k)
{
	int* temp = FindRecord(k);
	if (temp != NULL)
	{
		delete pRecs[CurrPos];
		pRecs[CurrPos] = pMark;
		DataCount--;
	}
}

int TArrayHash::IsTabEnded(void) const
{
	return CurrPos >= TabSize;
}

int TArrayHash::GoNext(void)
{
	if (!IsTabEnded())
	{
		while (++CurrPos < TabSize)
			if ((pRecs[CurrPos] != NULL) && (pRecs[CurrPos] != pMark)) break;
	}
	return IsTabEnded();
}

TKey TArrayHash::GetKey(void) const
{
	return ((CurrPos < 0) || (CurrPos >= TabSize)) ? std::string("") : pRecs[CurrPos] -> GetKey();
}

int* TArrayHash::GetValuePtr(void) const
{
	return  ((CurrPos < 0) || (CurrPos >= TabSize)) ? NULL : pRecs[CurrPos]->GetValuePtr();
}

int TArrayHash::Reset(void) 
{ 
	CurrPos = 0;
	while (CurrPos < TabSize)
		if ((pRecs[CurrPos] != NULL) && (pRecs[CurrPos] != pMark)) break;
		else CurrPos++;
	return IsTabEnded();
}
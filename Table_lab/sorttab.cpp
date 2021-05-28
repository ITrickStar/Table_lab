#include "sorttab.h"
TSortTable::TSortTable(const TScanTable & tab)
{
	*this = tab;
}

TSortTable& TSortTable::operator= (const TScanTable& tab)
{
	if (pRecs != NULL)
	{
		for (int i = 0; i < DataCount; i++)
			delete pRecs[i];
		delete[] pRecs;
		pRecs = NULL;
	}
	TabSize = tab.GetTabSize();
	DataCount = tab.GetDataCount();
	pRecs = new PTTabRecord[TabSize];
	for (int i = 0; i < DataCount; i++)
		pRecs[i] = tab.GetpRecs(i);
	SortData();
	CurrPos = 0;
	return *this;
}

int* TSortTable::FindRecord(TKey k)
{
	int midd = 0, left = 0, right = DataCount - 1;
	while (left<=right)
	{
		midd = (left + right) / 2;
		if (k < pRecs[midd]->GetKey())       // если искомое меньше значения в ячейке
			right = midd - 1;      // смещаем правую границу поиска
		else if (k > pRecs[midd]->GetKey())  // если искомое больше значения в ячейке
			left = midd + 1;    // смещаем левую границу поиска
		else                       // иначе (значения равны)
		{
			CurrPos = midd;
			return pRecs[midd]->GetValuePtr();
		}
	}
	CurrPos = left;
	DopTab.SetSortID(1);
	if (DopTab.FindRecord(k))	
		return DopTab.GetValuePtr();
	return NULL;
}

void TSortTable::InsRecord(TKey k, int* pVal)
{
	if (!DopTab.IsFull())
	{
		DopTab.SetSortID(1);
		int* temp = DopTab.FindRecord(k);
		DopTab.SetSortID(1);
		DopTab.InsRecord(k, pVal);
	}
	CurrPos = DataCount;
}

void TSortTable::DelRecord(TKey k)
{
	if (IsEmpty())
	{
		int midd = 0, left = 0, right = DataCount - 1, cheak = 1;
		while (cheak)
		{
			midd = (left + right) / 2;
			if (k < pRecs[midd]->GetKey())       // если искомое меньше значения в ячейке
				right = midd - 1;      // смещаем правую границу поиска
			else if (k > pRecs[midd]->GetKey())  // если искомое больше значения в ячейке
				left = midd + 1;    // смещаем левую границу поиска
			else  // иначе (значения равны)
			{
				if (midd < DataCount)
				{
					DataCount--;
					for (int j = midd; j < DataCount; j++)
					{
						pRecs[j]->pValue = pRecs[j + 1]->pValue;
						pRecs[j]->Key = pRecs[j + 1]->Key;
					}
					pRecs[DataCount]->pValue = NULL;
					pRecs[DataCount]->Key = "";
					pRecs[DataCount] = NULL;
				}
				cheak = 0;
			}
			if (left > right) // если границы сомкнулись 
			{
				DopTab.SetSortID(1);
				DopTab.DelRecord(k);
				cheak = 0;
			}
		}
		CurrPos = midd - 1;
	}
	else
	{
		CurrPos = 0;
		DopTab.SetSortID(1);
		DopTab.DelRecord(k);
	}
}

void TSortTable::Merge()
{
	int i = 0, i1 = 0, i2 = 0;
	int n1 = DataCount; int n2 = DopTab.GetDataCount();
	PTTabRecord* pDat1 = pRecs, * pDat2 = DopTab.GetAllpRecs();
	pBuff = new PTTabRecord[n1+n2];
	while ((i1 < n1) && (i2 < n2))
	{
		if (pDat1[i1]->Key < pDat2[i2]->Key)
			pBuff[i++] = pDat1[i1++];
		else
			pBuff[i++] = pDat2[i2++];
	}
	while (i1 < n1)
		pBuff[i++] = pDat1[i1++];
	while (i2 < n2)
		pBuff[i++] = pDat2[i2++];
	DataCount += DopTab.GetDataCount();
	pRecs = pBuff;
	DopTab.FreepRecs();
}

void TSortTable::MergeData(PTTabRecord*& pData, PTTabRecord*& pBuff, int n1,int n2)
{
	int i = 0, i1 = 0, i2 = 0;
	PTTabRecord* pDat1 = pData, * pDat2 = pData + n1;
	while ((i1 < n1) && (i2 < n2))
	{
		if (pDat1[i1]->Key < pDat2[i2]->Key)
			pBuff[i++] = pDat1[i1++];
		else pBuff[i++] = pDat2[i2++];
	}
	while (i1 < n1)
		pBuff[i++] = pDat1[i1++];
	while (i2<n2)
		pBuff[i++] = pDat2[i2++];
	pData = pBuff;
	pBuff = pDat1;
	Efficiency += n1 + n2;
}
void TSortTable::QuickSort(PTTabRecord* pRecs, int DataCount)
{
	int pivot;
	int n1, n2;
	if (DataCount > 1)
	{
		QuickSplit(pRecs, DataCount, pivot);
		n1 = pivot + 1;
		n2 = DataCount - n1;
		QuickSort(pRecs, n1 - 1);
		QuickSort(pRecs + n1, n2);
	}
}

void TSortTable::QuickSplit(PTTabRecord* pData, int Size, int& Pivot)
{
	PTTabRecord pPivot = pData[0], pTemp;
	int i1 = 1, i2 = Size - 1;
	while (i1 <= i2)
	{
		while ((i1 < Size) && !(pData[i1]->Key > pPivot->Key)) i1++;
		while (pData[i2]->Key > pPivot->Key) i2--;
		if (i1 < i2)
		{
			pTemp = pData[i1];
			pData[i1] = pData[i2];
			pData[i2] = pTemp;
		}
	}
	pData[0] = pData[i2];
	pData[i2] = pPivot;
	Pivot = i2;
	Efficiency += Size;
}
void TSortTable::Print()
{
	Merge();
	for (Reset(); !IsTabEnded(); GoNext())
	{
		std::cout << " Key: " << GetKey();
		std::cout << "  Val: ";
		for (int i = 0; i < 5; i++)
			std::cout << GetValuePtr()[i] << " ";
		std::cout << std::endl;
	}
}
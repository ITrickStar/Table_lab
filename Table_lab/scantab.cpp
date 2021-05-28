#include "scantab.h"

int* TScanTable::FindRecord(TKey k)
{
    if (SortID == 0)
    {
        int i;
        for (i = 0; i < DataCount; i++)
            if (pRecs[i]->Key == k) break;
        Efficiency = i + 1;
        if (i < DataCount) { CurrPos = i; return pRecs[i]->pValue; }
        return NULL;
    }
    else
    {
        int midd = 0, left = 0, right = DataCount - 1;
        SortID = 0;
        while (left <= right)
        {
            midd = (left + right) / 2;
            if (k < pRecs[midd]->GetKey())
                right = midd - 1;
            else if (k > pRecs[midd]->GetKey())
                left = midd + 1;
            else
            {
                CurrPos = midd;
                return pRecs[midd]->GetValuePtr();
            }
        }
        CurrPos = left;
        return NULL;
    }
}
void TScanTable::InsRecord(TKey k, int* pVal)
{
    if (!IsFull())
    {
        if (SortID == 0)
        {
            pRecs[DataCount] = new TTabRecord(k, pVal);
            CurrPos = DataCount;
            DataCount++;
        }
        else
        {
            SortID = 0;
            int* temp = FindRecord(k);
            for (int i = DataCount; i > CurrPos; i--)
                pRecs[i] = pRecs[i - 1];
            pRecs[CurrPos] = new TTabRecord(k,pVal);
            CurrPos = DataCount;
            DataCount++;
        }
    }
}
void TScanTable::DelRecord(TKey k)
{
    if (SortID == 0)
    {

        int i;
        for (i = 0; i < DataCount; i++)
            if (pRecs[i]->Key == k) break;
        Efficiency = i + 1;
        if (i < DataCount)
        {
            DataCount--;
            for (int j = i; j < DataCount; j++)
            {
                pRecs[j]->pValue = pRecs[j + 1]->pValue;
                pRecs[j]->Key = pRecs[j + 1]->Key;
            }
            pRecs[DataCount]->pValue = NULL;
            pRecs[DataCount]->Key = "";
            pRecs[DataCount] = NULL;
            CurrPos = i - 1;
        }
    }
    else
    {
        SortID = 0;
        int midd = 0, left = 0, right = DataCount - 1, cheak = 1;
        while (cheak)
        {
            midd = (left + right) / 2;
            if (k < pRecs[midd]->GetKey())
                right = midd - 1;
            else if (k > pRecs[midd]->GetKey())
                left = midd + 1;
            else
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
                std::cout << "Record is not found\n";
                cheak = 0;
            }
        }
        CurrPos = midd - 1;
    }
}
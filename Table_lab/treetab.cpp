#include "treetab.h"

int TTreeTable::IsFull() const
{
	PTTreeNode pNode = new TTreeNode();
	int temp = pNode == NULL;
	delete pNode;
	return temp;
}

int* TTreeTable::FindRecord(TKey k)
{
	PTTreeNode pNode = pRoot;
	ppRef = &pRoot;
	Efficiency = 0;
	while (pNode != NULL)
	{
		Efficiency++;
		if (pNode->Key == k) break;
		if (pNode->Key < k) ppRef = &pNode->pRight;
		else ppRef = &pNode->pLeft;
		pNode = *ppRef;
	}
	return (pNode == NULL) ? NULL : pNode->pValue;
}

void TTreeTable::InsRecord(TKey k, int* pVal)
{
	if (!IsFull())
	{
		if (FindRecord(k) == NULL)
		{
			*ppRef = new TTreeNode(k, pVal);
			DataCount++;
		}
	}
}

void TTreeTable::DelRecord(TKey k)
{
	if (FindRecord(k) != NULL)
	{
		PTTreeNode pNode = *ppRef;
		if (pNode->pRight == NULL) *ppRef = pNode->pLeft;
		else if (pNode->pLeft == NULL) *ppRef = pNode->pRight;
		else
		{
			PTTreeNode pN = pNode->pLeft, * ppR = &pNode->pLeft;
			while (pN->pRight != NULL)
			{
				ppR = &pN->pRight;
				pN = *ppR;
			}
			pNode->pValue = pN->pValue;
			pNode->Key = pN->Key;
			pNode = pN;
			*ppR = pN->pLeft;
		}
		DataCount--;
		delete pNode;
	}
}

TKey TTreeTable::GetKey(void) const
{
	return (pCurrent == NULL) ? std::string("") : pCurrent->Key;
}

int* TTreeTable::GetValuePtr(void) const
{
	return (pCurrent == NULL) ? NULL : pCurrent->pValue;
}

int TTreeTable::Reset(void)
{
	PTTreeNode pNode = pCurrent = pRoot;
	while (!Stack.empty()) Stack.pop();
	CurrPos = 0;
	while (pNode != NULL)
	{
		Stack.push(pNode); pCurrent = pNode; pNode = pNode->GetLeft();
	}
	return IsTabEnded();
}

int TTreeTable::IsTabEnded(void) const
{
	return CurrPos >= DataCount;
}

int TTreeTable::GoNext(void)
{
	if ((!IsTabEnded()) && (pCurrent != NULL))
	{
		PTTreeNode pNode = pCurrent = pCurrent->GetRight();
		Stack.pop();
		while (pNode != NULL)
		{
			Stack.push(pNode);
			pCurrent = pNode;
			pNode = pNode->GetLeft();
		}
		if((pCurrent == NULL)&&(!Stack.empty()))
			pCurrent = Stack.top();
		CurrPos++;
	}
	return IsTabEnded();
}

std::ostream& operator<<(std::ostream &os, TTreeTable& tab)
{
	std::cout << "Table Printing" << std::endl;
	tab.PrintTreeTab(os, tab.pRoot);
	return os;
}

void TTreeTable::Draw(void) 
{
	std::cout << "Table Printing" << std::endl;
	DrawTreeTab(pRoot, 0);
}

void TTreeTable::PutValues(PTTreeNode pNode, int Level)
{
	if ((pNode != NULL) && (pos < 20))
	{
		PutValues(pNode->pLeft, Level + 1);
		tk[pos] = pNode->Key;
		t1[pos] = Level;
		pos++;
		PutValues(pNode->pRight, Level + 1);
	}
}

void TTreeTable::Show (void)
{
	int max1 = 0, i, j, k, pn;
	pos = 0;
	PutValues(pRoot, 0);
	for (i = 0; i < pos; i++)
		if (max1 < t1[i]) max1 = t1[i];
	std::cout << "Table Visualization" << std::endl;
	for (i = 0; i < max1 + 1; i++)
	{
		pn = 0;
		for (j = 0; j < pos; j++)
		{
			if (t1[j] == i)
			{
				for (k = 0; k < 2 * (j - pn); k++) std::cout << " ";
				std::cout << tk[j];
				pn = j + 1;
			}
		}
		std::cout << std::endl;
	}
}

void TTreeTable::PrintTreeTab(std::ostream &os, PTTreeNode pNode)
{
	if (pNode != NULL)
	{
		PrintTreeTab(os, pNode->pLeft);
		pNode->PrintRec(os);
		os << std::endl;
		PrintTreeTab(os,pNode->pRight);
	}
}

void TTreeTable::DrawTreeTab(PTTreeNode pNode, int Level)
{
	if (pNode != NULL)
	{
		DrawTreeTab(pNode->pRight, Level + 1);
		for (int i = 0; i < 2 * Level; i++) std::cout << " ";
		pNode->PrintRec(std::cout);
		std::cout << std::endl;
		DrawTreeTab(pNode->pLeft, Level + 1);
	}
}

void TTreeTable::DeleteTreeTab(PTTreeNode pNode)
{
	if (pNode != NULL)
	{
		DeleteTreeTab(pNode->pLeft);
		DeleteTreeTab(pNode->pRight);
		delete pNode;
	}
}
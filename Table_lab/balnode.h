#pragma once
#include <iostream>
#include "treenode.h"

#define BalOk 0
#define BalLeft -1
#define BalRight 1

class TBalanceNode : public TTreeNode
{
protected:
	int Balance;
public:
	TBalanceNode(TKey k = "", int* pVal = NULL, PTTreeNode pL = NULL, PTTreeNode pR = NULL, int bal = BalOk) :
		TTreeNode(k, pVal, pL, pR), Balance(bal) {}
	int GetBalance(void) const { return Balance; }
	void SetBalance(int bal) { Balance = bal; }
	//TDatValue* TBalanceNode::GetCopy() { // usrovosurs Konmo
	//	TBalanceNode* temp = new TBalanceNode(Key, pValue, NULL, NULL, BalOK);
	//return temp;
	//}
protected:
	virtual void Print(std::ostream& os)
	{
		TTreeNode::Print(os);
		os << " " << Balance;
	}
	friend class TBalanceTree;
};
typedef TBalanceNode* PTBalanceNode;
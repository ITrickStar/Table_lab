#pragma once
#include "treenode.h"
#include "ttable.h"
#include <stack>

class TTreeTable : public TTable
{
protected:
	PTTreeNode pRoot;
	PTTreeNode* ppRef;
	PTTreeNode pCurrent;
	int CurrPos;
	std::stack<PTTreeNode> Stack;
	void PrintTreeTab(std::ostream& os, PTTreeNode pNode);
	void DrawTreeTab(PTTreeNode pNode, int Level);
	void DeleteTreeTab(PTTreeNode pNode);
public:
	TTreeTable() : TTable()
	{
		CurrPos = 0; pRoot = pCurrent = NULL; ppRef = NULL;
	}
	~TTreeTable() { DeleteTreeTab(pRoot); }
	virtual int IsFull() const;
	virtual int* FindRecord(TKey k);
	virtual void InsRecord(TKey k, int* pVal);
	virtual void DelRecord(TKey k);
	virtual TKey GetKey(void) const;
	virtual int* GetValuePtr(void) const;
	virtual int Reset(void);
	virtual int IsTabEnded(void) const;
	virtual int GoNext(void);
	virtual void Print(TTable& tab) {}
	virtual PTTabRecord* GetAllpRecs() const { return NULL; }
	friend std::ostream& operator<<(std::ostream &os, TTreeTable& tab);
	void Draw(void);
	void Show(void);
protected:
	std::string tk[20];
	int t1[20], pos;
	void PutValues(PTTreeNode pNode, int Level);
};
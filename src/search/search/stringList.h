#pragma once
#include "CharString.h"
#include <fstream>

struct Node
{
	CharString data;
	Node *next;
};
class StringList
{
private:
	Node* tail;
public:
	Node* head;
	StringList();
	~StringList();
	bool add(CharString m);
	bool removeLast(CharString &m);
	bool removeFirst(CharString &m);
	Node * search(CharString& m)
	{
		Node *p = head->next;
		while (p != nullptr)
		{
			if (p->data.compare(m) == 0)
				break;
			p = p->next;
		}
		if (p != nullptr)
			return p;
		else
			return nullptr;
	}
	void out(fstream &out);//将节点信息输入到文件中
	StringList(StringList &m);
	StringList &operator=(StringList m);
};

#ifndef _STRINGLIST_H
#define _STRINGLIST_H
#include "CharString.h"
#include <fstream>
//字符串链表
class StringList
{
	struct Node
	{
		CharString data;
		Node *next;
	};

public:
	Node* head;
	Node* tail;
	StringList();
	~StringList();
	bool add(CharString &m);
	bool removeLast(CharString &m);
	bool removeFirst(CharString &m);
	//查找节点
	Node * search(CharString &m)
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
	void putout(fstream &out);//将节点信息输入到文件中
	StringList(StringList &m);
	StringList &operator=(StringList m);
};

#endif
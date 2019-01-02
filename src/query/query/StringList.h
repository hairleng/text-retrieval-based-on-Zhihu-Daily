#ifndef _STRINGLIST_H
#define _STRINGLIST_H
#include "CharString.h"
#include <fstream>
//�ַ�������
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
	//���ҽڵ�
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
	void putout(fstream &out);//���ڵ���Ϣ���뵽�ļ���
	StringList(StringList &m);
	StringList &operator=(StringList m);
};

#endif
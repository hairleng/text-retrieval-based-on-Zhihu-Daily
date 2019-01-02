#include "CharString.h"
#include <fstream>
#include "StringList.h"

StringList::StringList()//��ʼ��
{
	head = new Node;
	tail = head;
	head->next = nullptr;
}
StringList::~StringList()//�ͷ��ڴ�
{
	Node *p;
	while (head != nullptr)
	{
		p = head;
		head = head->next;
		delete p;
	}
}
bool StringList::add(CharString &m)//��ӽڵ�
{
	Node *p = new Node;
	p->data = m;
	p->next = nullptr;
	if (head->next == nullptr)
	{
		head->next = p;
		tail = p;
	}
	else
	{
		tail->next = p;
		tail = p;
	}
	return true;
}
bool StringList::removeLast(CharString &m)//�Ƴ����ڵ�
{
	if (tail == head)
		return false;
	m = tail->data;
	Node *p = head;
	while (p->next != tail)
	{
		p = p->next;
	}
	delete tail;
	tail = p;
	tail->next = nullptr;
	return true;
}
bool StringList::removeFirst(CharString &m)//�Ƴ���ʼ�ڵ�
{
	if (tail == head)
		return false;
	m = head->next->data;
	Node *p = head->next;
	head->next = p->next;
	if (p == tail)
	{
		tail = head;
		head->next = nullptr;
	}
	delete p;
	return true;
}
void StringList::putout(fstream &out)//���ڵ���Ϣ���뵽�ļ���
{
	Node *p = head->next;
	while (p != nullptr)
	{
		out << p->data << endl;
		p = p->next;
	}
}
StringList::StringList(StringList & m)
{
	head = new Node;
	tail = head;
	head->next = nullptr;
	Node *q = m.head->next;
	while (q != nullptr)
	{
		add(q->data);
		q = q->next;
	}
}
StringList & StringList::operator=(StringList m)
{
	head = new Node;
	tail = head;
	head->next = nullptr;
	Node *q = m.head->next;
	while (q != nullptr)
	{
		add(q->data);
		q = q->next;
	}
	return *this;
}
;
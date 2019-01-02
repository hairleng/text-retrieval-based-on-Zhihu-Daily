#include "CharString.h"
#include <fstream>
#include "StringList.h"

StringList::StringList()
{
	head = new Node;
	tail = head;
	head->next = nullptr;
}
StringList::~StringList()
{
	Node *p;
	while (head != nullptr)
	{
		p = head;
		head = head->next;
		delete p;
	}
}
bool StringList::add(CharString m)//添加节点
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
bool StringList::removeLast(CharString &m)
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
bool StringList::removeFirst(CharString &m)
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
void StringList::out(fstream &out)//将节点信息输入到文件中
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
#include<iostream>
#include"stack.h"
using namespace std;

Stack::Stack()
{
	base = new Elem;
	base->next = nullptr;
	top = base;
}

Stack::~Stack()
{
	Elem* p;
	while (top != nullptr)
	{
		p = top;
		top = top->next;
		delete p;
	}
}

bool Stack::push(CharString &m)
{
	Elem* p;
	p = top;
	top = new Elem;
	top->data = m;
	top->next = p;
	return true;
}

bool Stack::pop(CharString &m)//退栈
{
	if (base == top)
		return false;
	Elem* p;
	p = top;
	m = top->data;
	top = top->next;
	delete p;
	return true;
}
bool Stack::empty()//是否为空
{
	if (base == top)
		return true;
	return false;
}

int Stack::length()//栈长度
{
	int len = 0;
	Elem* p = top;
	while (p != base)
	{
		p = p->next;
		len++;
	}
	return len;
}

bool Stack::getTop(CharString &m)
{
	if (top == base)
		return false;
	m = top->data;
	return true;
}


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

bool Stack::pop(CharString &m)
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
bool Stack::isEmpty()
{
	if (base == top)
		return true;
	return false;
}

int Stack::length()
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

void Stack::printStack()
{
	if (!base)
		return;
	Elem *p = base;
	for (int i = 0; i < length(); i++)
	{
		cout << p->data.tocstr();
		cout << endl;
		p = p->next;
	}
}

void Stack::clear()
{
	Elem *p = top;
	for (int i = 0; i < length(); i++)
	{
		Elem *temp = p;
		p = p->next;
		delete temp;
	}
	base = new Elem;
	top = base;
}
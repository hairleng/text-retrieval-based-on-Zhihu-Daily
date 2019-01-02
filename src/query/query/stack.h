#ifndef _STACK_H
#define _STACK_H
#include <iostream>
#include "CharString.h"
using namespace std;

class Stack
{
	struct Elem
	{
		CharString data;
		Elem* next;
	};
private:
	Elem* base;
	Elem* top;
	int len;
public:
	Stack();
	~Stack();
	bool push(CharString &m);
	bool pop(CharString &m);
	bool isEmpty();
	int length();
	bool getTop(CharString &m);
	void printStack();
	void clear();
};


#endif
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
public:
	Stack();
	~Stack();
	bool push(CharString &m);
	bool pop(CharString &m);
	bool empty();
	int length();
	bool getTop(CharString &m);
};


#endif
#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include "StringList.h"
#include <iostream>


//��ϣ��
class HashTable
{
private:
	StringList** head;
	int num;
public:
	HashTable();
	HashTable(int n);
	~HashTable();

	unsigned int Hash(CharString &m);//���ӳ��Ĺ�ϣֵ���õ�Ч�ʽϸߵ�BKDR_hash�㷨
	bool add(CharString &m);//�������
	bool search(CharString &m);//�ڹ�ϣ��������m
};

#endif
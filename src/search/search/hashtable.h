#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include "StringList.h"
#include <iostream>


//哈希表
class HashTable
{
private:
	StringList** head;
	int num;
public:
	HashTable();
	HashTable(int n);
	~HashTable();

	unsigned int Hash(CharString &m);//获得映射的哈希值，用的效率较高的BKDR_hash算法
	bool add(CharString &m);//添加因子
	bool search(CharString &m);//在哈希表中搜索m
};

#endif
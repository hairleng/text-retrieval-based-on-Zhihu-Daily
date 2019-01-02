#include "hashtable.h"
using namespace std;
#define MAXHASH 250000

HashTable::HashTable()
{
	num = MAXHASH;
	head = new StringList*[MAXHASH];
	for (int i = 0; i < MAXHASH; i++)
		head[i] = nullptr;
}
HashTable::HashTable(int n)
{
	num = n;
	head = new StringList *[n];
	for (int i = 0; i < n; i++)
		head[i] = nullptr;
}

HashTable::~HashTable()
{
	delete[] head;
}

unsigned int HashTable::Hash(CharString &m)
{
	unsigned int seed = 131;
	unsigned int hash = 0;
	int i = 0;
	while (i < m.Length())
	{
		hash = hash * seed + m[i];
		i++;
	}
	return (hash & 0x7FFFFFFF) % num;
}
bool HashTable::add(CharString &m)
{
	unsigned int hash = Hash(m);
	//不是冲突的因子
	if (head[hash] == nullptr)
	{
		head[hash] = new StringList;
		head[hash]->add(m);
	}
	//是冲突因子 接在该位置的链表尾端
	else
	{
		head[hash]->add(m);
	}
	return true;
}
bool HashTable::search(CharString &m)
{
	unsigned int hash = Hash(m);
	//对应位置无元素
	if (head[hash] == nullptr)
		return false;
	else
	{
		//对应位置有元素且符合
		if (head[hash]->search(m) != nullptr)
			return true;
	}
	return false;
}
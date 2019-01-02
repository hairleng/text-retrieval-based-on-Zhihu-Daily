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
	//���ǳ�ͻ������
	if (head[hash] == nullptr)
	{
		head[hash] = new StringList;
		head[hash]->add(m);
	}
	//�ǳ�ͻ���� ���ڸ�λ�õ�����β��
	else
	{
		head[hash]->add(m);
	}
	return true;
}
bool HashTable::search(CharString &m)
{
	unsigned int hash = Hash(m);
	//��Ӧλ����Ԫ��
	if (head[hash] == nullptr)
		return false;
	else
	{
		//��Ӧλ����Ԫ���ҷ���
		if (head[hash]->search(m) != nullptr)
			return true;
	}
	return false;
}
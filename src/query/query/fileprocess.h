#ifndef _FILEPROCESS_H
#define _FILEPROCESS_H
#include "CharString.h"
#include "stack.h"
#include "StringList.h"
#include "hashtable.h"
#include <iostream>
#include <fstream>
//ʵ��һ�ӿں��� + �����ĵ� + �ִ��������
#include <string>
#include <vector>
#include <io.h>
#include "AVLTree.h"
using namespace std;

void extractInfo(string filename, StringList &L, HashTable &removehash, 
	HashTable &authorhash, CharString *removeList, CharString *replaceList, 
	int maxremove, int &authorLine);//remove ת���ַ� author ����+����
void initDictionary(char * filename, HashTable & hash);//��ʼ���ʵ� ��ϣ��洢

void divideWords(StringList &L, HashTable & hash, StringList &answer, 
	HashTable & movehash);//�����ӵ�StringList�� movehash�����Ƴ�������Ϣ

void init(CharString keyWords, AVLTree &tree, HashTable & hash, 
	HashTable & movehash);//�ִʽ���Ĺ�ϣ���ʼ�� ���ķִʶ�AVL����ʼ��

void search(CharString &searchWords, docList & searchdoc, 
	AVLTree &tree, HashTable & hash, HashTable & movehash);//����searchWords �ִ������������searchdoc

#endif
#ifndef FILEPROCESS_H
#define FILEPROCESS_H
#include "CharString.h"
#include "stack.h"
#include "StringList.h"
#include "hashtable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <io.h>
#include "AVLTree.h"
using namespace std;
//��ؽӿ�
void extractInfo(string filename, StringList &L, HashTable &removehash, 
HashTable &authorhash, CharString *removeList, CharString *replaceList,
int maxremove, int &authorLine);//remove ת���ַ� author ����+����

void initDictionary(char * filename, HashTable & hash);//��ʼ���ʵ� ��ϣ��洢

void divideWords(StringList &L, HashTable & hash, StringList &answer,
	HashTable & movehash);//�����ӵ��ַ�������answer�У�movehash �Ƴ����ֵ��ֺͷ��ŵĹ�ϣ��

void init(CharString command, AVLTree &tree, HashTable & hash, HashTable & movehash);//���÷ִʽ����ʼ��AVLTree

void searchAll(CharString &searchline, docList & searchdoc, AVLTree &tree, HashTable & hash, 
	HashTable & movehash);//����searchline �ִ������������searchdoc

void makeInfo(const char *filename, StringList &sum, CharString &searchline, 
	HashTable & hash, HashTable & movehash);//�򿪶�Ӧ�ļ� ��������highlight��������뵽sum��

void initHash(HashTable & hash, HashTable & movehash, HashTable & removehash, HashTable & authorhash, 
	CharString *removeList, CharString *replaceList);//��ʼ�����Ĺ�ϣ���Լ����������Ϣ�Ĺ�ϣ��

#endif
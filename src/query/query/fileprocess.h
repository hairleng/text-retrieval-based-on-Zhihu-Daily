#ifndef _FILEPROCESS_H
#define _FILEPROCESS_H
#include "CharString.h"
#include "stack.h"
#include "StringList.h"
#include "hashtable.h"
#include <iostream>
#include <fstream>
//实验一接口函数 + 倒排文档 + 分词搜索结果
#include <string>
#include <vector>
#include <io.h>
#include "AVLTree.h"
using namespace std;

void extractInfo(string filename, StringList &L, HashTable &removehash, 
	HashTable &authorhash, CharString *removeList, CharString *replaceList, 
	int maxremove, int &authorLine);//remove 转义字符 author 作者+逗号
void initDictionary(char * filename, HashTable & hash);//初始化词典 哈希表存储

void divideWords(StringList &L, HashTable & hash, StringList &answer, 
	HashTable & movehash);//结果添加到StringList中 movehash用于移除冗余信息

void init(CharString keyWords, AVLTree &tree, HashTable & hash, 
	HashTable & movehash);//分词结果的哈希表初始化 中文分词对AVL树初始化

void search(CharString &searchWords, docList & searchdoc, 
	AVLTree &tree, HashTable & hash, HashTable & movehash);//输入searchWords 分词搜索结果传到searchdoc

#endif
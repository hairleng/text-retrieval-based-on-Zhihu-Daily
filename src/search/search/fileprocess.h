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
//相关接口
void extractInfo(string filename, StringList &L, HashTable &removehash, 
HashTable &authorhash, CharString *removeList, CharString *replaceList,
int maxremove, int &authorLine);//remove 转义字符 author 作者+逗号

void initDictionary(char * filename, HashTable & hash);//初始化词典 哈希表存储

void divideWords(StringList &L, HashTable & hash, StringList &answer,
	HashTable & movehash);//结果添加到字符串链表answer中，movehash 移除部分单字和符号的哈希表

void init(CharString command, AVLTree &tree, HashTable & hash, HashTable & movehash);//利用分词结果初始化AVLTree

void searchAll(CharString &searchline, docList & searchdoc, AVLTree &tree, HashTable & hash, 
	HashTable & movehash);//输入searchline 分词搜索结果传到searchdoc

void makeInfo(const char *filename, StringList &sum, CharString &searchline, 
	HashTable & hash, HashTable & movehash);//打开对应文件 对搜索词highlight处理后输入到sum中

void initHash(HashTable & hash, HashTable & movehash, HashTable & removehash, HashTable & authorhash, 
	CharString *removeList, CharString *replaceList);//初始化正文哈希表以及各类多余信息的哈希表

#endif
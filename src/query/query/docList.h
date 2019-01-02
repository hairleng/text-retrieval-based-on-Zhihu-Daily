#ifndef _DOCLIST_H
#define _DOCLIST_H
#include <iostream>
#include <fstream>
using namespace std;

class docNode
{
public:
	docNode(int doc);
	~docNode() {};
	int docID;
	int times;
	int keywordNum;//搜索的关键词个数
	docNode * next;
};

class docList
{
public:
	docNode * head;
	docNode * tail;
	docList();
	~docList() {};
	void Add(int &doc);//累加文档次数
	docNode* Search(int &doc);//搜索文档
	bool Remove(int &doc);//移除文档
	bool Edit(int &doc, int &times);//编辑文档次数
	void output(fstream &out);//向文件中输出链表内容，用于搜索
	bool isEmpty();
	void merge(docList *m);
	void sort();//链表排序 major factor关键词出现个数 minor factor出现次数
};

#endif
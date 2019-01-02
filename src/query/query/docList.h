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
	int keywordNum;//�����Ĺؼ��ʸ���
	docNode * next;
};

class docList
{
public:
	docNode * head;
	docNode * tail;
	docList();
	~docList() {};
	void Add(int &doc);//�ۼ��ĵ�����
	docNode* Search(int &doc);//�����ĵ�
	bool Remove(int &doc);//�Ƴ��ĵ�
	bool Edit(int &doc, int &times);//�༭�ĵ�����
	void output(fstream &out);//���ļ�������������ݣ���������
	bool isEmpty();
	void merge(docList *m);
	void sort();//�������� major factor�ؼ��ʳ��ָ��� minor factor���ִ���
};

#endif
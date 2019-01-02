#ifndef DOCLIST_H
#define DOCLIST_H
#include <iostream>
#include <fstream>
using namespace std;
//倒排文档链表
class docNode//文档节点
{
public:
	docNode(int doc) :docID(doc), times(1), next(nullptr), keywordNum(1) {};//构造函数
	~docNode() {};
	int docID;//文档编号
	int times;//单词出现次数
	int keywordNum;//搜索时所用记录文档中包含关键词个数
	docNode * next;
};
class docList
{
public:
	docNode * head;
	docNode * tail;
	docList() :head(nullptr), tail(nullptr) {};//构造函数
	~docList() //析构函数
	{
		docNode *p, *q;
		p = head;
		while (p != nullptr)
		{
			q = p;
			p = p->next;
			delete q;
		}
		head = nullptr;
		tail = nullptr;
	};
	void clear()
	{
		docNode *p, *q;
		p = head;
		while (p != nullptr)
		{
			q = p;
			p = p->next;
			delete q;
		}
		head = tail = nullptr;
	}
	void Add(int &doc)
	{
		docNode *p = Search(doc);//搜索文档
		if (p != nullptr)//p已存在
		{
			p->times++;
		}
		else
		{
			p = new docNode(doc);
			//p为头结点
			if (head == nullptr)
				tail = head = p;
			else
			{
				tail->next = p;
				tail = p;
			}
		}
	}

	docNode* Search(int &doc)
	{
		docNode * p = head;
		while (p != nullptr)
		{
			if (p->docID == doc)
				break;
			p = p->next;
		}
		return p;
	}

	bool Remove(int &doc)
	{
		if (head == nullptr)
			return false;
		docNode *p = Search(doc);
		if (p != nullptr)
		{
			if (p == head)
			{
				if (tail == head)
					tail = nullptr;
				head = p->next;
				delete p;
			}
			else
			{
				docNode * q = head;
				while (q->next != p)
					q = q->next;
				q->next = p->next;
				if (tail == p)
					tail = q;
				delete p;
			}
			return true;
		}
		else
			return false;
	}

	bool Edit(int &doc, int &times)
	{
		docNode * p = Search(doc);
		if (p != nullptr)
		{
			p->times = times;
			return true;
		}
		else
			return false;
	}
	void output(fstream &out)//输出链表内容
	{
		docNode *p = head;
		while (p != nullptr)
		{
			if (p == head)
				out << "(" << p->docID << "," << p->times << ")";
			else
				out << " (" << p->docID << "," << p->times << ")";
			p = p->next;
		}
		out << endl;
	}
	bool isEmpty()
	{
		if (head == nullptr)
			return true;
		return false;
	}

	void merge(docList *list)
	{
		if (head == nullptr)//该链表为空，复制链表
		{
			docNode *p, *q;
			q = list->head;
			while (q != nullptr)//待合并链表不空
			{
				p = new docNode(q->docID);
				p->times = q->times;
				p->keywordNum = q->keywordNum;
				if (head == nullptr)
				{
					head = tail = p;
				}
				else
				{
					tail->next = p;
					tail = p;
				}
				q = q->next;
			}
		}
		else//链表不空，相同节点次数相加 新节点接到末尾
		{
			docNode *p, *q;
			docNode* node;
			p = head;
			q = list->head;
			while (p && q)//待合并链表不空
			{
				if (p->docID == q->docID)
				{
					p->times += q->times;
					p->keywordNum++;
					p = p->next;
					q = q->next;
				}
				else if (p->docID < q->docID)
				{
					while (p && p->docID < q->docID)//p.docID小不断找p的next
						p = p->next;
					if (p != nullptr)
					{
						if (p->docID == q->docID)
						{
							p->times += q->times;
							p->keywordNum++;
							p = p->next;
							q = q->next;
						}
						else//p.docID比q大 增加节点末尾复制q
						{
							node = new docNode(q->docID);
							node->times = q->times;
							node->keywordNum = q->keywordNum;
							if (head == nullptr)
							{
								head = tail = node;
							}
							else
							{
								tail->next = node;
								tail = node;
							}
							q = q->next;
						}
					}
				}
				else//p.docID比q大，直接末尾添加节点 复制q的值
				{
					node = new docNode(q->docID);
					node->times = q->times;
					node->keywordNum = q->keywordNum;
					if (head == nullptr)
					{
						head = tail = node;
					}
					else
					{
						tail->next = node;
						tail = node;
					}
					q = q->next;
				}
			}
			while (q)//p空了 q不空 增加节点复制q的值
			{
				node = new docNode(q->docID);
				node->times = q->times;
				node->keywordNum = q->keywordNum;
				if (head == nullptr)
					head = tail = node;
				else
				{
					tail->next = node;
					tail = node;
				}
				q = q->next;
			}
		}
	}

	void sort()
	{
		if (head == nullptr)
			return;
		docNode *p, *q, *end;
		p = q = end = nullptr;

		//按照关键词出现个数排序
		q = head->next;
		p = head;
		end = nullptr;
		int temp;
		while (head->next != end)
		{
			p = head;
			q = head->next;
			while (q != end)
			{
				if (q->keywordNum > p->keywordNum)
				{
					temp = q->docID;
					q->docID = p->docID;
					p->docID = temp;

					temp = q->times;
					q->times = p->times;
					p->times = temp;

					temp = q->keywordNum;
					q->keywordNum = p->keywordNum;
					p->keywordNum = temp;
				}
				p = p->next;
				q = q->next;
			}
			end = p;
		}
		//个数同 按照出现次数排序
		docNode *s_begin, *s_end, *tempNode;
		s_begin = head;

		while (s_begin != nullptr)
		{
			p = s_begin;
			while (p && p->keywordNum == s_begin->keywordNum)
			{
				p = p->next;
			}
			s_end = p;
			tempNode = p;
			while (s_begin->next != s_end)
			{
				p = s_begin;
				q = s_begin->next;
				while (q != s_end)
				{
					if (q->times > p->times)
					{
						temp = q->docID;
						q->docID = p->docID;
						p->docID = temp;
						temp = q->times;
						q->times = p->times;
						p->times = temp;
						temp = q->keywordNum;
						q->keywordNum = p->keywordNum;
						p->keywordNum = temp;
					}
					p = p->next;
					q = q->next;
				}
				s_end = p;
			}
			s_begin = tempNode;
		}
	}
};

#endif
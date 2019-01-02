#ifndef DOCLIST_H
#define DOCLIST_H
#include <iostream>
#include <fstream>
using namespace std;
//�����ĵ�����
class docNode//�ĵ��ڵ�
{
public:
	docNode(int doc) :docID(doc), times(1), next(nullptr), keywordNum(1) {};//���캯��
	~docNode() {};
	int docID;//�ĵ����
	int times;//���ʳ��ִ���
	int keywordNum;//����ʱ���ü�¼�ĵ��а����ؼ��ʸ���
	docNode * next;
};
class docList
{
public:
	docNode * head;
	docNode * tail;
	docList() :head(nullptr), tail(nullptr) {};//���캯��
	~docList() //��������
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
		docNode *p = Search(doc);//�����ĵ�
		if (p != nullptr)//p�Ѵ���
		{
			p->times++;
		}
		else
		{
			p = new docNode(doc);
			//pΪͷ���
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
	void output(fstream &out)//�����������
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
		if (head == nullptr)//������Ϊ�գ���������
		{
			docNode *p, *q;
			q = list->head;
			while (q != nullptr)//���ϲ�������
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
		else//�����գ���ͬ�ڵ������� �½ڵ�ӵ�ĩβ
		{
			docNode *p, *q;
			docNode* node;
			p = head;
			q = list->head;
			while (p && q)//���ϲ�������
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
					while (p && p->docID < q->docID)//p.docIDС������p��next
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
						else//p.docID��q�� ���ӽڵ�ĩβ����q
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
				else//p.docID��q��ֱ��ĩβ��ӽڵ� ����q��ֵ
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
			while (q)//p���� q���� ���ӽڵ㸴��q��ֵ
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

		//���չؼ��ʳ��ָ�������
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
		//����ͬ ���ճ��ִ�������
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
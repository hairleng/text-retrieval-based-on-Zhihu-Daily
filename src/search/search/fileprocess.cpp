#pragma once
#include "CharString.h"
#include "stack.h"
#include "StringList.h"
#include "fileprocess.h"
#include "hashtable.h"
#include <iostream>
#include <fstream>
using namespace std;
#define MAXLEN 9
#define MAXREMOVE 8//�ִʺ����е�ת���ַ�������
#define MAINMAXREMOVE 12//init����������������
bool isTag(CharString m)//�ж��Ƿ�Ϊtag
{
	if (m.compare(CharString("meta")) == 0)
		return false;
	if (m.compare(CharString("!doctype")) == 0)
		return false;
	if (m.compare(CharString("link")) == 0)
		return false;
	if (m.compare(CharString("base")) == 0)
		return false;
	if (m.compare(CharString("img")) == 0)
		return false;
	if (m.compare(CharString("br")) == 0)
		return false;
	if (m.compare(CharString("hr")) == 0)
		return false;
	if (m.compare(CharString("button")) == 0)
		return true;
	if (m.indexof("!--", 0) != -1)
		return true;
	return true;

}
void extractInfo(string filename, StringList & L, HashTable &removehash, HashTable &authorhash, CharString *removeList, CharString *replaceList, int maxremove, int &authorLine)
{
	fstream in(filename, ios::in);
	Stack list;//���CharString
	CharString buffer, temp, m, templist, content;//tempΪ��ǩ,templistΪ��ǩ���ݣ�mΪ������contentΪ����Ҫ��ȡ���ݡ�
	int pos = 0;
	int authornum = 1, authorChange = 0;
	bool add = 0, titleadd = 0;
	while (in >> buffer)
	{
		pos = 0;
		while (buffer.indexof("<", pos) != -1 && pos < buffer.Length())
		{
			if (buffer.indexof(">", buffer.indexof("<", pos) + 1) != -1)
			{
				templist = buffer.subString(buffer.indexof("<", pos) + 1,
					buffer.indexof(">", buffer.indexof("<", pos) + 1) - buffer.indexof("<", pos) - 1);//�ҵ�ÿ����ǩ����
				pos = buffer.indexof(">", buffer.indexof("<", pos) + 1) + 1;//����ɨ��λ��
				if (templist.indexof(" ", 0) == -1)
				{
					temp = templist;//�ҵ���ǩ
				}
				else
				{
					temp = templist.subString(0, templist.indexof(" ", 0));//�ҵ���ǩ
				}
				if (isTag(temp))
				{
					if (templist.indexof("class=\"headline-title\"", 0) != -1 ||
						templist.indexof("class=\"question-title\"", 0) != -1 ||
						templist.indexof("class=\"author\"", 0) != -1 ||
						templist.indexof("class=\"content\"", 0) != -1)
					{
						//���Ŀ�ʼ��ǩ
						add = 1;
						titleadd = 1;
					}
					if (temp[0] == '/')//����ǽ�����ǩ
					{
						temp = temp.subString(1, temp.Length() - 1);
						list.pop(m);
						if (m[0] == '1')
						{
							add = 0;//��������
							m = m.subString(1, m.Length() - 1);
						}
						if (m.compare(temp) != 0)
							list.push(m);
					}
					else//����ǿ�ʼ��ǩ
					{
						if (add == 0)
							list.push(temp);
						else if (add == 1 && titleadd == 1)
						{
							CharString n("1");//���⿪ʼ��־��ʼ��Ϊ1
							temp = n.concat(temp);
							list.push(temp);
							titleadd = 0;
						}
						else
						{
							list.push(temp);
						}
					}
					if (add == 1 && pos < buffer.Length())
					{
						//��ʼ��ȡ����content
						if (buffer.indexof("<", pos) != -1)
							content = buffer.subString(pos, buffer.indexof("<", pos) - pos);
						else
							content = buffer.subString(pos, buffer.Length() - pos);
						if (!content.isEmpty())
						{
							L.add(content);//���
							authornum++;//����λ�ø���
						}
					}
				}
			}
		}
	}
	//ȥ��ĩβ���
	CharString irrelevant;
	L.removeLast(irrelevant);
	L.removeLast(irrelevant);
	L.removeLast(irrelevant);
}
void initDictionary(char * filename, HashTable & hash)
{
	fstream in(filename, ios::in);
	if (!in.is_open())
	{
		cout << "Open file failed" << endl;
		return;
	}
	CharString buffer;
	while (in >> buffer)
	{
		hash.add(buffer);//�����ϣ��
	}
}

void divideWords(StringList &L, HashTable &hash, StringList &answer, HashTable &movehash)
{
	CharString list;
	int pos = 0, end = 0, len = 0;
	while (L.removeFirst(list))//��ȡÿһ��
	{
		pos = 0;
		len = list.Length();
		while (pos < len)
		{
			//����λ��
			if (list[pos] > 0)//��һ���ַ���������
			{
				pos++;
				continue;
			}
			else
			{
				for (int i = MAXLEN; i > 0; i--)//����ȡ
				{
					if (i == 1)
					{
						answer.add(list.subString(pos, 3));//��������
						pos += 3;
					}
					else//����ж�
					{
						if (pos + i * 3 - 1 < len - 1)
							end = pos + i * 3 - 1;
						else
							end = pos + (len - pos) / 3 * 3 - 1;
						if (hash.search(list.subString(pos, end - pos + 1)))
						{
							answer.add(list.subString(pos, end - pos + 1));
							pos += i * 3;
							break;
						}
					}
				}

			}
		}
	}
}
void initHash(HashTable & hash, HashTable & movehash, HashTable & removehash, HashTable & authorhash, CharString *removeList, CharString *replaceList)
{
	initDictionary("dic\\�ʿ�.dic", hash);//
	initDictionary("dic\\remove.dic", removehash);//ȥ��ת���ַ�
	initDictionary("dic\\author.dic", authorhash);//ȥ�����߶���
	initDictionary("dic\\move.dic", movehash);//�ִ�ʱȥ�������뵥��
												 //�滻�ַ������ʼ��
	fstream fremove("dic\\remove.dic", ios::in || ios::out);
	int i = 0;
	while (fremove >> removeList[i])
		i++;
	i = 0;
	fstream freplace("dic\\replace.dic", ios::in || ios::out);
	while (freplace >> replaceList[i])
		i++;
}

void searchAll(CharString &searchline, docList & searchdoc, AVLTree &tree, HashTable & hash, HashTable & movehash)
{
	StringList searchlist;//����Ķ���ؼ���
	StringList searchWord; //�ִʺ󵥸��ؼ���
	docList *docTemp;//searchdocΪҪ����ĵ�����
	CharString searchTemp;
	searchlist.add(searchline);
	divideWords(searchlist, hash, searchWord, movehash);
	while (searchWord.removeFirst(searchTemp))//��ÿһ���ؼ��ʽ�������
	{
		if (tree.Search(tree.root,searchTemp) != nullptr)
		{
			docTemp = tree.Search(tree.root,searchTemp)->docline;//�ҵ��ؼ��ʶ�Ӧ����
			searchdoc.merge(docTemp);//����ϲ�
		}
	}
	searchdoc.sort();//��������
}
//�򿪶�Ӧ�ļ������ʽ��б�촦������뵽sum�С�
void makeInfo(const char *filename, StringList &sum, CharString &searchline, HashTable & hash, HashTable & movehash)
{
	fstream in(filename, ios::in);
	StringList wordlist, wordtemp;
	wordtemp.add(searchline);
	divideWords(wordtemp, hash, wordlist, movehash);//�ֳ�������
	CharString buffer;
	int pos = 0;// posΪ����λ��
	int isInput = 0;
	bool isDeleteA = false;
	bool isDeleteImg = false;
	while (in >> buffer)//����ÿһ��
	{
		if (buffer.indexof("class=\"view-more\"", 0) != -1)//ȥ��β���
		{
			isInput = 1;
			break;
		}
		if (buffer.indexof("class=\"qr\"", 0) != -1)//ȥ��β���
		{
			isInput = 2;
			break;
		}
		while (buffer.indexof("<a", 0) != -1 || buffer.indexof("</a", 0) != -1) //ȥ����
		{
			int beginapos = buffer.indexof("<a", 0);
			if (beginapos != -1)
				isDeleteA = true;//��ɾ�������źŴ�
			if (isDeleteA == true)
			{
				int endapos = buffer.indexof("</a", 0);
				if (endapos != -1)//ɾ����Ӧ����
				{
					isDeleteA = false;//�ر�ɾ�������ź�
					CharString concatTemp;
					if (beginapos != -1)//���ӱ�־ͬ��
					{
						concatTemp = buffer.subString(0, beginapos);
						buffer = concatTemp.concat(buffer.subString(buffer.indexof(">", endapos) + 1, buffer.Length() - buffer.indexof(">", endapos) - 1));
					}
					else//���ӱ�־��ͬ��
					{
						buffer = buffer.subString(buffer.indexof(">", endapos) + 1, buffer.Length() - buffer.indexof(">", endapos) - 1);
					}
				}
				else
					break;
			}
		}
		while (buffer.indexof("<img", 0) != -1)//ȥͼƬ
		{
			int beginImgpos = buffer.indexof("<img", 0);
			if (beginImgpos != -1)
				isDeleteImg = true;//��ɾ��ͼƬ�ź�
			if (isDeleteImg == true)
			{
				int endImgpos;
				if (beginImgpos != -1)
					endImgpos = buffer.indexof(">", beginImgpos);
				else
					endImgpos = buffer.indexof(">", 0);
				if (endImgpos != -1)//ɾ����ӦͼƬ
				{
					isDeleteImg = false;//�ر�ɾ��ͼƬ�ź�
					CharString concatTemp;
					if (beginImgpos != -1)//ͼƬ��־ͬ��
					{
						concatTemp = buffer.subString(0, beginImgpos);
						buffer = concatTemp.concat(buffer.subString(endImgpos + 1, buffer.Length() - 1 - endImgpos));
					}
					else//ͼƬ��־��ͬ��
					{
						buffer = concatTemp.concat(buffer.subString(endImgpos + 1, buffer.Length() - 1 - endImgpos));
					}
				}
				else
					break;

			}
		}
		if (isDeleteA == false && isDeleteImg == false)//ִ�ж������
		{
			Node *p;
			p = wordlist.head->next;
			while (p != nullptr)//��ÿһ���ؼ��ʽ��б��
			{
				pos = 0;
				while (pos < buffer.Length() && buffer.indexof(p->data, pos) != -1)
				{
					CharString concatTemp;
					concatTemp = buffer.subString(0, buffer.indexof(p->data, pos));
					concatTemp = concatTemp.concat(CharString("<font color=red>"));
					concatTemp = concatTemp.concat(p->data);
					concatTemp = concatTemp.concat(CharString("</font>"));
					buffer = concatTemp.concat(buffer.subString(buffer.indexof(p->data, pos) + p->data.Length(), buffer.Length() - buffer.indexof(p->data, pos) - p->data.Length()));
					pos = concatTemp.Length();
				}
				p = p->next;
			}
			if (!buffer.isEmpty())
				sum.add(buffer);//����sum
		}
	}
	if (isInput == 1)//����ṹ
	{
		sum.add("</div>");
		sum.add("</div>");
		sum.add("</div>");
		sum.add("</body>");
		sum.add("</html>");
	}
	if (isInput == 2)//����ṹ
	{
		sum.add("</div>");
		sum.add("</body>");
		sum.add("</html>");
	}
}



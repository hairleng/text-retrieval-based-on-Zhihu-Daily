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

bool isTag(CharString &m)//�ж��Ƿ�Ϊtags
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
	while (L.removeFirst(list))
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
void init(CharString keyWords, AVLTree &tree, HashTable & hash, HashTable & movehash)
{
	StringList L, sum;
	CharString rubbish;
	HashTable removehash(10), authorhash(2);
	//��ϣ���ʼ��
	initDictionary("dic\\�ʿ�.dic", hash);//
	initDictionary("dic\\remove.dic", removehash);//ȥ��ת���ַ�
	initDictionary("dic\\author.dic", authorhash);//ȥ�����߶���
	initDictionary("dic\\move.dic", movehash);//�ִ�ʱȥ�������뵥��

	CharString removeList[MAINMAXREMOVE];
	CharString replaceList[MAINMAXREMOVE];
	fstream fremove("dic\\remove.dic", ios::in || ios::out);
	int i = 0;
	while (fremove >> removeList[i])
		i++;
	i = 0;
	fstream freplace("dic\\replace.dic", ios::in || ios::out);
	while (freplace >> replaceList[i])
		i++;

	char * filePath = "input";
	vector<string> files;
	for (int i = keyWords.Length() - 1; i >= 0; --i)
	{
		if (keyWords[i] == '\\')
		{
			keyWords = keyWords.subString(0, i);
			break;
		}
	}
	string c = "dir " + string(keyWords.tocstr()) + "\\input /B > file.txt";
	system(c.c_str());
	fstream fin("file.txt", fstream::in);
	char str[500];
	while (fin.getline(str, 500))
	{
		c = "input\\" + string(str);
		files.push_back(c);
	}
	

	int size = (int)files.size();
	int  authorLine = 0;
	for (int i = 0; i < size; i++)
	{
		cout << files[i].substr(6, files[i].length() - 11) << endl;
		extractInfo(files[i], L, removehash, authorhash, removeList, replaceList, MAINMAXREMOVE, authorLine);//���ļ�������Ϣ��ȡ��������浽L��
		for (int j = 0; j < authorLine; j++)//������������Ϣ����֮ǰ������ȫ��ȥ��
			L.removeFirst(rubbish);
		divideWords(L, hash, sum, movehash);//���зִʲ�����������浽sum�С�
		while (sum.removeFirst(rubbish))
		{
			int k = i + 1;
			tree.Insert(tree.root,rubbish, k);//���ִʽ����ӵ�AVL����
		};
		while (L.removeFirst(rubbish));
	}
	fin.close();
	system("del file.txt");

}

void search(CharString & searchWords, docList & searchdoc, AVLTree &tree, 
	HashTable & hash, HashTable & movehash)
{
	StringList searchlist;//����Ķ���ؼ��� 
	StringList searchWord;//�ִʺ󵥸��ؼ���
	docList *docTemp;
	CharString searchTemp;
	searchlist.add(searchWords);
	divideWords(searchlist, hash, searchWord, movehash);//�ִ����

	while (searchWord.removeFirst(searchTemp))//��ÿһ���ؼ��ʽ�������
	{
		if (tree.Search(tree.root,searchTemp) != nullptr)
		{
			docTemp = tree.Search(tree.root,searchTemp)->docline;//�ҵ��ؼ��ʶ�Ӧ����
			searchdoc.merge(docTemp);//�����������ϲ�
		}
	}
	searchdoc.sort();//�������� ׼�����
}

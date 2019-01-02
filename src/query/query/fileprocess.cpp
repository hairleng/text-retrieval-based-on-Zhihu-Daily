#include "CharString.h"
#include "stack.h"
#include "StringList.h"
#include "fileprocess.h"
#include "hashtable.h"
#include <iostream>
#include <fstream>
using namespace std;
#define MAXLEN 9
#define MAXREMOVE 8//分词函数中的转义字符最大个数
#define MAINMAXREMOVE 12//init函数中替代数组个数

bool isTag(CharString &m)//判断是否为tags
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
	Stack list;//存放CharString
	CharString buffer, temp, m, templist, content;//temp为标签,templist为标签内容，m为暂量，content为所需要提取内容。
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
					buffer.indexof(">", buffer.indexof("<", pos) + 1) - buffer.indexof("<", pos) - 1);//找到每个标签内容
				pos = buffer.indexof(">", buffer.indexof("<", pos) + 1) + 1;//更新扫描位置
				if (templist.indexof(" ", 0) == -1)
				{
					temp = templist;//找到标签
				}
				else
				{
					temp = templist.subString(0, templist.indexof(" ", 0));//找到标签
				}
				if (isTag(temp))
				{
					if (templist.indexof("class=\"headline-title\"", 0) != -1 ||
						templist.indexof("class=\"question-title\"", 0) != -1 ||
						templist.indexof("class=\"author\"", 0) != -1 ||
						templist.indexof("class=\"content\"", 0) != -1)
					{
						//更改开始标签
						add = 1;
						titleadd = 1;
					}
					if (temp[0] == '/')//如果是结束标签
					{
						temp = temp.subString(1, temp.Length() - 1);
						list.pop(m);
						if (m[0] == '1')
						{
							add = 0;//结束读入
							m = m.subString(1, m.Length() - 1);
						}
						if (m.compare(temp) != 0)
							list.push(m);
					}
					else//如果是开始标签
					{
						if (add == 0)
							list.push(temp);
						else if (add == 1 && titleadd == 1)
						{
							CharString n("1");//特殊开始标志开始标为1
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
							//开始读取内容content
							if (buffer.indexof("<", pos) != -1)
								content = buffer.subString(pos, buffer.indexof("<", pos) - pos);
							else
								content = buffer.subString(pos, buffer.Length() - pos);
							if (!content.isEmpty())
							{
								L.add(content);//添加
								authornum++;//作者位置更新
							}
						}
				}
			}
		}
	}
	//去掉末尾广告
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
		hash.add(buffer);//存入哈希表
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
			//更新位置
			if (list[pos] > 0)//下一个字符不是中文
			{
				pos++;
				continue;
			}
			else
			{
				for (int i = MAXLEN; i > 0; i--)//最大截取
				{
					if (i == 1)
					{
						answer.add(list.subString(pos, 3));//单字输入
						pos += 3;
					}
					else//逐次判断
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
	//哈希表初始化
	initDictionary("dic\\词库.dic", hash);//
	initDictionary("dic\\remove.dic", removehash);//去掉转义字符
	initDictionary("dic\\author.dic", authorhash);//去掉作者逗号
	initDictionary("dic\\move.dic", movehash);//分词时去除符号与单字

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
		extractInfo(files[i], L, removehash, authorhash, removeList, replaceList, MAINMAXREMOVE, authorLine);//对文件进行信息提取，结果保存到L中
		for (int j = 0; j < authorLine; j++)//将包括作者信息在内之前的内容全部去掉
			L.removeFirst(rubbish);
		divideWords(L, hash, sum, movehash);//进行分词操作，结果保存到sum中。
		while (sum.removeFirst(rubbish))
		{
			int k = i + 1;
			tree.Insert(tree.root,rubbish, k);//将分词结果添加到AVL树中
		};
		while (L.removeFirst(rubbish));
	}
	fin.close();
	system("del file.txt");

}

void search(CharString & searchWords, docList & searchdoc, AVLTree &tree, 
	HashTable & hash, HashTable & movehash)
{
	StringList searchlist;//读入的多个关键词 
	StringList searchWord;//分词后单个关键词
	docList *docTemp;
	CharString searchTemp;
	searchlist.add(searchWords);
	divideWords(searchlist, hash, searchWord, movehash);//分词完毕

	while (searchWord.removeFirst(searchTemp))//对每一个关键词进行搜索
	{
		if (tree.Search(tree.root,searchTemp) != nullptr)
		{
			docTemp = tree.Search(tree.root,searchTemp)->docline;//找到关键词对应链表
			searchdoc.merge(docTemp);//搜索结果链表合并
		}
	}
	searchdoc.sort();//链表排序 准备输出
}

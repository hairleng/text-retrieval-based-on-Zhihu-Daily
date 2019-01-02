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
#define MAXREMOVE 8//分词函数中的转义字符最大个数
#define MAINMAXREMOVE 12//init函数中替代数组个数
bool isTag(CharString m)//判断是否为tag
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
	while (L.removeFirst(list))//读取每一行
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
void initHash(HashTable & hash, HashTable & movehash, HashTable & removehash, HashTable & authorhash, CharString *removeList, CharString *replaceList)
{
	initDictionary("dic\\词库.dic", hash);//
	initDictionary("dic\\remove.dic", removehash);//去掉转义字符
	initDictionary("dic\\author.dic", authorhash);//去掉作者逗号
	initDictionary("dic\\move.dic", movehash);//分词时去除符号与单字
												 //替换字符数组初始化
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
	StringList searchlist;//读入的多个关键词
	StringList searchWord; //分词后单个关键词
	docList *docTemp;//searchdoc为要输出文档链表
	CharString searchTemp;
	searchlist.add(searchline);
	divideWords(searchlist, hash, searchWord, movehash);
	while (searchWord.removeFirst(searchTemp))//对每一个关键词进行搜索
	{
		if (tree.Search(tree.root,searchTemp) != nullptr)
		{
			docTemp = tree.Search(tree.root,searchTemp)->docline;//找到关键词对应链表
			searchdoc.merge(docTemp);//链表合并
		}
	}
	searchdoc.sort();//链表排序
}
//打开对应文件搜索词进行标红处理后输入到sum中。
void makeInfo(const char *filename, StringList &sum, CharString &searchline, HashTable & hash, HashTable & movehash)
{
	fstream in(filename, ios::in);
	StringList wordlist, wordtemp;
	wordtemp.add(searchline);
	divideWords(wordtemp, hash, wordlist, movehash);//分出搜索词
	CharString buffer;
	int pos = 0;// pos为读入位置
	int isInput = 0;
	bool isDeleteA = false;
	bool isDeleteImg = false;
	while (in >> buffer)//读入每一行
	{
		if (buffer.indexof("class=\"view-more\"", 0) != -1)//去结尾广告
		{
			isInput = 1;
			break;
		}
		if (buffer.indexof("class=\"qr\"", 0) != -1)//去结尾广告
		{
			isInput = 2;
			break;
		}
		while (buffer.indexof("<a", 0) != -1 || buffer.indexof("</a", 0) != -1) //去链接
		{
			int beginapos = buffer.indexof("<a", 0);
			if (beginapos != -1)
				isDeleteA = true;//将删除链接信号打开
			if (isDeleteA == true)
			{
				int endapos = buffer.indexof("</a", 0);
				if (endapos != -1)//删除相应链接
				{
					isDeleteA = false;//关闭删除链接信号
					CharString concatTemp;
					if (beginapos != -1)//链接标志同行
					{
						concatTemp = buffer.subString(0, beginapos);
						buffer = concatTemp.concat(buffer.subString(buffer.indexof(">", endapos) + 1, buffer.Length() - buffer.indexof(">", endapos) - 1));
					}
					else//链接标志不同行
					{
						buffer = buffer.subString(buffer.indexof(">", endapos) + 1, buffer.Length() - buffer.indexof(">", endapos) - 1);
					}
				}
				else
					break;
			}
		}
		while (buffer.indexof("<img", 0) != -1)//去图片
		{
			int beginImgpos = buffer.indexof("<img", 0);
			if (beginImgpos != -1)
				isDeleteImg = true;//打开删除图片信号
			if (isDeleteImg == true)
			{
				int endImgpos;
				if (beginImgpos != -1)
					endImgpos = buffer.indexof(">", beginImgpos);
				else
					endImgpos = buffer.indexof(">", 0);
				if (endImgpos != -1)//删除相应图片
				{
					isDeleteImg = false;//关闭删除图片信号
					CharString concatTemp;
					if (beginImgpos != -1)//图片标志同行
					{
						concatTemp = buffer.subString(0, beginImgpos);
						buffer = concatTemp.concat(buffer.subString(endImgpos + 1, buffer.Length() - 1 - endImgpos));
					}
					else//图片标志不同行
					{
						buffer = concatTemp.concat(buffer.subString(endImgpos + 1, buffer.Length() - 1 - endImgpos));
					}
				}
				else
					break;

			}
		}
		if (isDeleteA == false && isDeleteImg == false)//执行读入操作
		{
			Node *p;
			p = wordlist.head->next;
			while (p != nullptr)//对每一个关键词进行标红
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
				sum.add(buffer);//读入sum
		}
	}
	if (isInput == 1)//补充结构
	{
		sum.add("</div>");
		sum.add("</div>");
		sum.add("</div>");
		sum.add("</body>");
		sum.add("</html>");
	}
	if (isInput == 2)//补充结构
	{
		sum.add("</div>");
		sum.add("</body>");
		sum.add("</html>");
	}
}



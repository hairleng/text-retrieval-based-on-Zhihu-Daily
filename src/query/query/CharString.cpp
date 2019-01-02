#include <iostream>
#include "CharString.h"
#include <string>
#define MAXSIZE 5000
using namespace std;

CharString::CharString(string str)//直接以字符串或者string初始化。
{
	length = str.length();
	head = new char[length + 1];
	for (int i = 0; i < length; i++)
		head[i] = str[i];
	head[length] = '\0';
}
CharString::CharString(char * str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	length = i;
	head = new char[length + 1];
	for (int i = 0; i < length; i++)
		head[i] = str[i];
	head[length] = '\0';
};
CharString::CharString(CharString &m)
{
	length = m.Length();
	head = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		head[i] = m[i];
	}
	head[length] = '\0';
}
CharString::CharString()
{
	head = new char[1];
	length = 0;
	head[length] = '\0';
}
CharString::CharString(int m)
{
	length = m;
	head = new char[length + 1];
	for (int i = 0; i < length; i++)
		head[i] = '\0';
	head[length] = '\0';
}
CharString::~CharString()
{
	delete[] head;
}
int CharString::Length()
{
	return length;
}
bool CharString::isEmpty()
{
	if (length == 0)
		return true;
	return false;
}
bool CharString::assign(int i, char m)
{
	if (i >= length || i < 0)
		return false;
	head[i] = m;
	return true;
}
int CharString::compare(CharString &m)//head小于m返回-1，等于返回0,大于时返回1
{
	int i = 0;
	while (i < length && i < m.Length())
	{
		if (head[i] < m[i])
			return -1;
		if (head[i] > m[i])
			return 1;
		i++;
	}
	if (i < length)
		return 1;
	if (i < m.Length())
		return -1;
	return 0;//相等时返回false
}
bool CharString::copy(CharString &m)//复制整个m，原值改变
{
	delete[] head;
	length = m.Length();
	head = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		head[i] = m[i];
	}
	head[length] = '\0';
	return true;
}
CharString CharString::concat(CharString &m)//返回head+m
{
	CharString temp(length + m.Length());
	int i = 0;
	while (i < length)
	{
		temp.assign(i, head[i]);
		i++;
	}
	while (i < length + m.Length())
	{
		temp.assign(i, m[i - length]);
		i++;
	}
	return temp;
}
CharString CharString::subString(int pos, int len)
{
	CharString temp(len);
	//访问的子串位置不合法
	if (pos < 0 || pos + len > length)
		return CharString();

	int i = 0;
	while (i < len)
	{
		temp.assign(i, head[pos + i]);
		i++;
	};
	return temp;
}
void getNext(CharString T, int *&next)
{
	int j = 0, k = -1, m = T.Length() - 1;
	next[0] = -1;
	while (j < m)
	{
		if (k == -1 || T[j] == T[k])
		{
			++j;
			++k;
			next[j] = k;
		}
		else
			k = next[k];
	}
}
int CharString::indexof(CharString CS, int pos)
{
	int len = CS.Length(), k = 0;
	int * next = new int[len];
	int * nextval = new int[len];
	getNext(CS, next);
	for (int i = 0; i < len; i++)
		nextval[i] = next[i];
	for (int j = 1; j < len; j++)
	{
		k = next[j];
		if (CS[j] == CS[k])
		{
			nextval[j] = nextval[k];
		}
	}
	int i = pos, j = 0;
	while (i < length && j < len)
	{
		if (j == -1 || head[i] == CS[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];
	}
	delete[] next;
	delete[] nextval;
	if (j >= len)
		return i - len;
	return -1;
}
char CharString::operator[] (int m)
{
	if (m < 0 || m >= length)
		return '\0';
	return head[m];
}
CharString& CharString::operator=(CharString &m)
{
	delete[] head;
	length = m.Length();
	head = new char[length + 1];
	for (int i = 0; i < length; i++)
		head[i] = m[i];
	head[length] = '\0';
	return *this;
}
CharString& CharString::operator=(string &m)
{
	delete[] head;
	length = m.length();
	head = new char[length + 1];
	for (int i = 0; i < length; i++)
		head[i] = m[i];
	head[length] = '\0';
	return *this;
}
bool CharString::operator>(CharString &m)
{
	if (compare(m) == 1)
		return true;
	else
		return false;
}
bool CharString::operator>=(CharString &m)
{
	if (compare(m) == -1)
		return false;
	return true;
}
bool CharString::operator<(CharString &m)
{
	if (compare(m) == -1)
		return true;
	return false;
}
bool CharString::operator<=(CharString &m)
{
	if (compare(m) == 1)
		return false;
	return true;
}
bool CharString::operator==(CharString &m)
{
	if (compare(m) == 0)
		return true;
	return false;
}
bool CharString::operator!=(CharString &m)
{
	if (compare(m) == 0)
		return false;
	return true;
}
std::ostream & operator << (std::ostream &out, CharString& str)
{
	for (int i = 0; i < str.Length(); i++)
		out << str[i];
	return out;
}
std::istream & operator >> (std::istream & in, CharString &str)
{
	/*string temp;
	in >> temp;*/
	char * buffer = new char[MAXSIZE];
	in.getline(buffer, MAXSIZE);
	str = string(buffer);
	delete[] buffer;
	return in;

}
unsigned int CharString::findNext(int & index, int& forward)
{
	if(index < 0 && index >= length)
		return 0;
	char first = head[index];
	if ((first >> 7 & 1) == 0)
	{
		index++;
		forward = 1;
		return first;
	}
	else if ((first >> 6 & 0x03) != 0x03)
	{
		return 0;
	}
	else if ((head[index + 1] >> 6 & 0x03) == 0x02)
	{
		int result = head[index + 1] & 0x3f;
		int byte = 2;
		while ((first << byte & 0x80) == 0x80)
		{
			result = (result << 6) | (head[index + byte] & 0x3f);
			byte++;
		}
		index += byte;
		result |= (first & ((0x01 << (7 - byte)) - 1)) << (6 * (byte - 1));
		forward = byte;
		return result;
	}
	else
		return 0;
}
const char * CharString::tocstr() const
{
	return head;
}

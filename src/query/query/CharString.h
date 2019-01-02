#ifndef _CHARSTRING_H
#define _CHARSTRING_H
#include <iostream>
#include <string>

#define MAXSIZE 5000
using namespace std;

class CharString
{
private:
	char* head;
	int length;
public:
	CharString(string str);
	CharString(char * str);
	CharString(CharString &m);
	CharString();
	CharString(int m);
	~CharString();
	int Length();
	bool isEmpty();
	bool assign(int i, char m);
	int compare(CharString &m);
	bool copy(CharString &m);
	CharString concat(CharString &m);
	CharString subString(int pos, int len);//posΪ�Ӵ������lenΪ�ִ��ĳ���
	int indexof(CharString T, int pos);//����ƥ���±꣬��ƥ���򷵻�-1.
	unsigned int findNext(int &index, int &forward);

	const char* tocstr() const;//����ת��ΪC�����ַ���
	//��������������
	char operator[] (int m);
	CharString& operator=(CharString &m);
	CharString& operator=(string &m);
	bool operator>(CharString &m);
	bool operator>=(CharString &m);
	bool operator<(CharString &m);
	bool operator<=(CharString &m);
	bool operator==(CharString &m);
	bool operator!=(CharString &m);
	friend std::ostream & operator << (std::ostream &out, CharString& str);
	friend std::istream & operator >> (std::istream & in, CharString &str);
	
};

#endif


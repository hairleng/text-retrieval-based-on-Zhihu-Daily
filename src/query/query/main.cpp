#include <iostream>
#include<fstream>
#include<ctime>
#include "AVLTree.h"
#include "hashtable.h"
#include "CharString.h"
#include "fileprocess.h"
#include "StringList.h"
#include <string>
#include <vector>
#include <io.h>
using namespace std;

int main(int argv, char * argc[])
{
	CharString keyWords = string(argc[0]);//¼üÈë´ýËÑË÷¹Ø¼ü´Ê
	CharString searchWords;
	AVLTree tree;
	HashTable hash, movehash(30);
	init(keyWords, tree, hash, movehash);
	fstream fin("query.txt", ios::in);
	fstream fout("result.txt", ios::out);
	while (fin >> searchWords)
	{
		docList searchdoc;
		search(searchWords, searchdoc, tree, hash, movehash);
		searchdoc.output(fout);//Á´±íÊä³ö
	}
	return 0;
}
#ifndef SEARCH_H
#define SEARCH_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QListWidget.h>
#include <string>
#include "ui_search.h"
#include "CharString.h"
#include "AVLTree.h"
#include "hashtable.h"
#include "docList.h"
#include "fileprocess.h"
#include <fstream>
#include <string>
#include "thread.h"
#include <QProgressBar>
#include <vector>
class Search : public QMainWindow
{
	Q_OBJECT

public:
	Search(CharString command, QWidget *parent = 0);
	Search(QWidget *parent = 0);
	~Search();
public:
	CharString m_command;
	CharString m_string;
	AVLTree tree;
	HashTable hash;
	HashTable movehash,authorhash,removehash;
	CharString *removeList;
	CharString *replaceList;
	docList searchdoc;//�������
	int fileNum;
	Thread *m_thread;
	vector<string> files;//�ļ�����
	QProgressBar* m_progressBar;//������
private:
	Ui::searchClass ui;
	void readfile();
public slots:
	void receive();
	void progressBarChange(const int num);//������
public slots:
	void contentChange(QListWidgetItem *item);//��ʾ����ĳ���ļ�
};

#endif // SEARCH_H

#pragma once
#include <QThread>
#include <QtWidgets/QMainWindow>
#include "fileprocess.h"
#include "CharString.h"
#include "StringList.h"

class Search;
class Thread : public QThread//�߳���
{
	Q_OBJECT
public:
	Thread(Search *parent = 0);
	~Thread();
protected:
	void run();//��ʼ��������ʱʹ�ô��߳�
	Search *m_parent;
signals:
	void finished(const int num);//ÿ���һ���ļ�����һ���ź�	
};
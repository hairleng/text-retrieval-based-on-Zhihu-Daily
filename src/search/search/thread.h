#pragma once
#include <QThread>
#include <QtWidgets/QMainWindow>
#include "fileprocess.h"
#include "CharString.h"
#include "StringList.h"

class Search;
class Thread : public QThread//线程类
{
	Q_OBJECT
public:
	Thread(Search *parent = 0);
	~Thread();
protected:
	void run();//初始化构造树时使用次线程
	Search *m_parent;
signals:
	void finished(const int num);//每完成一个文件发出一个信号	
};
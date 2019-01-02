#include "search.h"
#include <qlayout.h>
#define MAINMAXREMOVE 12
Search::Search(CharString command, QWidget *parent)
	: QMainWindow(parent), m_command(command), authorhash(2), movehash(30), removehash(10)
{
	replaceList = new CharString[MAINMAXREMOVE];
	removeList = new CharString[MAINMAXREMOVE];
	initHash(hash, movehash, removehash, authorhash, removeList, replaceList);//初始化将会用到的各哈希表 数组
	readfile();//读入文件
	m_thread = new Thread(this);//开始线程
	m_thread->start();
	resize(400, 50);
	QWidget * centralWidget = new QWidget(this);//创造进度条
	QVBoxLayout * hBox = new QVBoxLayout(centralWidget);
	m_progressBar = new QProgressBar();
	m_progressBar->setMinimum(0);
	m_progressBar->setMaximum(fileNum);
	m_progressBar->setAlignment(Qt::AlignHCenter);
	m_progressBar->setValue(0);
	hBox->addWidget(m_progressBar);
	setCentralWidget(centralWidget);				
	connect(m_thread, SIGNAL(finished(const int)), this, SLOT(progressBarChange(const int)));
};
Search::Search(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
};
void Search::receive()
{
	QString text = ui.lineEdit->text();
	m_string = text.toStdString();
	searchdoc.clear();//清空原有内容
	searchAll(m_string, searchdoc, tree, hash, movehash);//进行搜索
	docNode *p;
	p = searchdoc.head;
	ui.listWidget->clear();//清空原有内容
	while (p != nullptr)//将搜索结果输出
	{
		ui.listWidget->addItem(QString::number(p->docID));
		p = p->next;
	}
	show();
};

Search::~Search()
{
	delete[] replaceList;
	delete[] removeList;
}

void Search::readfile()
{
	char * filePath = "input";
	for (int i = m_command.Length() - 1; i >= 0; --i)
	{
		if (m_command[i] == '\\')
		{
			m_command = m_command.subString(0, i);
			break;
		}
	}
	string c = "dir " + string(m_command.tocstr()) + "\\input /B > file.txt";
	system(c.c_str());
	fstream fin("file.txt", fstream::in);
	char str[500];
	while (fin.getline(str, 500))
	{
		c = "input\\" + string(str);
		files.push_back(c);
	}
	fin.close();
	system("del file.txt");
	fileNum = (int)files.size();
}

void Search::progressBarChange(const int num)//进度条响应
{
	if (num == -1)//进度完成
	{
		delete m_progressBar;
		ui.setupUi(this);
		connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(receive()));
		connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(contentChange(QListWidgetItem *)));
		show();
	}
	else
		m_progressBar->setValue(num);//进度更新
}

void Search::contentChange(QListWidgetItem * item)
{
	QString text = item->text();
	int docID = text.toInt();
	CharString m = "input//", temp;
	char numChar[2];
	numChar[1] = '\0';
	numChar[0] = docID / 1000 + '0';
	m = m.concat(CharString(numChar));
	numChar[0] = docID / 100 % 10 + '0';
	m = m.concat(CharString(numChar));
	numChar[0] = docID / 10 % 10 + '0';
	m = m.concat(CharString(numChar));
	numChar[0] = docID % 10 + '0';
	m = m.concat(CharString(numChar));
	m = m.concat(CharString(".html"));
	ui.textBrowser->clear();//清除原有文字
	StringList sum;
	makeInfo(m.tocstr(), sum, m_string, hash, movehash);//处理文档内容
	string str;
	while (sum.removeFirst(temp))
		str += string(temp.tocstr());
	ui.textBrowser->setText(QString::fromStdString(str));//输出
	show();
}

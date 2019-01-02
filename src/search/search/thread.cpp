#include "thread.h"
#include "search.h"
#define MAINMAXREMOVE 12//init函数中替代数组个数
Thread::Thread(Search * parent)
	:QThread(parent)
{
	m_parent = parent;
}
Thread::~Thread()
{
}
void Thread::run()
{
	//对每一个文件进行操作。
	int size = (int)m_parent->files.size();
	int  authorLine = 0;
	StringList L, sum;
	CharString rubbish;
	for (int i = 0; i < size; i++)
	{
		extractInfo(m_parent->files[i], L, m_parent->removehash, m_parent->authorhash, m_parent->removeList, m_parent->replaceList, MAINMAXREMOVE, authorLine);//对文件进行信息提取，结果保存到L中
		for (int j = 0; j < authorLine; j++)//将包括作者信息在内之前的内容全部去掉
			L.removeFirst(rubbish);
		divideWords(L, m_parent->hash, sum, m_parent->movehash);//进行分词操作，结果保存到sum中。
		while (sum.removeFirst(rubbish))
		{
			int k = i + 1;
			m_parent->tree.Insert(m_parent->tree.root,rubbish, k);//将分词结果添加到AVL树中
		};
		while (L.removeFirst(rubbish));
		emit finished(i + 1);//发出文件完成信号
	}
	emit finished(-1);//发出结束信号
}

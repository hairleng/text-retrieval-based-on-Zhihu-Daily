#include "thread.h"
#include "search.h"
#define MAINMAXREMOVE 12//init����������������
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
	//��ÿһ���ļ����в�����
	int size = (int)m_parent->files.size();
	int  authorLine = 0;
	StringList L, sum;
	CharString rubbish;
	for (int i = 0; i < size; i++)
	{
		extractInfo(m_parent->files[i], L, m_parent->removehash, m_parent->authorhash, m_parent->removeList, m_parent->replaceList, MAINMAXREMOVE, authorLine);//���ļ�������Ϣ��ȡ��������浽L��
		for (int j = 0; j < authorLine; j++)//������������Ϣ����֮ǰ������ȫ��ȥ��
			L.removeFirst(rubbish);
		divideWords(L, m_parent->hash, sum, m_parent->movehash);//���зִʲ�����������浽sum�С�
		while (sum.removeFirst(rubbish))
		{
			int k = i + 1;
			m_parent->tree.Insert(m_parent->tree.root,rubbish, k);//���ִʽ����ӵ�AVL����
		};
		while (L.removeFirst(rubbish));
		emit finished(i + 1);//�����ļ�����ź�
	}
	emit finished(-1);//���������ź�
}

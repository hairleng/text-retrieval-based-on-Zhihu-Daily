#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <iostream>
#include <string>
#include "CharString.h"
#include "docList.h"
using namespace std;

class TreeNode
{
public:
	TreeNode();
	~TreeNode() {};
	CharString word;
	int DF;//���ֵ�������
	int height;//���ĸ߶�
	int Occur;//�ܹ����ֵĸ���
	docList *docline;//�ĵ�����ָ��
	TreeNode *lchild;
	TreeNode *rchild;
};
class AVLTree
{
public:
	TreeNode * root;
	void Insert(TreeNode *&node, CharString &x, int &doc); //����
	TreeNode * Search(TreeNode* node, CharString &x);//����
	void Remove(TreeNode* &node, CharString &x);//�Ƴ�
	int height(TreeNode* node);
	int max(int a, int b);
	//Adjust������ת����ƽ����
	void LL_Adujust(TreeNode * &node1); //LL����
	void RR_Adujust(TreeNode * &node2); //RR����
	void LR_Adujust(TreeNode * &node3); //LR˫��
	void RL_Adujust(TreeNode * &node4); //RL˫��

	void Delete(TreeNode *&root);

	AVLTree();
	~AVLTree();
};

#endif
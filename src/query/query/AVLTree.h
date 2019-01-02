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
	int DF;//出现的文章数
	int height;//树的高度
	int Occur;//总共出现的个数
	docList *docline;//文档链表指针
	TreeNode *lchild;
	TreeNode *rchild;
};
class AVLTree
{
public:
	TreeNode * root;
	void Insert(TreeNode *&node, CharString &x, int &doc); //插入
	TreeNode * Search(TreeNode* node, CharString &x);//查找
	void Remove(TreeNode* &node, CharString &x);//移除
	int height(TreeNode* node);
	int max(int a, int b);
	//Adjust（）旋转试树平衡树
	void LL_Adujust(TreeNode * &node1); //LL单旋
	void RR_Adujust(TreeNode * &node2); //RR单旋
	void LR_Adujust(TreeNode * &node3); //LR双旋
	void RL_Adujust(TreeNode * &node4); //RL双旋

	void Delete(TreeNode *&root);

	AVLTree();
	~AVLTree();
};

#endif
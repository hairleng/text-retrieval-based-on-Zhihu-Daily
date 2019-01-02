#include <iostream>
#include <string>
#include "CharString.h"
#include "docList.h"
#include "AVLTree.h"
using namespace std;

TreeNode::TreeNode()
{
	lchild =rchild = nullptr;
	Occur = 1;
	height = 0;
	DF = 1;
}

void AVLTree::Insert(TreeNode *&node, CharString &x, int &doc)
{
	if (node == nullptr)
	{
		node = new TreeNode;
		node->docline = new docList;
		node->docline->Add(doc);
		node->word = x;
		return;
	}
	if (node->word > x)//x小于节点值，插入左子树
	{
		Insert(node->lchild, x, doc);
		if ((height(node->lchild) - height(node->rchild)) == 2)
		{
			if (x < node->lchild->word)
				LL_Adujust(node);
			else
				LR_Adujust(node);
		}
	}
	else if (node->word < x)//x大于节点值，插入右子树
	{
		Insert(node->rchild, x, doc);
		if ((height(node->rchild) - height(node->lchild)) == 2)
		{
			if (x < node->rchild->word)
			{
				RL_Adujust(node);
			}
			else
				RR_Adujust(node);
		}
	}
	else
	{
		if (node->docline->Search(doc) != nullptr)//文档已存在
		{
			node->docline->Add(doc);
		}
		else//文档不存在
		{
			node->DF++;//文档数加一
			node->docline->Add(doc);
		}
		node->Occur++;//单词出现加一
	}
	node->height = max(height(node->lchild), height(node->rchild)) + 1;
}

TreeNode * AVLTree::Search(TreeNode* node, CharString &x)
{
	if (node == nullptr)
		return nullptr;
	if (node->word > x)//当前节点比x小 向左继续搜
		return Search(node->lchild, x);
	else if (node->word < x)//当前节点比x小 向左继续搜
		return Search(node->rchild, x);
	else
		return node;
}

void AVLTree::Remove(TreeNode* &node, CharString &x)
{
	if (node == nullptr)//没有找到值为x的节点
		return;
	if (x < node->word)//x小于节点值，在左子树寻找删除
	{
		Remove(node->lchild, x);
		if ((height(node->rchild) - height(node->lchild)) == 2)
		{
			if (node->rchild->lchild != nullptr &&
				(height(node->rchild->lchild) > height(node->rchild->rchild)))
				RL_Adujust(node);
			else
				RR_Adujust(node);
		}
	}
	else if (x > node->word)//x大于节点值，在右子树寻找删除
	{
		Remove(node->rchild, x);
		if ((height(node->lchild) - height(node->rchild)) == 2)
		{
			if (node->lchild->rchild != nullptr
				&& (height(node->lchild->rchild) > height(node->lchild->lchild)))
				LR_Adujust(node);
			else
				LL_Adujust(node);
		}
	}
	else//相等
	{
		if (node->lchild && node->rchild)//节点两个儿子
		{
			TreeNode* temp = node->lchild;
			while (temp->rchild != nullptr)//找到rchild的尽头
				temp = temp->rchild;
			node->word = temp->word;
			node->Occur = temp->Occur;
			Remove(node->lchild, temp->word);

		if ((height(node->lchild) - height(node->rchild)) == 2)
			{
				if (node->lchild->rchild != nullptr
					&& (height(node->lchild->rchild) > height(node->lchild->lchild)))
					LR_Adujust(node);
				else
					LL_Adujust(node);
			}
		}
		else//有一个儿子或者没有儿子
		{
			TreeNode* temp = node;
			if (node->lchild == nullptr)
				node = node->rchild;
			else if (node->rchild == nullptr)
				node = node->lchild;
			delete(temp);
			temp = nullptr;
		}
	}
	if (node == nullptr) return;
	node->height = max(height(node->lchild), height(node->rchild)) + 1;
	return;
}

int AVLTree::height(TreeNode* node)
{
	if (node != nullptr)
		return node->height;
	else
		return -1;
}
	
int AVLTree::max(int a, int b)
{
	if (a > b)
		return a;
	else return b;
}

void AVLTree::LL_Adujust(TreeNode * &node1)
{
	TreeNode * node;
	node = node1->lchild;
	node1->lchild = node->rchild;
	node->rchild = node1;

	node1->height = max(height(node1->lchild), height(node1->rchild)) + 1;
	node->height = max(height(node->lchild), node1->height) + 1;
	node1 = node;
}

void AVLTree::RR_Adujust(TreeNode * &node2)
{
	TreeNode * node;
	node = node2->rchild;
	node2->rchild = node->lchild;
	node->lchild = node2;
	node2->height = max(height(node2->lchild), height(node2->rchild)) + 1;
	node->height = max(height(node->rchild), node2->height) + 1;
	node2 = node;
};

void AVLTree::LR_Adujust(TreeNode * &node3)
{
	RR_Adujust(node3->lchild);
	LL_Adujust(node3);
}

void AVLTree::RL_Adujust(TreeNode * &node4)
{
	LL_Adujust(node4->rchild);
	RR_Adujust(node4);
}

void AVLTree::Delete(TreeNode *&root)
{
	if (root != nullptr)
	{
		Delete(root->lchild);
		Delete(root->rchild);
		delete root;
		root = nullptr;
	}
}



AVLTree::AVLTree()
{
	root = nullptr;
}
AVLTree::~AVLTree()
{
	Delete(root);
}

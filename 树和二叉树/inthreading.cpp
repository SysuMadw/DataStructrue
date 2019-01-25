/*************************************************************************
    > File Name: inthreading.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月25日 星期五 19时23分43秒
 ************************************************************************/

# include <iostream>
using namespace std;

class TreeNode {
	public:
		int val;
		TreeNode* left;
		TreeNode* right;
		int ltag;
		int rtag;
		TreeNode(int x) : val(x), left(NULL), right(NULL), ltag(0), rtag(0) {}
};

// TreeNode* pre = NULL;
void inthreading(TreeNode* root){
	if (root == NULL)
		return;
	inthreading(root->left);
	if (root->left == NULL){
		ltag = 1;
		root->left = pre;
	}
	if (pre!=NULL && pre->right==NULL){
		pre->rtag = 1;
		pre->right = root;
	}
	pre = root;
	inthreading(root->right);
}
// pre->rtag = 1

//中序线索树寻找节点的前驱
TreeNode* prior(TreeNode* node){
	if (node->ltag == 1)
		return node->left;
	TreeNode* temp = node->left;
	while (temp->right != NULL)
		temp = temp->right;
	return temp;
}

//中序线索树寻找节点的后继
TreeNode* next(TreeNode* node){
	if (node->rtag == 1)
		return node->right;
	TreeNode* temp = noed->right;
	while (temp->left != NULL)
		temp = temp->left;
	return temp;
}


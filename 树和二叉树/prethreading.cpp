/*************************************************************************
    > File Name: prethreading.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月25日 星期五 19时48分37秒
 ************************************************************************/

# include <iostream>
using namespace std;

class TreeNode {
	public:
		int val;
		int ltag;
		int rtag;
		TreeNode* left;
		TreeNode* right;
		TreeNode* parent;
		TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL), ltag(0), rtag(0) {}
};

// TreeNode* pre = NULL;
void prethreading(TreeNode* root){
	if (root == NULL)
		return;
	if (root->left == NULL){
		root->ltag = 1;
		root->left = pre;
	}
	if (pre!=NULL && pre->right==NULL){
		pre->rtag = 1;
		pre->right = root;
	}
	pre = root;
	prethreading(root->left);
	prethreading(root->right);
}
// pre->rtag = 1;

TreeNode* prior(TreeNode* node){
	if (node->ltag == 1)
		return node->left;
	return node->parent;
}

TreeNode* next(TreeNode* node){
	if (node->rtag == 1)
		return node->right;
	return node->ltag==1? node->right : node->left;
}


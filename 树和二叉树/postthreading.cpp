/*************************************************************************
    > File Name: postthreading.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月25日 星期五 19时57分00秒
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
void postthreading(TreeNode* root){
	if (root == NULL)
		return;
	postthreading(root->left);
	postthreading(root->right);
	if (root->left == NULL){
		root->ltag = 1;
		root->left = pre;
	}
	if (pre!=NULL && pre->right==NULL){
		pre->rtag = 1;
		pre->right = root;
	}
	pre = root;
}
// pre->rtag = pre->right == NULL ? 1 : 0;

TreeNode* prior(TreeNode* node){
	if (node->ltag == 1)
		return node->left;
	return node->rtag==0? node->right : node->left;
}

TreeNode* next(TreeNode* node){
	if (node->rtag == 1)
		return node->right;
	if (node->parent == NULL)
		return NULL;
	TreeNode* parent = node->parent;
	if (parent->right==node || (parent->rtag==1 && parent->left==node))
		return parent;
	else {
		TreeNode* temp = parent->right;
		while (temp->ltag != 1)
			temp = temp->left;
		return temp;
	}
}

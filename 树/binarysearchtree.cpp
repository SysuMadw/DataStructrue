/*************************************************************************
    > File Name: binarysearchtree.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月26日 星期六 20时50分33秒
 ************************************************************************/

# include <iostream>

using namespace std;

class TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void insert(TreeNode*& root, int val){
	if (root == NULL)
		root = new TreeNode(val);
	else if (val < root->val)
		insert(root->left,val);
	else
		insert(root->right,val);
}

TreeNode* deletenode(TreeNode* root, int val){
	if (root == NULL)
		return NULL;
	if (val < root->val)
		root->left = deletenode(root->left,val);
	else if (val == root->val){
		if (root->left==NULL && root->right==NULL){
			delete root;
			return NULL;
		}
		else if (root->left == NULL){
			TreeNode* temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == NULL){
			TreeNode* temp = root->left;
			delete root;
			return emp;
		}
		else {
			TreeNode* temp = root->left, pre = root;
			while (temp->right != NULL)
				pre = temp, temp = temp->right;
			root->val = temp->val;
			pre->right = NULL;
			delete temp;
			return root;
		}
	}
	else
		root->right = deletenode(root->right,val);
	return root;
}

TreeNode* createtree(vector<int> ans){
	TreeNode* root = NULL;
	for (int i=0; i<ans.size(); i++)
		insert(root,ans[i]);
	return root;
}

TreeNode* search(TreeNode* root, int val){
	if (root == NULL)
		return NULL;
	else if (root->val == val)
		return root;
	else if (val < root->val)
		return search(root->left,val);
	else
		return search(root->right,val);
}


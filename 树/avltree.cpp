# include <iostream>
# include <algorithm>

using namespace std;

class TreeNode {
public:
	int val;
	int height;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), height(1), left(NULL), right(NULL) {}
};

int height(TreeNode* root){
	return root==NULL? 0 : root->height;
}

TreeNode* RR(TreeNode* root){
	TreeNode* temp = root->right;
	root->right = temp->left;
	temp->left = root;
	
	temp->left->height = max(height(temp->left->left),height(temp->left->right)) + 1;
	temp->height = max(height(temp->left),height(temp->right)) + 1;
	return temp;
}

TreeNode* LL(TreeNode* root){
	TreeNode* temp = root->left;
	root->left = temp->right;
	temp->right = root;
	
	temp->right->height = max(height(temp->right->left),height(temp->right->right)) + 1;
	temp->height = max(height(temp->left),height(temp->right)) + 1;
	return temp;
}

TreeNode* LR(TreeNode* root){
	root->left = RR(root->left);
	return LL(root);
}

TreeNode* RL(TreeNode* root){
	root->right = LL(root->right);
	return RR(root);
}

int balance(TreeNode* root){
	int left = root->left==NULL? 0 : root->left->height;
	int right = root->right==NULL? 0 : root->right->height;
	return left - right;
}

void insert(TreeNode*& root, int val){
	if (root == NULL)
		root = new TreeNode(val);
	else if (val < root->val){
		insert(root->left,val);
		if (balance(root) == 2){
			if (height(root->left->left) > height(root->left->right))
				root = LL(root);
			else
				root = LR(root);
		}
	}
	else {
		insert(root->right,val);
		if (balance(root) == -2){
			if (height(root->right->left) > height(root->right->right))
				root = RL(root);
			else
				root = RR(root);
		}
	}
	root->height = max(height(root->left),height(root->right)) + 1;
}

void deletenode(TreeNode*& root, int val){
	if (root == NULL)
		return;
	if (root->val == val){
		if (root->left==NULL && root->right==NULL){
			delete root;
			root = NULL;
		}
		else if (root->left!=NULL && root->right!=NULL){
			if (height(root->left) > height(root->right)){
				TreeNode* node = root->left;
				while (node->right != NULL)
					node = node->right;
				root->val = node->val;
				deletenode(root->left,node->val);
			}
			else {
				TreeNode* node = root->right;
				while (node->left != NULL)
					node = node->left;
				root->val = node->val;
				deletenode(root->right,node->val);
			}
		}
		else {
			TreeNode* left = root->left, *right = root->right;
			delete root;
			root = left==NULL? right : left;
		}
	}
	else if (root->val < val){
		deletenode(root->left,val);
		root->height = max(height(root->left),height(root->right)) + 1;
		if (balance(root) == -2){
			if (height(root->right->left) > height(root->right->right))
				root = RL(root);
			else
				root = RR(root);
		}
	}
	else{
		deletenode(root->right,val);
		root->height = max(height(root->left),height(root->right)) + 1;
		if (balance(root) == 2){
			if (height(root->left->left) > height(root->left->right))
				root = LL(root);
			else
				root = LR(root);
		}
	}
}

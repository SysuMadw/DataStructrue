/*************************************************************************
    > File Name: B+tree.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月28日 星期一 22时32分44秒
 ************************************************************************/
/*
 *  红黑树特性: --二叉查找树
 *	1 每个节点或者是黑色，或者是红色
 *  2 根节点是黑色
 *  3 每个叶子节点都是黑色，这里的叶子节点指的是NIL节点
 *  4 如果一个节点是红色的，那么它的子节点必须是黑色的
 *  5 对每一个节点，从该节点到其所有后代叶子节点的简单路径上，包含相同数目的黑色节点
 */

# include<iostream>

using namespace std;

class TreeNode {
	public:
		char color;
		int val;
		TreeNode* left, *right, *parent;
		TreeNode(int x) : val(x), color('r'), left(NULL), right(NULL), parent(NULL) {}
};

TreeNode* RR(TreeNode* root){
	TreeNode* temp = root->right;
	temp->parent = root->parent;
	root->right = temp->left;
	if (temp->left != NULL)
		temp->left->parent = root;
	if (root->parent != NULL){
		if (root == root->parent->left)
			root->parent->left = temp;
		else
			root->parent->right = temp;
	}
	root->parent = temp;
	temp->left = root;
	return temp;
}

TreeNode* LL(TreeNode* root){
	TreeNode* temp = root->left;
	temp->parent = root->parent;
	root->left = temp->right;
	if (temp->right != NULL)
		temp->right->parent = root;
	if (root->parent != NULL){
		if (root == root->parent->left)
			root->parent->left = temp;
		else 
			root->parent->right = temp;
	}
	temp->right = root;
	root->parent = temp;
	return temp;
}

void RB_insert_fixup(TreeNode*& root, TreeNode* newnode){
	if (newnode == root)
		newnode->color = 'b';
	else if (newnode->parent->color == 'b')
		return;
	else {
		while (newnode->parent!=NULL && newnode->parent->color == 'r'){
			if (newnode->parent == node->parent->parent->left){
				TreeNode* right = node->parent->parent->right;
				if (right->color == 'r'){
					//case 1 -- 插入节点的父节点红色，父亲节点的兄弟节点也是红色
					newnode->parent->color = 'b';
					right->color = 'b';
					newnode->parent->parent->color = 'r';
					newnode = newnode->parent->parent;
				}
				else {	//叔叔节点是黑色
					if (newnode->parent->right == newnode)	{
						//case 2 插入节点是父节点的右孩子 
						//将父节点作为新的当前节点
						//以新的当前节点为支点进行左旋
						newnode = newnode->parent;
						RR(newnode);
					}
					else {
						//case 3 插入节点是父节点的左孩子
						//将父节点设为黑色，祖父节点设为红色，以祖父节点为支点进行右旋
						newnode->parent->color = 'b';
						newnode->parent->parent = 'r';
						TreeNode* temp = LL(newnode->parent->parent);
						if (temp->parent == NULL)
							root = temp;
					}
				}
			}
			else{
				TreeNode* left = node->parent->parent->left;
				if (left->color == 'r'){
					//case 1
					newnode->parent->color = 'b';
					left->color = 'b';
					newnode->parent->parent->color = 'r';
					newnode = newnode->parent->parent;
				}
				else {
					if (newnode->parent->left == newnode){
						//case 2 
						newnode = newnode->parent;
						RR(newnode);
					}
					else {
						//case 3
						newnode->parent->color = 'b';
						newnode->parent->parent->color = 'r';
						TreeNode* temp = LL(newnode->parent->parent);
						if (temp->parent == NULL)
							root = temp;
					}
				}
			}
		}
		root->color = 'b';
	}
}

void insert(TreeNode*& root, int val){
	TreeNode* node = NULL, *temp = root;
	while (temp != NULL){
		node = temp;
		if (val < temp->val)
			temp = temp->left;
		else if (val == temp->val)
			return;
		else
			temp = temp->right;
	}

	TreeNode* newnode = new TreeNode(val);
	newnode->parent = node;
	if (node == NULL)
		root = newnode;
	else if (newnode->val < node->val)
		node->left = newnode;
	else
		node->right = newnode;
	RB_insert_fixup(root,newnode);
}

TreeNode* next(TreeNode* root){
	TreeNode* temp = root->right;
	while (temp->left != NULL)
		temp = temp->left;
	return temp;
}

bool isblack(TreeNode* root){
	return root==NULL || root->color=='b'? true : false;
}

bool isred(TreeNode* root){
	return !isblack(root);
}

void RB_delete_fixup(TreeNode*& root, TreeNode* parent, TreeNode* child){
	//在修复红黑树过程中，假设child节点包含额外的黑色(child节点原本的颜色依然存在)，这样就不会违反特性5
	TreeNode* bro = NULL;
	while (child!=root && (child==NULL || child->color=='b')){
		if (parent->left == child){
			bro = parent->right;
			if (bro->color == 'r'){
				//child是黑+黑节点，而它的兄弟节点是红色节点  -->case1
				//将child的兄弟节点设置为黑色，将child的父节点设置为红色，对child的父节点进行左旋，左旋后，重新设置child的兄弟节点	
				parent->color = 'r';
				bro->color = 'b';
				RR(parent);
				bro = parent->right;	//case1的目的是为了转成case2、case3或case4情况，以便后续处理
			}
			if (isblack(bro->left) && isblack(bro->right)){
				//child节点的兄弟节点是黑色节点，且兄弟节点的左右孩子都是黑色节点 -->case2
				//将child的兄弟节点设置为红色，并将child的父节点设置为当前父节点
				bro->color = 'r';
				child = parent;
				parent = child->parent;
			}
			else if (isblack(bro->right)){
				//child节点的兄弟节点是黑色节点，且兄弟节点的右孩子是黑色，左孩子是红色 -->case3
				//将child兄弟节点的左孩子设置为黑色，将child兄弟节点设置为红色，对child的兄弟节点进行右旋，右旋后,重新设置child的兄弟节点
				bro->left->color = 'b';
				bro->color = 'r';
				LL(bro);
				bro = parent->right;	//case3处理后变为case4情况，继续后续处理
			}
			else {
				//child节点的兄弟节点是黑色节点，且兄弟节点的右孩子是红色，左孩子颜色任意 -->case4
				//将父节点颜色赋给child的兄弟节点	，将child父节点设置为黑色，将child兄弟节点的右孩子设置为黑色，对child的父节点进行左旋，设置	child为根
				bro->color = parent->color;	
				parent->color = 'b';
				bro->right->color = 'b';
				RR(parent);
				child = root;	//经过case4处理，红黑树性质恢复
			}
		}
		else {
			//对称情况
			bro = parent->left;
			if (bro->color == 'r') {
				parent->color = 'r';
				bro->color = 'b';
				LL(parent);
				bro = parent->left;
			}
			if (isblack(bro->left) && isblack(bro->right)){
				bro->color = 'r';
				child = parent;
				parent = child->parent;
			}
			else if (isblack(bro->left)){
				bro->right->color = 'b';
				bro->color = 'r';
				RR(bro);
				bro = parent->left;	//case3处理后变为case4情况，继续后续处理
			}
			else {
				bro->color = parent->color;	
				parent->color = 'b';
				bro->left->color = 'b';
				LL(parent);
				child = root;	//经过case4处理，红黑树性质恢复
			}
		}
	}
	child->color = 'b';
}

void deletenode(TreeNode*& root, int val){
	
	TreeNode* node = root, *temp = NULL, *child = NULL;
	while (node != NULL){
		if (val == node->val)
			break;
		else if (val < node->val)
			node = node->left;
		else
			node = node->right;
	}

	if (node == NULL)	//无该节点
		return;
	if (node->left==NULL || node->right==NULL)
		temp = node;
	else
		temp = next(node);
	child = temp->left==NULL? temp->right : temp->left;
	if (child != NULL)
		child->parent = temp->parent;
	if (temp->parent == NULL)
		root = child;
	else if (temp->parent->left == temp)
		temp->parent->left = child;
	else
		temp->parent->right = child;

	if (temp != node)
		node->val = temp->val;
	
	if (temp->color == 'b')
		RB_delete_fixup(root,temp->parent,child);

	delete temp;
}



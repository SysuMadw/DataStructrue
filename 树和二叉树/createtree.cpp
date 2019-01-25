/*************************************************************************
    > File Name: createtree.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月25日 星期五 16时52分29秒
 ************************************************************************/

# include <iostream>
using namespace std;

class TreeNode {
	public:
		char val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(char x) : val(x), left(NULL), right(NULL) {}
};

class TreeNodeTriple {
	public:
		char val;
		TreeNodeTriple* left;
		TreeNodeTriple* right;
		TreeNodeTriple* parent;
		TreeNodeTriple(char x,TreeNodeTriple* parent) : val(X), left(NULL), right(NULL), parent(parent) {}
};

//根据树的先序遍历序列构造一颗二叉树，' '表示空树
//二叉链表
TreeNode* createtreeByPre(string& ans, int& i){
	if (i == ans.length() || ans[i]==' ')
		return NULL;
	TreeNode* root = new TreeNode(ans[i]);
	i = i + 1;
	root->left = createtreeByPre(ans,i);
	i = i + 1;
	root->right = createtreeBYPre(ans,i);
	return root;
}

//三叉链表
TreeNodeTriple* TripleCreatetreeByPre(string& ans, int& i, TreeNodeTriple* parent){
	if (i == ans.length() || ans[i] == ' ')
		return NULL;
	TreeNodeTriple* root = new TreeNodeTriple(ans[i],parent);
	i = i + 1;
	root->left = TripleCreatetreeByPre(ans,i,root);
	i = i + 1;
	root->right = TripleCreatetreeByPre(ans,i,root);
	return root;
}

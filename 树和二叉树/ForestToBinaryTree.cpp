/*************************************************************************
    > File Name: ForestToBinaryTree.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月25日 星期五 21时12分29秒
 ************************************************************************/

# include <iostream>
using namespace std;

class TreeNode {
	public:
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* ForestToBinaryTree(vector<TreeNode*> trees){
	if (nodes.size() == 0)
		return 0;
	for (int i=1; i<trees.size(); i++)
		(trees[i-1])->right = trees[i];
	return trees[0];
}

void BinaryTreeToForest(TreeNode* root, vector<TreeNode*> trees){
	if (root == NULL)
		return;
	TreeNode* temp = root->right;
	root->right = NULL;
	trees.push_back(root);
	BinaryTreeToForest(temp,trees);
}

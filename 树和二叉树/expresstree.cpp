/*************************************************************************
    > File Name: expresstree.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月25日 星期五 16时41分30秒
 ************************************************************************/

# include <iostream>
# include <stack>

using namespace std;

class TreeNode {
public:
	char val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(char x) : val(x) , left(NULL), right(NULL) {}
	TreeNode(char x, TreeNode* leftnode, TreeNode* rightnode) : val(x), left(leftnode),right(rightnode) {}
};

TreeNode* MakeExpressTreeByPost(string& ans){
	stack<TreeNode*> nodes;
	for (int i=0; i<ans.length(); i++)
		if (ans[i]!='+' && ans[i]!='-' && ans[i]!='*' && ans[i]!='/'){
			TreeNode* node = new TreeNode(ans[i]);
			nodes.push(node);
		}
		else {
			TreeNode* rightnode = nodes.top();	//右孩子
			nodes.pop();
			TreeNode* leftnode = nodes.top();	//左孩子
			nodes.pop();
			TreeNode* node = new TreeNode(ans[i],leftnode,rightnode);
			nodes.push(node);
		}
	return nodes.top();
}

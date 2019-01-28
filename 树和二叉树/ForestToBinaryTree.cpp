/*************************************************************************
    > File Name: ForestToBinaryTree.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月25日 星期五 21时12分29秒
 ************************************************************************/

# include <iostream>

using namespace std;

/*
	思路：u的孩子节点为v1,v2,v3.... (v1,v2,....互为兄弟节点)
	那么将u的一个孩子节点(v1)连在u的左子树上，其他孩子节点都连在v1的右子树上*/

# include <cstring>
# define nodes 15
int E[nodes][nodes];
int P[nodes];
int V[nodes];

class TreeNode {
	int val;
	TreeNode* leftchild;
	TreeNode* rightchild;
	TreeNode(int x) : val(x), leftchild(NULL), rightchild(NULL) {}
};

//以i为根的树转换为二叉树
int n = 0, m = 0;
void bulidTree(TreeNode*& root, int i){
	bool flag = false;
	root = new TreeNode(i);
	TreeNode* cur = root;
	V[i] = 1;

	for (int v=1; v<=n; v++)
		if (E[i][v] == 1){
			if (flag == false){
				buildTree(cur->leftchild,v);
				cur = cur->leftchild;
				flag = true;
			}
			else {
				buildTree(cur->rightchild,v);
				cur = cur->rightchild;
			}
		}
}
//将森林转换为二叉树
int main(void){
	TreeNode* root = NULL, cur = NULL;
	memset(E,0,sizeof(E));
	memset(P,0,sizeof(P));
	memset(V,0,sizeof(V));
	int  u = 0, v = 0;
	cin >> n >> m;
	while (m > 0){
		m--;
		cin >> u >> v;
		E[u][v] = 1;
		P[v] = u;
	}
	bool flag = false;
	for (int i=1; i<=n; i++){
		if (V[i] == false && P[i] == 0){
			if (flag == false){
				flag = true;
				buildTree(root,i);
				cur = root;
			}
			else {
				bulidTree(cur->rightchild,i);
				cur = cur->rightchild;
			}
		}
	}
}

//将二叉树还原为森林
int forest[nodes][nodes];
void rebuildMap(TreeNode* root, TreeNode* cur){
	if (root == NULL)
		return;
	if (cur != NULL)
		forest[cur->val][root->val] = 1;
	rebuildMap(root->leftchild,root);
	rebuildMap(root->rightchild,cur);	
}

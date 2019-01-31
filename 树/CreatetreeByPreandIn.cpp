/*************************************************************************
    > File Name: CreatetreeByPreandIn.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月26日 星期六 20时14分07秒
 ************************************************************************/

# include <iostream>
using namespace std;

class TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* createtree(vector<int>& pre, vector<int>& in){
	return createtree(pre,0,pre.size()-1,in,0,in.size()-1);
}

TreeNode* createtree2(vector<int>& in, vector<int>& post){
	return createtree2(in,0,in.size()-1,post,0,post.size()-1);
}

TreeNode* createtree2(vector<int>& in, int instart, int inend, vector<int>& post, int poststart, int postend){
	if (instart > inend)
		return NULL;
	int rootVal = post[postend], i = 0;
	for (i=instart; i<=inend; i++)
		if (in[i] == rootVal)
			break;
	int leftnum = i - instart;
	TreeNode* root = new TreeNode(rootVal);
	root->left = createtree2(in,instart,i-1,post,poststart,poststart+leftnum-1);
	root->right = createtree2(in,i+1,inend,post,poststart+leftnum,postend-1);
	return root;
}

TreeNode* createtree(vector<int>& pre, int prestart, int preend, vector<int>& in, int instart, int inend){
	if (prestart > preend)
		return NULL;
	int rootVal = pre[prestart], i = 0;
	for (i=instart; i<=inend; i++)
		if (in[i] == rootVal)
			break;
	int leftnum = i - instart;
	TreeNode* root = new TreeNode(rootVal);
	root->left = createtree(pre,prestart+1,prestart+leftnum,in,instart,i-1);
	root->right = createtree(pre,prestart+leftnum+1,preend,in,i+1,inend);
	return root;
}

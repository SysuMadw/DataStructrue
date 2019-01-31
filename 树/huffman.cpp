/*************************************************************************
    > File Name: huffman.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月26日 星期六 15时49分02秒
 ************************************************************************/

# include <iostream>
# include <cstring>

using namespace std;

class TreeNdoe {
	public:
		int weight;
		char data;
		char* parse;
		TreeNode* left, *right, *parent;
		TreeNode() : data('\0'), left(NULL), right(NULL), parent(NULL), parse(NULL) {}
};

int main(void){
	int leaf = 0, weight = 0;
	char data = '\0';

	//构造赫夫曼树
	cin >> leaf;
	TreeNode* nodes = new TreeNode[2 * leaf - 1];
	for (int i=0; i<leaf; i++){
		cin >> data >> weight;
		nodes[i].data = data;
		nodes[i].weight = weight;
	}

	for (int i=leaf; i<2*leaf-1; i++){
		int min1 = -1, index1 = -1, min2 = -1, index2 = -1;
		for(int j=0; j<i; j++){
			if (nodes[j].parent != NULL)
				continue;
			if (min1 == -1)
				min1 = nodes[j].weight, index1 = j;
			else if (min2 == -1)
				min2 = nodes[j].weight, index2 = j;
			else if (nodes[j].weight < min1)
				min2 = min1, index2 = index1, min1 = nodes[j].weight, index1 = j;
			else if (nodes[j].weight < min2)
				min2 = nodes[j].weight, index2 = j;
		}
		nodes[i].weight = min1 + min2;
		nodes[i].left = &nodes[index1];
		nodes[i].right = &nodes[index2];
		nodes[index1].parent = nodes[index2].parent = &nodes[i];
	}
	return 0;
}

//利用构造的赫夫曼树求解相应字符的赫夫曼编码
string parse(TreeNode* nodes, int leaf, char num){
	int k = 0;
	string ans = "";
	for (k=0; k<leaf; k++)
		if (nodes[k].data == num)
			break;
	for (TreeNode* parent=&nodes[k].parent, *child=&nodes[k]; parent!=NULL; child=parent,parent=parent->parent){
		if (parent->left == child)
			ans = '0' + ans;
		else
			ans = '1' + ans;
	}
	return ans;
}

//解析赫夫曼编码得到对应的字符
char parse(TreeNode* root, string ans){
	TreeNode* temp = root;
	for (int i=0; <ans.length(); i++)
		temp = ans[i]=='0'? temp->left : temp->right;
	return temp->data;
}

//无栈非递归遍历赫夫曼树，求取所有字符的赫夫曼编码
void parse(TreeNode* nodes, int leaf){
	int len = 0;
	char* map = new char[n+1];
	for (int i=0; i<2*leaf-1; i++)
		nodes[i].weight = 0;
	TreeNode* p = &nodes[2*leaf-2];
	while (p != NULL){
		if (p->weight == 0){	//向左
			p->weight = 1;
			if (p->left != NULL)
				p = p->left, map[len++] = '0';
			if (p->right == NULL){
				p->parse = new char[len+1];
				strcpy(p->parse,map);
				p->parse[len] = '/0';
			}
		}
		else if (p->weight == 1){	//向右
			p->weight = 2;
			if (p->right != NULL)
				p = p->right, map[len++] = '1';
		}
		else {
			p->weight = 0;
			p = p->parent;
			len--;
		}
	}
	return;
}

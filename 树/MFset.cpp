/*************************************************************************
    > File Name: MFset.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月26日 星期六 15时12分36秒
 ************************************************************************/

# include <iostream>
using namespace std;

struct node {
	int data;
	int parent;
};

//子集的合并
void MixMFset(node* nodes, int i, int j, int num){
	if (i<0 || i>=num || j<0 || j>=num)
		return;
	if (nodes[i].parent > nodes[j].parent){
		nodes[j].parent += nodes[i].parent;
		nodes[i].parent = j;
	}
	else {
		nodes[i].parent += nodes[j].parent;
		nodes[j].parent = i;
	}
}

//寻找元素对应的子集...
int FindMFset(node* nodes, int i, int num){
	if (i<0 || i>=n)
		return -1;
	int k = 0;
	for (k=i; nodes[k].parent>=0; k=nodes[k].parent);
	int t,j;
	for (j=i; j!=k; j = t)
		t = nodes[j].parent, nodes[j].parent = k;
	return k;
}


int main(void){
	int num = 0, m = 0;
	cin >> num >> m;
	node* point = new node[num];
	for (int i=0; i<num; i++)
		point[i].data = i, point[i].parent = -1;
	int x,y;
	for (int i=0; i<m; i++){
		cin >> x >> y;
		int rootx = FindMFSet(point,x,num);
		int rooty = FindMFset(point,y,num);
		if (rootx != rooty)
			MixMFset(point,rootx,rooty,num);
	}
	return 0;
}


/*************************************************************************
    > File Name: B-tree.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月27日 星期日 20时48分42秒
 ************************************************************************/

# include <iostream>
# define m 4

using namespace std;

/*
 *	一颗m阶的B-树，或为空树，或为满足下列特性的m叉树
 *  1 树中每个节点至多有m棵子树
 *  2 若根节点不是叶子节点，则至少有两棵子树
 *  3 除根之外的所有非终端节点至少有[m/2](向上取整)棵子树
 *  4 所有的非终端节点中包括如下的信息数据:(n,A0,K1,A1,K2,....,An)
 *  5 所有的叶子节点都出现在同一层次，并且不带信息，指向这些节点的指针为空
 */

class TreeNode {
	public:
		int keynum;			//节点中关键字的个数
		TreeNode* parent;	//指向双亲节点
		int	key[m+1];		//关键字向量，0号单元未用
		TreeNode* ptr[m+1];	//子树指针向量
		TreeNode() : keynum(0), parent(NULL) {
			for (int i=0; i<=m; i++){
				key[i] = 0;
				ptr[i] = NULL;
			}
		}
};

class BTree {
	public:
		BTree() : head(NULL) {}
		bool insert_BTree(int val);
		bool searchKey_BTree(int val, TreeNode*& node, int& index);
		bool delete_BTree(int val);
	private:
		int search(TreeNode*& node, int val);
		void insert(TreeNode*& t, int i, int val, TreeNode* node);
		void Delete(TreeNode* node, int index);
		void split(TreeNode*& t, int middle, TreeNode*& rhs, int& k);
		void newroot(TreeNode*& head, TreeNode*& lhs, int curk, TreeNode*& rhs);
		void DeleteBalance(TreeNode* node);
		void RotateLeft(TreeNode* parent, int index, TreeNode* cur, TreeNode* right);
		void RotateRight(TreeNode* parent, int index, TreeNode* cur, TreeNode* left);
		void merge(TreeNode* parent, int index,TreeNode* left, TreeNode* node);
		TreeNode* head;
};

void BTree::merge(TreeNode* parent, int index, TreeNode* left, TreeNode* cur){
	//将被删除关键字的剩余部分合并到相邻左节点
	for (int i=0; i<=cur->keynum; i++){
		left->key[left->keynum+1+i] = cur->key[i];
		left->ptr[left->keynum+1+i] = cur->ptr[i];
		if (left->ptr[left->keynum+1+i] != NULL)
			left->ptr[left->keynum+1+i]->parent =left;
	}
	//将父节点中index对应的内容添加到相邻左节点中
	left->key[left->keynum+1] = parent->key[index];
	//删除节点
	delete cur;
	//将父节点index之后的序列向前移动一个位置
	for (int i=index; i<=parent->keynum; i++){
		parent->key[i] = parent->key[i+1];
		parent->ptr[i] = parent->ptr[i+1];
	}
	parent->keynum--;
}

void BTree::RotateLeft(TreeNode* parent, int index, TreeNode* cur, TreeNode* right){
	cur->key[cur->keynum+1] = parent->key[index+1];	//此时将父节点中index+1位置的关键字下移到删除关键字的节点中
	cur->ptr[cur->keynum+1] = right->ptr[0];	
	if (cur->ptr[cur->keynum+1])
		cur->ptr[cur->keynum+1]->parent = cur;
	cur->keynum++;	

	//将右兄弟最小关键字上移到父亲节点
	parent->key[index+1] = right->key[1];
	//将右兄弟的关键字序列向前移动一个位置
	for (int i=0; i<=right->keynum; i++){
		right->key[i] = right->key[i+1];
		right->ptr[i] = right->ptr[i+1];
	}
	right->keynum--;
}

void BTree::RotateRight(TreeNode* parent, int index, TreeNode* cur, TreeNode* left){
	//将删除关键字的节点中的关键字序列后移一个位置
	for (int i=cur->keynum; i>=1; i--){
		cur->key[i+1] = cur->key[i];
		cur->ptr[i+1] = cur->ptr[i];
	}
	cur->key[1] = parent->key[index];	//将父节点index位置的关键字下移到删除关键字的节点中
	cur->ptr[0] = left->ptr[left->keynum];	
	if (cur->ptr[0])
		cur->ptr[0]->parent = cur;
	left->ptr[left->keynum] = NULL;
	cur->keynum++;

	//将左节点中的最大关键字上移至父节点
	parent->key[index] = left->key[left->keynum];
	left->key[left->keynum] = 0;
	left->keynum--;
}



void BTree::DeleteBalance(TreeNode* node){
	int lb = m / 2;	//lb为(向上取整)[m/2]-1
	TreeNode* parent = node->parent;
	while (parent!=NULL &&  node->keynum < lb){
		//说明删除了关键字后，原来的节点已经不满足B-树的要求
		//此时被删除关键字的节点剩余的关键字少于[m/2]-1,违背了B树的性质
		int index = 0;
		//找到node在其父亲节点中的位置
		for (int i=0; i<=parent->keynum; i++)
			if (parent->ptr[i] == node){
				index = i;
				break;
			}
		TreeNode* left = NULL, *right = NULL;
		if (index-1 >= 0)	//如果当前节点有左节点
			left = parent->ptr[index-1];
		if (index+1 <= parent->keynum)	//如果当前节点有右节点
			right = parent->ptr[index+1];
		if (right!=NULL && right->keynum>lb){
			//相邻的右节点中关键字数目大于[m/2]-1
			this->RotateLeft(parent,index,node,right);
			break;
		}
		else if (left!=NULL && left->keynum>lb){
			//相邻的左节点中关键字数目大于[m/2]-1
			this->RotateRight(parent,index,node,left);
			break;
		}
		else {
			//若相邻左右节点的关键字数目都等于[m/2]-1，那么需要进行合并
			if (left != NULL)	//如果相邻左节点存在，合并到左节点
				this->merge(parent,index,left,node);
			else	//如果相邻右节点不为空，则合并到右节点
				this->merge(parent,index+1,node,right);
			//合并后，父节点的关键字可能少于[m/2]-1，可能违反B树的性质
			//将父节点设置为当前节点
			node = parent;
			parent = node->parent;
		}	
	}
	if (node->keynum == 0){
		head = node->ptr[0];
		delete node;
	}
}

void BTree::Delete(TreeNode* node, int index){
	if (node->ptr[index-1] && node->ptr[index]) {
		//此处说明该节点是非叶子节点，且被删除关键字为该节点中的第index个关键字key[index]
		//可从node->ptr[index]所指的子树中找出最小关键字Y,代替key[index]的位置，然后从叶子节点中删去Y
		TreeNode* temp = node->ptr[index];
		while (temp->ptr[0] != NULL)
			temp = temp->ptr[0];
		int res = temp->key[1];
		this->delete_BTree(temp->key[1]);
		node->key[index] = res; 
	}
	else {
		//此处说明该节点是叶子，直接删掉该节点
		for (int i=index; i<=node->keynum; i++)
			node->key[i] = node->key[i+1];
		node->keynum--;
		//删除节点可能会影响B树的性质，调用DeleteBalance来恢复B树的性质
		this->DeleteBalance(node);
	}
}

int BTree::search(TreeNode*& node, int val){
	//找出并返回关键字val在node节点中关键序列的插入位置
	int i = 0;
	for (int j=1; j<=node->keynum; j++)
		if (node->key[j] <= val)
			i = j;
	return i;
}

/*
 * B-树的删除
 * 1 利用查找算法找出该关键字的节点，如果没有找到，则直接返回，否则根据val所在
 *   节点是否为叶子节点有不同的处理方法。
 * 2 若该节点为非叶子节点,且被删除的关键字为该节点中第i个关键字key[i],则可从指针
 *   ptr[i]中找出最小的关键字Y,代替key[i]的位置，然后在叶子节点中删去Y
 *
 *
 */
bool BTree::delete_BTree(int val){
	TreeNode* node = NULL;
	int index = 0;
	if (this->searchKey_BTree(val,node,index) == true){
		//找出关键字val所在的节点和相应下标，进行删除
		this->Delete(node,index);
		return true;
	}
	else
		//如果没有找到,则直接返回
		return false;
}

void BTree::split(TreeNode*& t, int middle, TreeNode*& rhs, int& k){
	rhs = new TreeNode();	//rhs为新建的节点，用来保存右半部分
	rhs->parent = t->parent;	//我们把t分裂，因此rhs和t有着共同的父母
	k = t->key[middle];	//关键字序列的中间值

	t->key[middle] = 0;
	//这个通过画图，可以知道rhs的0号孩子的指针就是t的s号节点指针
	rhs->ptr[0] = t->ptr[middle];
	if (rhs->ptr[0])
		rhs->ptr[0]->parent = rhs;
	t->ptr[middle] = NULL;
			
	//将右半部分拷贝到rhs节点
	for (int i=1; i<=m-middle; i++){
		rhs->key[i] = t->key[middle+i], t->key[middle+i] = 0;
		rhs->ptr[i] = t->ptr[middle+i], t->ptr[middle+i] = NULL;
		if (rhs->ptr[i])
			rhs->ptr[i]->parent = rhs;
	}

	rhs->keynum = m - middle;
	t->keynum = middle - 1;
}

void BTree::insert(TreeNode*& t, int index, int val, TreeNode* node){
	for (int j=t->keynum; j>=index+1; j--){
		t->key[j+1] = t->key[j];
		t->ptr[j+1] = t->ptr[j];
	}
	t->key[index+1] = val;
	t->ptr[index+1] = node;
	t->keynum++;
}
/* 
 * B-树的插入
 * 1 如果在B-树中查找到了关键字，则直接返回
 * 2 然后，在相应终端节点插入关键字后，判断关键字数量是否满足: n<=m-1,如果满足的话
 *   返回，否则进行分裂
 *   分裂的方法是:生成一个新的节点，把原节点关键字和插入的关键字排序后，从中间位置
 *   把关键字序列分为两部分，左部分所含关键字放在旧节点中，右部分所含关键字放在新
 *   节点中，中间位置的关键字放在父节点中，如果父节点的关键字也超过m-1，则要再分裂
 *   ，再往上插，直到这个过程传到根节点为止.
 */

void BTree::newroot(TreeNode*& head, TreeNode*& lhs, int curk, TreeNode*& rhs){
	TreeNode* temp = new TreeNode();
	temp->keynum = 1;
	temp->key[1] = curk;
	temp->ptr[0] = lhs;
	if (temp->ptr[0])
		temp->ptr[0]->parent = temp;
	temp->ptr[1] = rhs;
	if (temp->ptr[1])
		temp->ptr[1]->parent = temp;
	head = temp;
}

bool BTree::insert_BTree(int val){
	TreeNode* node;
	int index = 0;
	if (this->searchKey_BTree(val,node,index) == true)
		return false;
	//返回的node为关键字val应插入的叶子节点，index为在node关键字序列中的插入位置

	bool finished = false;
	int curk = val;
	TreeNode* rhs = NULL;
	while (node){
		//不管是否合法，直接插入到找到的那个关键字序列中
		this->insert(node,index,curk,rhs);
		if (node->keynum < m) 
			finished = true;	//如果插入的终端节点上的关键字数量满足keynum<=m-1,则插入不影响B树性质
		else {
			//否则该关键字的插入影响了B树的性质，需要对终端节点进行分裂
			int middle = (m + 1) / 2;
			this->split(node,middle,rhs,curk);
			if (node->parent == NULL)
				break;	//如果node已经是根节点了，则直接退出
			else {
				//此时curk为分裂节点的中间关键字,rhs为包含右半部分关键字的节点，找出curk在父节点的插入位置，并在下次循环中插入父节点中.
				node = node->parent;
				index = this->search(node,curk);
			}
		}
	}
	//如果此时finished为false,说明因为分裂的原因需要新生一个根节点
	if (finished == false)
		this->newroot(head,node,curk,rhs);
	return true;
}

//查找指定的关键字，若指定关键字不存在，则返回相应的插入位置
bool BTree::searchKey_BTree(int val, TreeNode*& node, int& index){
	if (head == NULL)
		return false;
	TreeNode* p = head, *q = NULL;
	while (p != NULL){
		int i = search(p,val);
		if (i>0 && p->key[i]==val){
			//若在B树中找到该关键字则返回
			index = i;
			node = p;
			return true;
		}
		else {
			node = p;
			index = i;	
			p = p->ptr[i];	
		}
	}
	//若在B树中找不到val关键字，则最终返回的node节点是叶子节点，且index为关键字val在node节点的关键字序列中的插入位置
	return false;
}


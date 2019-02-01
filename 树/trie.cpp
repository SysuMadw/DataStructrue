# include <iostream>
# include <vector>
# include <string>

# define maximum 256
 
using namespace std;


/*
 * Trie树的三个基本性质：
 * 1 根节点不包含字符，除根节点外每一个节点都只包含一个字符
 * 2 从根节点到某一个节点，路径上经过的字符连接起来，为该节点对应的字符串
 * 3 每个节点的所有子节点包含的字符都不相同
 */

/*
 * Trie树的作用：
 * 1 字符串检索
 * 2 词频统计
 * 3 去除重复单词，建立字典树的过程就是给字符串去重的过程
 * 4 字符串排序
 * 5 最长公共前缀
 * 6 前缀匹配，比如找以an为前缀的字符串
 */

/*
 * Trie树的优点:
 * 1 查询快，对于长度为m的键值，最坏情况下只需花费O(m)的时间
 * 2 当存储大量字符串时，Trie耗费的空间较少.因为键值并非显式存储的,而是与其他键值共享子串
 */

struct TreeNode {
	int count;
	TreeNode* next[maximum];
};

class Trietree {
	public :
		Trietree();	//构造函数
		~Trietree(); //析构函数
		//接口函数
		void Makempty();	//清空根节点下的所有子树
		vector<string> keys();	//返回以""为前缀的所有单词，即所有单词
		void insert(string& ans);	//插入一个关键字
		void deletekey(string& ans);	//删除一个关键字
		TreeNode* find(string& ans);	//寻找ans关键字，若存在则返回相应记录的叶子节点，否则返回NULL
		vector<string> KeysWithPrefix(string& ans);	//返回以ans为前缀的所有关键字
		vector<string> KeysthatMatch(string& ans);	//搜集Trietree中匹配指定模式字符串形式的字符串
		bool empty();	//判断Trietree是否为空
		string LongestPrefixOf(string& ans);	//获取指定字符串在Trietree中存在的最长前缀
	private:
		//辅助函数
		void Makempty(TreeNode*& tree);	//清空以tree为根节点的子树
		void insert(string& ans, TreeNode*& root, int index);
		void deletekey(string& ans, Trietree*& root, int index);
		int search(string& ans, TreeNode* root, int, int);
		void collect(string& ans, TreeNode* root, vector<string>& arr);
		void collect(string& pre, string& pat, TreeNode* root, vector<string>& arr);
		TreeNode* find(string& ans, TreeNode* root, int index);
		TreeNode* root;
};

Trietree::Trietree(){
	//构造函数
	root = new TreeNode();
	root->count = 0;
	for (int i=0; i<maximum; i++)
		next[i] = NULL;
}

Trietree::~Trietree(){
	//清空整棵字典树，释放所有节点占用的空间
	Makempty(root);
}

bool Trietree::empty() {
	for (int i=0; i<maximum; i++)
		if (root->next[i] != NULL)
			return false;
	return true;
}

void Trietree::Makempty(){
	//清除根节点的所有子树
	for (int i=0; i<maximum; i++)
		if (root->next[i] != NULL)
			Makempty(root->next[i]);
}


void Trietree::Makempty(TreeNode*& tree){
	//清除以tree节点为根的所有子树
	for (int i=0; i<maximum; i++)
		if (tree->next[i] != NULL)
			Makempty(tree->next[i]);
	delete tree; //删除当前节点
	tree = NULL;	//将节点置空
}

vector<string> Trietree::keys(){
	return KeysWithPrefix("");
}

vector<string> Trietree::KeysWithPrefix(string& ans){
	vector<string> arr;
	collect(ans,find(ans,root,0),arr);
	return arr;
}

TreeNode* Trietree::find(string& ans){
	TreeNode* node = find(ans,root,0);
	if (node==NULL || node->count==0)
		return NULL;
	else
		return node;
}

TreeNode* Trietree::find(string& ans, TreeNode* root, int index){
	if (root == NULL)	//节点不存在返回空
		return NULL;
	if (index == ans.length())	//若检索完成，返回该节点
		return root;
	//检索下一层
	return find(ans,root->next[ans[index]],index+1);
}

void Trietree::insert(string& ans){
	TreeNode* temp = find(ans);
	if (temp == NULL)
		insert(ans,root,0);	//从根节点开始递归插入
	else
		temp->count++;
}

void Trietree::insert(string& ans, TreeNode*& root, int index){
	if (root == NULL){
		//若没有节点则生成新的节点
		root = new TreeNode();
		root->count = 0;
		for (int i=0; i<maximum; i++)
			root->next[i] = NULL;
	}

	if (index == ans.length()){
		//若检索到最后一位，则置count的值为1
		root->count = 1;
		return;
	}
	//检索下一层节点
	insert(ans,root->next[ans[index]],index+1);
}

void Trietree::deletekey(string& ans){
	deletekey(ans,root,0); //从根节点开始递归删除
}

void Trietree::deletekey(string& ans, Trietree*& root, int index){
	if (root == NULL)
		return;
	if (index == ans.length())
		root->count = 0;
	else
		deletekey(ans,root->next[ans[index]],index+1);	//检索下一层

	if (root->count != 0)
		return;

	for (int i=0; i<maximum; i++)
		if (root->next[i] != NULL)
			return;
	delete root;
	root = NULL;
}

int Trietree::search(string& ans, TreeNode* root, int index, int length){
	//空树则返回当前前缀长度
	if (root == NULL)
		return length;
	else
		length = length + 1;
	
	if (root->count != 0 || index == ans.length())
		return length;
	//检索下一层
	return search(ans,root->next[ans[index]],index+1,length);
}	

string Trietree::LongestPrefixOf(string& ans){
	if (ans.length() == 0)
		return string();
	int len = search(ans,root->next[ans[0]],1,0);
	return ans.substr(0,len);
}

void Trietree::collect(string& ans, TreeNode* root, vector<string>& arr){
	if (root == NULL)
		return;

	if (root->count != 0)
		arr.push_back(ans);

	for (int i=0; i<maximum; i++)
		collect(key+i,root->next[i],arr);
}

void Trietree::collect(string& pre, string& pat, TreeNode* root, vector<string>& arr){
	int index = pre.length();
	if (root == NULL)
		return;
	//若前缀长度与指定单词相同且当前节点代表记录存在，则存入数组
	if (index==pat.length() && root->count!=0)
		arr.push_back(pre);
	//如果仅仅是长度相同则直接返回
	if (index == pat.length())
		return;

	//检索下一层节点
	int next = pat[index];
	for (int i=0; i<maximum; i++)
		if (next=='.' || next==i)
			collect(pre+i,pat,root->next[i],arr;)
}

vector<string> Trietree::KeysthatMatch(string& ans){
	vector<string> arr;
	collect("",ans,root,arr);
	return arr;
}




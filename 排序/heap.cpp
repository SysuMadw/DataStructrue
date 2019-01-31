# include <iostream>
# include <vector> 

# define parent(i) (i>>1)
# define left(i) (i<<1)
# define right(i) (i<<1 + 1)

using namespace std;

//在最大堆中，除了根以外的所有节点i都要满足:A[parent(i)] >= A[i]
//在最小堆中，除了根以外的所有节点i都要满足:A[parent(i)] <= A[i]

void max_heapify(vector<int>& heap, int heapnum, int i){
	//维护最大堆的性质，假定左子树和右子树都是最大堆，而这时heap[i]有可能小于其孩子，违反了最大堆的性质
	//通过让heap[i]的值在最大堆中逐级下落，从而使得以i为根节点的子树重新满足最大堆的性质
	int left = left(i), right = right(i), largest = i;
	if (left<=heapnum && heap[left]>heap[largest])
		largest = left;
	if (right<=heapnum && heap[right]>heap[largest])
		largest = right;
	if (largest != i){
		int temp = heap[i];
		heap[i] = heap[largest];
		heap[largest] = temp;
		max_heapify(heap,heapnum,largest);
	}
}

void build_max_heap(vector<int>& heap){
	//当用数组表示存储n个元素的堆时，叶子节点的下标分别是(向下取整)[n/2]+1,[n/2]+2,...,n
	//对于任一包含n个元素的堆中，至多有(向上取整)[n/2^(h+1)]个高度为h的节点
	int n = ans.size();
	for (int i=n/2; i>=1; i--)
		max_heapify(heap,n,i);
}


void heapsort(vector<int>& heap){
	int n = heap.size();
	build_max_heap(heap);
	for (int i=heap.size()-1; i>=2; i--){
		int temp = heap[n];
		heap[n] = heap[1];
		heap[1] = temp;
		n--;
		max_heapify(heap,n,1);
	}
}

//基于最小堆实现最小优先队列
int heap_minimum(vector<int>& heap){
	//返回最小优先队列中的最小元素
	return heap[1];
}

int heap_extract_min(vector<int>& heap, int& n){
	//返回并去掉最小优先队列中具有最小关键字的元素
	int Min = heap[1];
	heap[1] = heap[n];
	n = n - 1;
	min_heapify(heap,n-1,1);
	return Min;
}

void heap_decrease_key(vector<int>& heap, int i, int k){
	//将heap[i]的关键字值减少到k，k必须不大于heap[i]
	if (k >= heap[i])
		return;		//k必须不大于heap[i]
	heap[i] = k;
	while (i>1 && heap[parent(i)]>heap[i]){
		int temp = heap[parent(i)];
		heap[parent(i)] = heap[i];
		heap[i] = temp;
		i = parent(i);
	}
}

void min_heap_insert(vector<int>& heap, int val, int& n){
	//将关键字val插入最小优先队列中
	heap.push_back(INT_MAX);
	n++;
	heap_decrease_key(heap,n,val);
}










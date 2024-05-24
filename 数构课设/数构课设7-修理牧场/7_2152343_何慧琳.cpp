#include <iostream>
using namespace std;

template<class Type>
class MinHeap {
public:
	MinHeap(int maxsize=10);
	MinHeap(Type arr[], int n=10);
	~MinHeap() { delete[] heap; }
	int insert(const Type& x);//插入结点
	int DeleteMin(Type& x);//在x堆中删除最小结点
	int IsEmpty() const { return CurrentSize == 0; }//判断堆是否为空
	int IsFull() const{return CurrentSize == MaxHeapSize;}//判断堆是否满
	void MakeEmpty() { CurrentSize = 0; }//置空堆
private:
	Type* heap;
	int CurrentSize;//堆当前大小
	int MaxHeapSize;//堆最大大小
	void FilterDown(int i, int m);//向下调整
	void FilterUp(int i);//向上调整
};
template <class Type> MinHeap <Type> ::MinHeap(int maxSize) 
{//根据给定大小maxSize,建立堆对象
	MaxHeapSize = maxSize;//确定堆大小
	heap = new Type[MaxHeapSize]; //创建堆空间
	CurrentSize = 0; //初始化
}
template <class Type> MinHeap <Type> ::MinHeap(Type arr[], int n)
{//根据给定数组中的数据和大小,建立堆对象
	MaxHeapSize = n;
	heap = new Type[MaxHeapSize];
	heap = arr; //数组传送
	CurrentSize = n; //当前堆大小
	int currentPos = (CurrentSize - 2) / 2; //最后非叶
	while (currentPos >= 0) {
		//从下到上逐步扩大,形成堆
		FilterDown(currentPos, CurrentSize - 1);
		//从currentPos开始,到CurrentSize为止, 调整
		currentPos--;
	}
}
template <class Type> int MinHeap<Type> ::insert(const Type& x) 
{//在堆中插入新元素 x
	if (CurrentSize == MaxHeapSize) //堆满
	{
		cout << "堆已满" << endl; 
		return 0;
	}
	heap[CurrentSize] = x; //插在表尾
	FilterUp(CurrentSize); //向上调整为堆
	CurrentSize++; //堆元素增一
	return 1;
}
template <class Type> int MinHeap <Type> ::DeleteMin(Type& x)
{//最小元素出队，将最小元素传给x
	if (!CurrentSize)
	{
		cout << " 堆已空" << endl;
		return 0; 
	} 
	x = heap[0]; //最小元素出队列
	heap[0] = heap[CurrentSize - 1];//用最大元素填补
	CurrentSize--; 
	FilterDown(0, CurrentSize - 1);//从0号位置开始自顶向下调整为堆
	return 1;
}
template <class Type> void MinHeap<Type> ::FilterDown(int start, int EndOfHeap)
{//从start位置开始自顶向下调整堆
	int i = start, j = 2 * i + 1; // j 是 i 的左子女
	Type temp = heap[i];
	while (j <= EndOfHeap) {
		if (j < EndOfHeap && heap[j].root->key >heap[j + 1].root->key)
			j++; //两子女中选小者
		if (temp.root->key <= heap[j].root->key)
			break;
		else { 
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}
template <class Type> void MinHeap<Type> ::FilterUp(int start)
{//从 start 开始,向上直到0,调整堆
	int j = start, i = (j - 1) / 2; // i 是 j 的双亲
	Type temp = heap[j];
	while (j > 0) {
		if (heap[i].root->key <= temp.root->key) break;
		else { heap[j] = heap[i]; j = i; i = (i - 1) / 2; }
	}
	heap[j] = temp;
}


class ExtBinTree;//扩充二叉树
class Element {
	friend class ExtBinTree;
	template <class Type> friend void HuffmanTree(Type* fr, int n, ExtBinTree& newtree);
	template <class Type> friend class MinHeap;
	int key;//权值
	Element* leftchild, * rightchild;
};
class ExtBinTree {
	template <class Type> friend void HuffmanTree(Type* fr, int n, ExtBinTree& newtree);
	template <class Type> friend class MinHeap;
public:
	ExtBinTree(ExtBinTree& bt1, ExtBinTree& bt2)
	{//将bt2与bt1合并
		root->leftchild = bt1.root;
		root->rightchild = bt2.root;
		root->key = bt1.root->key + bt2.root->key;
	}
	ExtBinTree() { root = new Element(); }
	ExtBinTree(ExtBinTree* bt)
	{
		root = bt->root;
	}
private:
	Element* root=new Element();//扩充二叉树的根
};

template <class Type>
void HuffmanTree(Type* fr, int n, ExtBinTree& newtree)
{//建立霍夫曼树
	ExtBinTree first, second;
	ExtBinTree  *Node=new ExtBinTree[n];
	int ans=0;//最小权重和
	for (int i = 0; i < n; i++) {
		Node[i].root->key = fr[i];
		Node[i].root->leftchild =Node[i].root->rightchild = NULL;
	} //传送初始权值
	MinHeap < ExtBinTree> hp(Node, n); //最小堆
	for (int i = 0; i < n - 1; i++) {//建立霍夫曼树的过程，做n-1趟
		hp.DeleteMin(first); //选根权值最小的树
		hp.DeleteMin(second); //选根权值次小的树
		newtree = new ExtBinTree(first, second); //建新的根结点
		ans += newtree.root->key;
		hp.insert(newtree); //形成新树插入
	}
	cout << ans << endl;
}



int main()
{
	cout << "请输入要将木头锯成的块数N：";
	int N;
	while (1) {
		cin >> N;
		if (cin.fail() || N <= 0) {
			cout << "输入错误请重新输入：";
			cin.ignore(100, '\n');
			cin.clear();
		}
		else
			break;
	}
	cout << "请输入每块木头的长度：" << endl;
	int* a=new int[N];
	for (int i = 0; i < N; i++) {
		while (1) {
			cin >> a[i];
			if (cin.fail() || a[i] <= 0) {
				cout << "第" << i + 1 << "块木头长度输入错误，请重新从该处输入！" << endl;
				cin.ignore(1000, '\n');
				cin.clear();
			}
			else
				break;
		}
	}
	ExtBinTree ebt;//存储目标生成树
	HuffmanTree<int>(a, N, ebt);
	cin.ignore(100, '\n');
	cout << "程序结束，按回车键退出！";
	while (getchar() != '\n')
		;
	return 0;
}
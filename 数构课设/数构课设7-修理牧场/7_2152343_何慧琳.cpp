#include <iostream>
using namespace std;

template<class Type>
class MinHeap {
public:
	MinHeap(int maxsize=10);
	MinHeap(Type arr[], int n=10);
	~MinHeap() { delete[] heap; }
	int insert(const Type& x);//������
	int DeleteMin(Type& x);//��x����ɾ����С���
	int IsEmpty() const { return CurrentSize == 0; }//�ж϶��Ƿ�Ϊ��
	int IsFull() const{return CurrentSize == MaxHeapSize;}//�ж϶��Ƿ���
	void MakeEmpty() { CurrentSize = 0; }//�ÿն�
private:
	Type* heap;
	int CurrentSize;//�ѵ�ǰ��С
	int MaxHeapSize;//������С
	void FilterDown(int i, int m);//���µ���
	void FilterUp(int i);//���ϵ���
};
template <class Type> MinHeap <Type> ::MinHeap(int maxSize) 
{//���ݸ�����СmaxSize,�����Ѷ���
	MaxHeapSize = maxSize;//ȷ���Ѵ�С
	heap = new Type[MaxHeapSize]; //�����ѿռ�
	CurrentSize = 0; //��ʼ��
}
template <class Type> MinHeap <Type> ::MinHeap(Type arr[], int n)
{//���ݸ��������е����ݺʹ�С,�����Ѷ���
	MaxHeapSize = n;
	heap = new Type[MaxHeapSize];
	heap = arr; //���鴫��
	CurrentSize = n; //��ǰ�Ѵ�С
	int currentPos = (CurrentSize - 2) / 2; //����Ҷ
	while (currentPos >= 0) {
		//���µ���������,�γɶ�
		FilterDown(currentPos, CurrentSize - 1);
		//��currentPos��ʼ,��CurrentSizeΪֹ, ����
		currentPos--;
	}
}
template <class Type> int MinHeap<Type> ::insert(const Type& x) 
{//�ڶ��в�����Ԫ�� x
	if (CurrentSize == MaxHeapSize) //����
	{
		cout << "������" << endl; 
		return 0;
	}
	heap[CurrentSize] = x; //���ڱ�β
	FilterUp(CurrentSize); //���ϵ���Ϊ��
	CurrentSize++; //��Ԫ����һ
	return 1;
}
template <class Type> int MinHeap <Type> ::DeleteMin(Type& x)
{//��СԪ�س��ӣ�����СԪ�ش���x
	if (!CurrentSize)
	{
		cout << " ���ѿ�" << endl;
		return 0; 
	} 
	x = heap[0]; //��СԪ�س�����
	heap[0] = heap[CurrentSize - 1];//�����Ԫ���
	CurrentSize--; 
	FilterDown(0, CurrentSize - 1);//��0��λ�ÿ�ʼ�Զ����µ���Ϊ��
	return 1;
}
template <class Type> void MinHeap<Type> ::FilterDown(int start, int EndOfHeap)
{//��startλ�ÿ�ʼ�Զ����µ�����
	int i = start, j = 2 * i + 1; // j �� i ������Ů
	Type temp = heap[i];
	while (j <= EndOfHeap) {
		if (j < EndOfHeap && heap[j].root->key >heap[j + 1].root->key)
			j++; //����Ů��ѡС��
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
{//�� start ��ʼ,����ֱ��0,������
	int j = start, i = (j - 1) / 2; // i �� j ��˫��
	Type temp = heap[j];
	while (j > 0) {
		if (heap[i].root->key <= temp.root->key) break;
		else { heap[j] = heap[i]; j = i; i = (i - 1) / 2; }
	}
	heap[j] = temp;
}


class ExtBinTree;//���������
class Element {
	friend class ExtBinTree;
	template <class Type> friend void HuffmanTree(Type* fr, int n, ExtBinTree& newtree);
	template <class Type> friend class MinHeap;
	int key;//Ȩֵ
	Element* leftchild, * rightchild;
};
class ExtBinTree {
	template <class Type> friend void HuffmanTree(Type* fr, int n, ExtBinTree& newtree);
	template <class Type> friend class MinHeap;
public:
	ExtBinTree(ExtBinTree& bt1, ExtBinTree& bt2)
	{//��bt2��bt1�ϲ�
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
	Element* root=new Element();//����������ĸ�
};

template <class Type>
void HuffmanTree(Type* fr, int n, ExtBinTree& newtree)
{//������������
	ExtBinTree first, second;
	ExtBinTree  *Node=new ExtBinTree[n];
	int ans=0;//��СȨ�غ�
	for (int i = 0; i < n; i++) {
		Node[i].root->key = fr[i];
		Node[i].root->leftchild =Node[i].root->rightchild = NULL;
	} //���ͳ�ʼȨֵ
	MinHeap < ExtBinTree> hp(Node, n); //��С��
	for (int i = 0; i < n - 1; i++) {//�������������Ĺ��̣���n-1��
		hp.DeleteMin(first); //ѡ��Ȩֵ��С����
		hp.DeleteMin(second); //ѡ��Ȩֵ��С����
		newtree = new ExtBinTree(first, second); //���µĸ����
		ans += newtree.root->key;
		hp.insert(newtree); //�γ���������
	}
	cout << ans << endl;
}



int main()
{
	cout << "������Ҫ��ľͷ��ɵĿ���N��";
	int N;
	while (1) {
		cin >> N;
		if (cin.fail() || N <= 0) {
			cout << "����������������룺";
			cin.ignore(100, '\n');
			cin.clear();
		}
		else
			break;
	}
	cout << "������ÿ��ľͷ�ĳ��ȣ�" << endl;
	int* a=new int[N];
	for (int i = 0; i < N; i++) {
		while (1) {
			cin >> a[i];
			if (cin.fail() || a[i] <= 0) {
				cout << "��" << i + 1 << "��ľͷ����������������´Ӹô����룡" << endl;
				cin.ignore(1000, '\n');
				cin.clear();
			}
			else
				break;
		}
	}
	ExtBinTree ebt;//�洢Ŀ��������
	HuffmanTree<int>(a, N, ebt);
	cin.ignore(100, '\n');
	cout << "������������س����˳���";
	while (getchar() != '\n')
		;
	return 0;
}
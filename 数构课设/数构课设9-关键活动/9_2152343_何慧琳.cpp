#include <iostream>
using namespace std;

template<class Type>
class Queue {
	struct QueueNode {
		Type data;//���ֵ
		QueueNode* link;//����ָ��
		QueueNode(Type d) :data(d), link(NULL) {};//���캯��
	};
	QueueNode* first,*current;//����ָ�룬�ֱ�ָ�����ͷ�����ڱ���
public:
	Queue() :first(NULL),current(NULL){};//���캯��
	~Queue();//��������
	void push(Type newnode);//������newnodeΪֵ���½��
	Type pop();//ɾȥ��ͷ��㷵����ֵ
	int IsEmpty() { return first == NULL; }//�ж϶����Ƿ�Ϊ��
};
template<class Type> Queue<Type>::~Queue()
{//��������
	while (first) {//����ͷŽ��
		QueueNode* p = first;
		first = first->link;
		delete p;
	}
}
template<class Type> void Queue<Type>::push(Type newnode)
{//��������Ҫ������˳������½��
	if (first == NULL) {//����Ϊ�գ������½��
		first = current = new QueueNode(newnode);
	}
	else {//��ͷ��㿪ʼ�����ҵ���ȷ�Ĳ���λ��
		current = first;
		QueueNode* temp= current->link;
		while (temp) {
			if (newnode > current->data && newnode <= temp->data) {
				temp = new QueueNode(newnode);
				temp->link = current->link;
				current->link = temp;//��ɲ���
				break;
			}
			current = current->link;
			temp = current->link;
		}
		if (temp == NULL)//������δ�ҵ����ʲ���λ�ã�current��Ϊ���һ����㣬�ڶ�β�����½��
			current->link = new QueueNode(newnode);
	}
}
template<class Type> Type Queue<Type>::pop()
{
	Type ret = first->data;//�����ͷ��ֵ
	QueueNode* p = first;
	first = first->link;//��ͷ����
	delete p;//�ͷ�ԭ��ͷ
	return ret;
}



template<class NameType, class DistType>
class Graph;

template <class DistType> 
class Edge {//�߱����ඨ��
	template<class NameType, class DistType>
	friend class Graph;
	int dest;//�ߵ��յ����
	DistType cost;//�ߵ�Ȩֵ
	Edge<DistType>* link;//ָ����һ����
	Edge() { }//Ĭ�Ϲ��캯��
	Edge(int D, DistType C) :dest(D), cost(C), link(NULL) { }//���ι��캯��
	int operator != (Edge<DistType>& E)	const//���������
    {
		return dest != E.dest;
	}
};

template<class NameType,class DistType>
class Vertex {//ͼ�Ľ���ඨ��
	friend class Graph<NameType, DistType>;
	NameType name;//�����
	Edge<DistType>* adj_first,*adj_current;//ָ��߱�ĵ�һ���ߺ͵�ǰ���һ����
	Vertex(Vertex* v) :name(v.name), adj_first(v->adj_first), adj_current(v->adj_current) {};//���ƹ��캯��
	Vertex():name(NULL),adj_first(NULL),adj_current(NULL) {};//Ĭ�Ϲ��캯��
};

template<class NameType, class DistType>
class Graph {//�ؼ��ͼ���ඨ��
public:
	Graph(const int vertices = 0) : MaxNumVertex(vertices) //���캯��
	{
		NodeTable = new Vertex<NameType, DistType>[MaxNumVertex];
		count = new int[MaxNumVertex];
	};
	~Graph();
	int GetSeq(NameType name);//������nameΪ���Ľ���ڽڵ������е����
	void InsertVertex(NameType vertex);//����ڵ�
	void InsertEdge(NameType v1, NameType v2,DistType weight);//�����
	int TopologicalOrder(int* TopoQueue);//��������
	void CriticalPath();//��ؼ��
private:
	Vertex<NameType, DistType>* NodeTable;//�������
	int* count;//ÿ�������������
	int NumVertex=0;//��ǰ������
	int MaxNumVertex;//��������
};

template <class NameType, class DistType>
Graph<NameType, DistType> ::~Graph() 
{//��������
	for (int i = 0; i < NumVertex; i++) {
		Edge<DistType>* p = NodeTable[i].adj_first;
		while (p != NULL) { //�������ͷ�
			NodeTable[i].adj_first = p->link;
			delete p;
			p = NodeTable[i].adj_first;
		}
	}
	delete[] NodeTable; //�ͷŶ����
}
template <class NameType, class DistType>
int Graph<NameType, DistType> ::GetSeq(NameType name)
{//������nameΪ���Ľ���ڽڵ������е����
	for (int i = 0; i <= NumVertex; i++) {
		if (NodeTable[i].name == name)
			return i;
	}
	return -1;
}
template <class NameType, class DistType>
void Graph<NameType, DistType> ::InsertVertex(NameType vertex)
{
	NodeTable[NumVertex].name = vertex;//�ڽ�������м���������
	count[NumVertex] = 0;//��ʼ���ý�����
	NumVertex++;//��ǰ������+1
}
template <class NameType, class DistType>
void Graph<NameType, DistType> ::InsertEdge(NameType v1, NameType v2, DistType weight)
{//������v1Ϊ���v2Ϊ�յ�weightΪ��Ȩ�ı�
	int seq1 = GetSeq(v1);
	int seq2 = GetSeq(v2);//��ȡ�������ı��
	if (NodeTable[seq1].adj_first == NULL) {//��seq1�ı߱�����һ����
		NodeTable[seq1].adj_first = NodeTable[seq1].adj_current = new Edge<DistType>(seq2, weight);
	}
	else {
		NodeTable[seq1].adj_current->link = new Edge<DistType>(seq2, weight);//��seq1�ı߱�ĩβ�����±�
		NodeTable[seq1].adj_current = NodeTable[seq1].adj_current->link;//���±߱�ָ��
	}
	count[seq2]++;//v2������+1
}
template <class NameType, class DistType>
int Graph<NameType, DistType> ::TopologicalOrder(int* TopoQueue)
{//�������򣬽������Ľ������Topo_NodeTable
	int top = -1; //���Ϊ��Ķ���ջ��ʼ��
	for (int i = 0; i < MaxNumVertex; i++) //���Ϊ�㶥���ջ
		if (count[i] == 0) { 
			count[i] = top; 
			top = i; 
		}
	for (int i = 0; i < MaxNumVertex; i++) //�������n������
		if (top == -1) { //��;ջ��,ת��
			return -1;//�������л�·(����),����-1
		}
		else { //������������
			int j = top; 
			top = count[top]; //��ջ
			TopoQueue[i]= j; //����ż���������������
			Edge<DistType>* l = NodeTable[j].adj_first;
			while (l) { //ɨ��ö���ĳ��߱�
				int k = l->dest; //��һ����
				if (--count[k] == 0) //�ö�����ȼ�һ
				{
					count[k] = top; 
					top = k;
				} //������
				l = l->link;
			}
		}
}
template <class NameType, class DistType>
void Graph<NameType, DistType> ::CriticalPath()
{
	int i, j,k;
	DistType e, l;//������翪ʼʱ�����������ʼʱ��
	DistType* Ve = new DistType[MaxNumVertex];//��¼��������翪ʼʱ��
	DistType* Vl = new DistType[MaxNumVertex];//��¼�������������ʼʱ��
	int* TopoQueue=new int[MaxNumVertex];//����һ��int���鱣�����������Ľ����˳��
	struct path_edge {//����һ���ṹ�壬���ڱ�ʾ�ؼ��������
		NameType src,dst;//����յ���
		int operator > (path_edge E) const//���������
		{//�����С������
			return src > E.src;
		}
		int operator <= (path_edge E) const//���������
		{//�����С������
			return src <= E.src;
		}
		path_edge(NameType s, NameType d) :src(s), dst(d) {};//���캯��
	};
	Queue<path_edge> critical_path;//����ؼ�·��,�����������
	//����Ƿ��л���������˽������
	if (TopologicalOrder(TopoQueue) == -1) {//�л��������еķ��������0
		cout << "0" << endl;
		return;
	}
	//�޻����ѻ���������������飬�������ҹؼ��
	Edge<DistType>* p;//�߱����ָ��
	for (i = 0; i < MaxNumVertex; i++) //��ʼ��Ve����
		Ve[i] = 0;
	for (i = 0; i < MaxNumVertex; i++) {//�����������翪ʼʱ��(��㵽�õ������)
		int m = TopoQueue[i];
		p = NodeTable[m].adj_first;//ָ��ǰ���߱�
		while (p != NULL) {
			k = p->dest;
			if (Ve[m] + p->cost > Ve[k])
				Ve[k] = Ve[m] + p->cost; 
			p = p->link;
		}
	}
	cout <<"�����Ŀ��ʱ��"<< Ve[MaxNumVertex - 1] << endl;//������������Ŀ�������ʱ��
	for (i = 0; i < MaxNumVertex; i++)//��ʼ��Vl����Ϊ���л��̿�����ʱ
		Vl[i] = Ve[MaxNumVertex - 1];
	for (i = MaxNumVertex - 2; i; i--) {//�ӵ����ڶ����㿪ʼ������������������ʼʱ��
		int m = TopoQueue[i];
		p = NodeTable[m].adj_first;
		while (p != NULL) {
			k = p->dest;
			if (Vl[k] - p->cost < Vl[m])
				Vl[m] = Vl[k] - p->cost;
			p = p->link;
		}
	}
	for (i = 0; i < MaxNumVertex; i++) {//���ҹؼ��
		int m = TopoQueue[i];
		p = NodeTable[m].adj_first;
		while (p != NULL) {
			k = p->dest;
			e = Ve[m]; 
			l = Vl[k] - p->cost;
			if (l == e)
				critical_path.push(path_edge(m, k));//���������ı߼���ؼ�·��
			p = p->link;
		}
	}
	//����ؼ��
	cout << "�ؼ����" << endl;
	while (!critical_path.IsEmpty()) {
		path_edge l = critical_path.pop();//��ͷ����
		cout << NodeTable[l.src].name << "->" << NodeTable[l.dst].name << endl;
	}
}




int main()
{
	int N, M;//���񽻽ӵ�����N������������M
	cout << "��ӭ������ؼ������" << endl;
	cout << "���������񽻽ӵ�����N������������M" << endl;
	while (1) {//���빤��
		cin >> N >> M;
		if (cin.fail() || N <= 0 || M <= 0 || N-1 > M) {
			cout << "����������������룡" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		else
			break;
	}
	Graph<int, int> activities(N);//����һ��ͼ����
	for (int i = 0; i < N; i++) //��ʼ���������������
		activities.InsertVertex(i+1);
	cout << "������" << M << "������Ŀ�ʼ����ɵĽ��ӵ��ţ�1-"<<N<<"�����Լ���ɸ���������Ҫ��ʱ�䣨����������" << endl;
	for (int i = 0; i < M; i++) {//���벢����M����
		int start, dest;//��㡢�յ���
		int time;//�����������ʱ��
		while(1) {//���빤��
			cin >> start >> dest>>time;
			if (cin.fail() || (start-1)*(start-N)>0 || (dest - 1) * (dest - N) > 0 || time<=0) {
				cout << "����������������룡" << endl;
				cin.clear();
				cin.ignore(100, '\n');
			}
			else
				break;
		}
		activities.InsertEdge(start, dest, time);//����������
	}
	activities.CriticalPath();//��Ⲣ����ؼ�·��
	cout << "���س����˳���" << endl;
	cin.ignore(100, '\n');
	while (getchar() != '\n')
		;
	return 0;
}
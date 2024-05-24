#include <iostream>
using namespace std;

template<class Type>
class Queue {
	struct QueueNode {
		Type data;//结点值
		QueueNode* link;//链接指针
		QueueNode(Type d) :data(d), link(NULL) {};//构造函数
	};
	QueueNode* first,*current;//队列指针，分别指向队列头和用于遍历
public:
	Queue() :first(NULL),current(NULL){};//构造函数
	~Queue();//析构函数
	void push(Type newnode);//加入已newnode为值的新结点
	Type pop();//删去队头结点返回其值
	int IsEmpty() { return first == NULL; }//判断队列是否为空
};
template<class Type> Queue<Type>::~Queue()
{//析构函数
	while (first) {//逐个释放结点
		QueueNode* p = first;
		first = first->link;
		delete p;
	}
}
template<class Type> void Queue<Type>::push(Type newnode)
{//按照题中要求的输出顺序加入新结点
	if (first == NULL) {//队列为空，创建新结点
		first = current = new QueueNode(newnode);
	}
	else {//从头结点开始遍历找到正确的插入位置
		current = first;
		QueueNode* temp= current->link;
		while (temp) {
			if (newnode > current->data && newnode <= temp->data) {
				temp = new QueueNode(newnode);
				temp->link = current->link;
				current->link = temp;//完成插入
				break;
			}
			current = current->link;
			temp = current->link;
		}
		if (temp == NULL)//队列中未找到合适插入位置，current已为最后一个结点，在队尾插入新结点
			current->link = new QueueNode(newnode);
	}
}
template<class Type> Type Queue<Type>::pop()
{
	Type ret = first->data;//保存队头的值
	QueueNode* p = first;
	first = first->link;//队头出队
	delete p;//释放原队头
	return ret;
}



template<class NameType, class DistType>
class Graph;

template <class DistType> 
class Edge {//边表结点类定义
	template<class NameType, class DistType>
	friend class Graph;
	int dest;//边的终点序号
	DistType cost;//边的权值
	Edge<DistType>* link;//指向下一条边
	Edge() { }//默认构造函数
	Edge(int D, DistType C) :dest(D), cost(C), link(NULL) { }//带参构造函数
	int operator != (Edge<DistType>& E)	const//运算符重载
    {
		return dest != E.dest;
	}
};

template<class NameType,class DistType>
class Vertex {//图的结点类定义
	friend class Graph<NameType, DistType>;
	NameType name;//结点名
	Edge<DistType>* adj_first,*adj_current;//指向边表的第一条边和当前最后一条边
	Vertex(Vertex* v) :name(v.name), adj_first(v->adj_first), adj_current(v->adj_current) {};//复制构造函数
	Vertex():name(NULL),adj_first(NULL),adj_current(NULL) {};//默认构造函数
};

template<class NameType, class DistType>
class Graph {//关键活动图的类定义
public:
	Graph(const int vertices = 0) : MaxNumVertex(vertices) //构造函数
	{
		NodeTable = new Vertex<NameType, DistType>[MaxNumVertex];
		count = new int[MaxNumVertex];
	};
	~Graph();
	int GetSeq(NameType name);//返回以name为名的结点在节点数组中的序号
	void InsertVertex(NameType vertex);//插入节点
	void InsertEdge(NameType v1, NameType v2,DistType weight);//插入边
	int TopologicalOrder(int* TopoQueue);//拓扑排序
	void CriticalPath();//求关键活动
private:
	Vertex<NameType, DistType>* NodeTable;//结点数组
	int* count;//每个结点的入度数组
	int NumVertex=0;//当前结点个数
	int MaxNumVertex;//最大结点个数
};

template <class NameType, class DistType>
Graph<NameType, DistType> ::~Graph() 
{//析构函数
	for (int i = 0; i < NumVertex; i++) {
		Edge<DistType>* p = NodeTable[i].adj_first;
		while (p != NULL) { //逐条边释放
			NodeTable[i].adj_first = p->link;
			delete p;
			p = NodeTable[i].adj_first;
		}
	}
	delete[] NodeTable; //释放顶点表
}
template <class NameType, class DistType>
int Graph<NameType, DistType> ::GetSeq(NameType name)
{//返回以name为名的结点在节点数组中的序号
	for (int i = 0; i <= NumVertex; i++) {
		if (NodeTable[i].name == name)
			return i;
	}
	return -1;
}
template <class NameType, class DistType>
void Graph<NameType, DistType> ::InsertVertex(NameType vertex)
{
	NodeTable[NumVertex].name = vertex;//在结点数组中加入这个结点
	count[NumVertex] = 0;//初始化该结点入度
	NumVertex++;//当前结点个数+1
}
template <class NameType, class DistType>
void Graph<NameType, DistType> ::InsertEdge(NameType v1, NameType v2, DistType weight)
{//插入以v1为起点v2为终点weight为边权的边
	int seq1 = GetSeq(v1);
	int seq2 = GetSeq(v2);//获取两个结点的编号
	if (NodeTable[seq1].adj_first == NULL) {//在seq1的边表创建第一条边
		NodeTable[seq1].adj_first = NodeTable[seq1].adj_current = new Edge<DistType>(seq2, weight);
	}
	else {
		NodeTable[seq1].adj_current->link = new Edge<DistType>(seq2, weight);//在seq1的边表末尾插入新边
		NodeTable[seq1].adj_current = NodeTable[seq1].adj_current->link;//更新边表指针
	}
	count[seq2]++;//v2结点入度+1
}
template <class NameType, class DistType>
int Graph<NameType, DistType> ::TopologicalOrder(int* TopoQueue)
{//拓扑排序，将排序后的结果存入Topo_NodeTable
	int top = -1; //入度为零的顶点栈初始化
	for (int i = 0; i < MaxNumVertex; i++) //入度为零顶点进栈
		if (count[i] == 0) { 
			count[i] = top; 
			top = i; 
		}
	for (int i = 0; i < MaxNumVertex; i++) //期望输出n个顶点
		if (top == -1) { //中途栈空,转出
			return -1;//网络中有回路(有向环),返回-1
		}
		else { //继续拓扑排序
			int j = top; 
			top = count[top]; //退栈
			TopoQueue[i]= j; //结点编号加入拓扑排序数组
			Edge<DistType>* l = NodeTable[j].adj_first;
			while (l) { //扫描该顶点的出边表
				int k = l->dest; //另一顶点
				if (--count[k] == 0) //该顶点入度减一
				{
					count[k] = top; 
					top = k;
				} //减至零
				l = l->link;
			}
		}
}
template <class NameType, class DistType>
void Graph<NameType, DistType> ::CriticalPath()
{
	int i, j,k;
	DistType e, l;//活动的最早开始时间和最晚允许开始时间
	DistType* Ve = new DistType[MaxNumVertex];//记录各结点最早开始时间
	DistType* Vl = new DistType[MaxNumVertex];//记录各结点最晚允许开始时间
	int* TopoQueue=new int[MaxNumVertex];//构建一个int数组保存拓扑排序后的结点编号顺序
	struct path_edge {//构建一个结构体，用于表示关键活动所经边
		NameType src,dst;//起点终点名
		int operator > (path_edge E) const//运算符重载
		{//起点编号小的优先
			return src > E.src;
		}
		int operator <= (path_edge E) const//运算符重载
		{//起点编号小的优先
			return src <= E.src;
		}
		path_edge(NameType s, NameType d) :src(s), dst(d) {};//构造函数
	};
	Queue<path_edge> critical_path;//保存关键路径,用于最终输出
	//检查是否有环，获得拓扑结点数组
	if (TopologicalOrder(TopoQueue) == -1) {//有环，不可行的方案，输出0
		cout << "0" << endl;
		return;
	}
	//无环，已获得拓扑排序结点数组，继续查找关键活动
	Edge<DistType>* p;//边表遍历指针
	for (i = 0; i < MaxNumVertex; i++) //初始化Ve数组
		Ve[i] = 0;
	for (i = 0; i < MaxNumVertex; i++) {//计算各结点最早开始时间(起点到该点最长距离)
		int m = TopoQueue[i];
		p = NodeTable[m].adj_first;//指向当前结点边表
		while (p != NULL) {
			k = p->dest;
			if (Ve[m] + p->cost > Ve[k])
				Ve[k] = Ve[m] + p->cost; 
			p = p->link;
		}
	}
	cout <<"最短项目用时："<< Ve[MaxNumVertex - 1] << endl;//输出完成整个项目所需最短时间
	for (i = 0; i < MaxNumVertex; i++)//初始化Vl数组为所有活动最短可能用时
		Vl[i] = Ve[MaxNumVertex - 1];
	for (i = MaxNumVertex - 2; i; i--) {//从倒数第二个点开始倒序计算各点最晚允许开始时间
		int m = TopoQueue[i];
		p = NodeTable[m].adj_first;
		while (p != NULL) {
			k = p->dest;
			if (Vl[k] - p->cost < Vl[m])
				Vl[m] = Vl[k] - p->cost;
			p = p->link;
		}
	}
	for (i = 0; i < MaxNumVertex; i++) {//查找关键活动
		int m = TopoQueue[i];
		p = NodeTable[m].adj_first;
		while (p != NULL) {
			k = p->dest;
			e = Ve[m]; 
			l = Vl[k] - p->cost;
			if (l == e)
				critical_path.push(path_edge(m, k));//符合条件的边加入关键路径
			p = p->link;
		}
	}
	//输出关键活动
	cout << "关键活动：" << endl;
	while (!critical_path.IsEmpty()) {
		path_edge l = critical_path.pop();//队头出列
		cout << NodeTable[l.src].name << "->" << NodeTable[l.dst].name << endl;
	}
}




int main()
{
	int N, M;//任务交接点数量N和子任务数量M
	cout << "欢迎来到求关键活动程序！" << endl;
	cout << "请输入任务交接点数量N和子任务数量M" << endl;
	while (1) {//输入工作
		cin >> N >> M;
		if (cin.fail() || N <= 0 || M <= 0 || N-1 > M) {
			cout << "输入错误，请重新输入！" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		else
			break;
	}
	Graph<int, int> activities(N);//创建一个图对象
	for (int i = 0; i < N; i++) //初始化结点数组各结点名
		activities.InsertVertex(i+1);
	cout << "请输入" << M << "个任务的开始和完成的交接点编号（1-"<<N<<"），以及完成该任务所需要的时间（三个整数）" << endl;
	for (int i = 0; i < M; i++) {//输入并插入M条边
		int start, dest;//起点、终点编号
		int time;//完成任务所需时间
		while(1) {//输入工作
			cin >> start >> dest>>time;
			if (cin.fail() || (start-1)*(start-N)>0 || (dest - 1) * (dest - N) > 0 || time<=0) {
				cout << "输入错误，请重新输入！" << endl;
				cin.clear();
				cin.ignore(100, '\n');
			}
			else
				break;
		}
		activities.InsertEdge(start, dest, time);//加入这条边
	}
	activities.CriticalPath();//求解并输出关键路径
	cout << "按回车键退出！" << endl;
	cin.ignore(100, '\n');
	while (getchar() != '\n')
		;
	return 0;
}
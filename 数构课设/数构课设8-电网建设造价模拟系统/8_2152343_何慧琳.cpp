#include <iostream>
#include <assert.h>
using namespace std;

const int MaxEdges = 50;
const int MaxVertices = 10;

class MSTEdgeNode;
class MinSpanTree;

template<class NameType,class DistType>//结点名数据类型，权值数据类型
class Graph {//用邻接矩阵表示的图的类定义
	friend class MinSpanTree;
public:
	Graph(int sz = MaxVertices);
	void InsertVertex(NameType& vertex);//插入顶点
	void InsertEdge(NameType v1, NameType v2, DistType weight);//插入以v1为起点，v2为终点，weight为权值的边
	void Prim(MinSpanTree& T,NameType start_name);
	int find(NameType name) { return VL.get_seq(name)>=0; }//图中是否存在name点
private:
	struct Vertex {//顶点结构体
		NameType name;//顶点名
		int seq;//顶点在顶点表中的序号
		Vertex* next;//链接指针，指向下一个结点
		Vertex(NameType N, int s, Vertex* n = NULL) :name(N), seq(s), next(n) {};
	};
	class VertexList {//顶点链表
		friend class MinSpanTree;
		friend class Graph;
		Vertex* first, * current;//结点指针
	public:
		VertexList(Vertex* f = NULL, Vertex* c = NULL) :first(f), current(c) {};//构造函数
		int get_seq(NameType name);//返回名为name结点的序号
		NameType operator [](int dex);//重载[]运算符取第i个元素名字
	};
	VertexList VL;//节点链表
	int VertexNum = 0;//结点个数
	DistType Edge[MaxVertices][MaxVertices];//邻接矩阵
	int CurrentEdges=0;//当前边数
};

template<class NameType, class DistType>
int Graph<NameType, DistType>::VertexList::get_seq(NameType name)
{//返回名为name结点的序号
	Vertex* temp = first;
	while (temp!=NULL&&strcmp(temp->name,name))
		temp = temp->next;
	if (temp)//temp不为空，找到该结点
		return temp->seq;
	else {
		cout << "结点不存在！"<<endl;
		return -1;
	}
}
template<class NameType,class DistType>
Graph<NameType, DistType>::Graph(int sz)
{//构造函数,初始化邻接矩阵
	for (int i = 0; i < sz; i++)
		for (int j = 0; j < sz; j++)
			Edge[i][j] = INT_MAX;
	CurrentEdges = 0;
}
template<class NameType, class DistType>
void Graph<NameType, DistType>::InsertVertex(NameType& vertex)
{//插入顶点
	if (!VertexNum) {//结点链表为空
		VL.first=VL.current = new Vertex(vertex, VertexNum);
	}
	else {
		VL.current->next = new Vertex(vertex, VertexNum);//在结点链表末尾加入新结点
		VL.current = VL.current->next;
	}
	VertexNum++;//结点个数+1
}
template<class NameType, class DistType>
void Graph<NameType, DistType>::InsertEdge(NameType v1, NameType v2, DistType weight)
{//插入以v1，v2为端点，weight为权值的边
	int i = VL.get_seq(v1);
	int j = VL.get_seq(v2);
	Edge[i][j] = weight;//在邻接表中更改权值
	Edge[j][i] = weight;
}
template<class NameType, class DistType>
NameType Graph<NameType, DistType>::VertexList::operator [](int dex)
{//获取第dex个元素name
	Vertex* temp = first;//游标指针开始指向first
	while (dex) {
		temp = temp->next;
		dex--;
	}
	return temp->name;
}



//最小生成树类定义
class MSTEdgeNode {//生成树边结点类定义
	friend class MinSpanTree;
	friend class Graph<char*,float>;
private:
	int tail, head;//生成树各边的两顶点
	float cost;//生成树各边的代价
	MSTEdgeNode() :tail(0), head(0), cost(0) {};
	MSTEdgeNode(MSTEdgeNode *mstedge) :tail(mstedge->tail), head(mstedge->head), cost(mstedge->cost) {};
};

class MinSpanTree {//生成树的类定义
public:
	MinSpanTree(int sz= MaxEdges) :MaxSize(sz), CurrentSize(0) { edgevalue = new MSTEdgeNode[MaxSize]; }
	void Insert(MSTEdgeNode &e);//插入一条边
	void print(Graph<char*,float> graph);//打印最小生成树
private:
	MSTEdgeNode* edgevalue;//边值数组
	int MaxSize, CurrentSize;//最大边数，当前边数
};

void MinSpanTree::Insert(MSTEdgeNode &e)
{ //插入一条边
	edgevalue[CurrentSize] = new MSTEdgeNode(e);
	CurrentSize++;//当前边数+1
}
void MinSpanTree::print(Graph<char*, float> graph)
{
	for (int i = 0; i < CurrentSize; i++) {
		int head_seq = edgevalue[i].head;
		int tail_seq = edgevalue[i].tail;
		cout <<graph.VL[head_seq]<< "-<" << edgevalue[i].cost << ">-" << graph.VL[tail_seq] <<"     ";
	}
	cout << endl;
}

template<class NameType,class DistType>
void Graph<NameType, DistType>::Prim(MinSpanTree& T,NameType start_name)
{//以start_name为起点用prim算法找到最小生成树放入T
	DistType *lowcost = new DistType[VertexNum];
	DistType* nearvex = new DistType[VertexNum];
	int start = VL.get_seq(start_name);
	for (int i = 0; i < VertexNum; i++) {
		lowcost[i] = Edge[start][i];//顶点到各边的代价
		nearvex[i] = start;//最短带权路径
	}
	nearvex[start] = -1;//顶点0加到生成树顶点集合
	MSTEdgeNode e;//最小生成树结点辅助单元
	for (int i = 0; i < VertexNum; i++) {//循环n-1次，加入n-1条边
		if (i == start)
			continue;
		DistType min = INT_MAX;//最短边长
		int v = start;
		for (int j = 0; j < VertexNum; j++) {
			//遍历更新，找到不在最小生成树顶点集合的到集合内点距离最短的顶点v及其距离min
			if (nearvex[j] != -1 && lowcost[j] < min) {
				v = j;
				min = lowcost[j];
			}
		}
		if (v != start) {//v==start表示再也找不到要求顶点了
			e.head = nearvex[v];
			e.tail = v;
			e.cost = lowcost[v];
			T.Insert(e);//选中的边加入生成树
			nearvex[v] = -1;//作该边已加入生成树标记
			for (int j = 0; j < VertexNum; j++) {
				//每新加入一个结点，更新一遍集合外结点到集合内结点的lowcost
				if (nearvex[j] != -1 && Edge[v][j] < lowcost[j]) {
					//j不在生成树中且原lowcost比j到新加入的点距离大，需要修改
					lowcost[j] = Edge[v][j];
					nearvex[j] = v;
				}
			}
		}
	}
}



int main()
{
	cout << "**          电网造价模拟系统          **" << endl;
	cout << "========================================" << endl;
	cout << "**          A---创建电网项点          **" << endl;
	cout << "**          B---添加电网的边          **" << endl;
	cout << "**          C---构造最小生成树        **" << endl;
	cout << "**          D---显示最小生成树        **" << endl;
	cout << "**          E---退出程序              **" << endl;
	cout << "========================================" << endl;
	cout << endl;
	char menu;//操作选项
	int num=MaxVertices;//顶点个数
	char* start=new char[20];//起点名
	Graph<char*, float> electricity_network;
	MinSpanTree T;//创建一个最小生成树对象
	while (1) {
	    cout << "请按顺序选择操作：";
		while (1) {//输入处理
			cin >> menu;
			if ((menu >= 'A' && menu <= 'E') || (menu >= 'a' && menu <= 'e')) {
				if (menu >= 'a' && menu <= 'e')
					menu -= 'a' - 'A';
				break;
			}
			else {
				cout << "输入错误，请重新输入！";
				cin.ignore(20, '\n');
			}
		}
		switch (menu) {
		case 'A': {
			cout << "请输入顶点的个数(小于10)：";
			while (1) {//输入处理
				cin >> num;
				if (cin.fail() || num <= 0) {
					cout << "输入错误，请重新输入！";
					cin.clear();
					cin.ignore(20, '\n');
				}
				else
					break;
			}
			cout << "请依次输入各顶点的名称：" << endl;
			for (int i = 0; i < num; i++) {
				char* name = new char[20];
				cin >> name;
				electricity_network.InsertVertex(name);//插入顶点
			}
			break;
		}
		case 'B': {
			int n = 0;//记录输入的边数
			char* v1=new char[20], * v2=new char[20];//两个顶点名
			float length;//边权
			cout << "输入电网中的边，以？ ？ 0结尾" << endl;
			while (1) {
				cout << "请输入两个顶点及边：";
				cin >> v1 >> v2 >> length;
				if (n >= num - 1 && *v1 == '?')
					break;
				else if (*v1 == '?') {
					cout << "边数不够，请继续输入至少" << num - 1 - n << "条边，以？ ？ 0结尾" << endl;
					continue;
				}
				assert(electricity_network.find(v1));
				assert(electricity_network.find(v2));
				electricity_network.InsertEdge(v1, v2, length);//插入边
				n++;
			}
			break;
		}
		case 'C':
			cout << "请输入起始顶点：";
			while (1) {
				cin >> start;
				if (electricity_network.find(start))
					break;
				else {
					cout << "请重新输入：";
					cin.ignore(100, '\n');
				}
			}
			electricity_network.Prim(T, start);
			cout << "生成Prim最小生成树！" << endl;
			break;
		case 'D':
			cout << "最小生成树的顶点及边为：" << endl;
			T.print(electricity_network);
			break;
		case 'E':
			cout << "程序结束!" << endl;
			return 0;
		}
		cout << endl;
	}
	return 0;
}
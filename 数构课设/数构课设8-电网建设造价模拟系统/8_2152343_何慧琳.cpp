#include <iostream>
#include <assert.h>
using namespace std;

const int MaxEdges = 50;
const int MaxVertices = 10;

class MSTEdgeNode;
class MinSpanTree;

template<class NameType,class DistType>//������������ͣ�Ȩֵ��������
class Graph {//���ڽӾ����ʾ��ͼ���ඨ��
	friend class MinSpanTree;
public:
	Graph(int sz = MaxVertices);
	void InsertVertex(NameType& vertex);//���붥��
	void InsertEdge(NameType v1, NameType v2, DistType weight);//������v1Ϊ��㣬v2Ϊ�յ㣬weightΪȨֵ�ı�
	void Prim(MinSpanTree& T,NameType start_name);
	int find(NameType name) { return VL.get_seq(name)>=0; }//ͼ���Ƿ����name��
private:
	struct Vertex {//����ṹ��
		NameType name;//������
		int seq;//�����ڶ�����е����
		Vertex* next;//����ָ�룬ָ����һ�����
		Vertex(NameType N, int s, Vertex* n = NULL) :name(N), seq(s), next(n) {};
	};
	class VertexList {//��������
		friend class MinSpanTree;
		friend class Graph;
		Vertex* first, * current;//���ָ��
	public:
		VertexList(Vertex* f = NULL, Vertex* c = NULL) :first(f), current(c) {};//���캯��
		int get_seq(NameType name);//������Ϊname�������
		NameType operator [](int dex);//����[]�����ȡ��i��Ԫ������
	};
	VertexList VL;//�ڵ�����
	int VertexNum = 0;//������
	DistType Edge[MaxVertices][MaxVertices];//�ڽӾ���
	int CurrentEdges=0;//��ǰ����
};

template<class NameType, class DistType>
int Graph<NameType, DistType>::VertexList::get_seq(NameType name)
{//������Ϊname�������
	Vertex* temp = first;
	while (temp!=NULL&&strcmp(temp->name,name))
		temp = temp->next;
	if (temp)//temp��Ϊ�գ��ҵ��ý��
		return temp->seq;
	else {
		cout << "��㲻���ڣ�"<<endl;
		return -1;
	}
}
template<class NameType,class DistType>
Graph<NameType, DistType>::Graph(int sz)
{//���캯��,��ʼ���ڽӾ���
	for (int i = 0; i < sz; i++)
		for (int j = 0; j < sz; j++)
			Edge[i][j] = INT_MAX;
	CurrentEdges = 0;
}
template<class NameType, class DistType>
void Graph<NameType, DistType>::InsertVertex(NameType& vertex)
{//���붥��
	if (!VertexNum) {//�������Ϊ��
		VL.first=VL.current = new Vertex(vertex, VertexNum);
	}
	else {
		VL.current->next = new Vertex(vertex, VertexNum);//�ڽ������ĩβ�����½��
		VL.current = VL.current->next;
	}
	VertexNum++;//������+1
}
template<class NameType, class DistType>
void Graph<NameType, DistType>::InsertEdge(NameType v1, NameType v2, DistType weight)
{//������v1��v2Ϊ�˵㣬weightΪȨֵ�ı�
	int i = VL.get_seq(v1);
	int j = VL.get_seq(v2);
	Edge[i][j] = weight;//���ڽӱ��и���Ȩֵ
	Edge[j][i] = weight;
}
template<class NameType, class DistType>
NameType Graph<NameType, DistType>::VertexList::operator [](int dex)
{//��ȡ��dex��Ԫ��name
	Vertex* temp = first;//�α�ָ�뿪ʼָ��first
	while (dex) {
		temp = temp->next;
		dex--;
	}
	return temp->name;
}



//��С�������ඨ��
class MSTEdgeNode {//�������߽���ඨ��
	friend class MinSpanTree;
	friend class Graph<char*,float>;
private:
	int tail, head;//���������ߵ�������
	float cost;//���������ߵĴ���
	MSTEdgeNode() :tail(0), head(0), cost(0) {};
	MSTEdgeNode(MSTEdgeNode *mstedge) :tail(mstedge->tail), head(mstedge->head), cost(mstedge->cost) {};
};

class MinSpanTree {//���������ඨ��
public:
	MinSpanTree(int sz= MaxEdges) :MaxSize(sz), CurrentSize(0) { edgevalue = new MSTEdgeNode[MaxSize]; }
	void Insert(MSTEdgeNode &e);//����һ����
	void print(Graph<char*,float> graph);//��ӡ��С������
private:
	MSTEdgeNode* edgevalue;//��ֵ����
	int MaxSize, CurrentSize;//����������ǰ����
};

void MinSpanTree::Insert(MSTEdgeNode &e)
{ //����һ����
	edgevalue[CurrentSize] = new MSTEdgeNode(e);
	CurrentSize++;//��ǰ����+1
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
{//��start_nameΪ�����prim�㷨�ҵ���С����������T
	DistType *lowcost = new DistType[VertexNum];
	DistType* nearvex = new DistType[VertexNum];
	int start = VL.get_seq(start_name);
	for (int i = 0; i < VertexNum; i++) {
		lowcost[i] = Edge[start][i];//���㵽���ߵĴ���
		nearvex[i] = start;//��̴�Ȩ·��
	}
	nearvex[start] = -1;//����0�ӵ����������㼯��
	MSTEdgeNode e;//��С��������㸨����Ԫ
	for (int i = 0; i < VertexNum; i++) {//ѭ��n-1�Σ�����n-1����
		if (i == start)
			continue;
		DistType min = INT_MAX;//��̱߳�
		int v = start;
		for (int j = 0; j < VertexNum; j++) {
			//�������£��ҵ�������С���������㼯�ϵĵ������ڵ������̵Ķ���v�������min
			if (nearvex[j] != -1 && lowcost[j] < min) {
				v = j;
				min = lowcost[j];
			}
		}
		if (v != start) {//v==start��ʾ��Ҳ�Ҳ���Ҫ�󶥵���
			e.head = nearvex[v];
			e.tail = v;
			e.cost = lowcost[v];
			T.Insert(e);//ѡ�еı߼���������
			nearvex[v] = -1;//���ñ��Ѽ������������
			for (int j = 0; j < VertexNum; j++) {
				//ÿ�¼���һ����㣬����һ�鼯�����㵽�����ڽ���lowcost
				if (nearvex[j] != -1 && Edge[v][j] < lowcost[j]) {
					//j��������������ԭlowcost��j���¼���ĵ�������Ҫ�޸�
					lowcost[j] = Edge[v][j];
					nearvex[j] = v;
				}
			}
		}
	}
}



int main()
{
	cout << "**          �������ģ��ϵͳ          **" << endl;
	cout << "========================================" << endl;
	cout << "**          A---�����������          **" << endl;
	cout << "**          B---��ӵ����ı�          **" << endl;
	cout << "**          C---������С������        **" << endl;
	cout << "**          D---��ʾ��С������        **" << endl;
	cout << "**          E---�˳�����              **" << endl;
	cout << "========================================" << endl;
	cout << endl;
	char menu;//����ѡ��
	int num=MaxVertices;//�������
	char* start=new char[20];//�����
	Graph<char*, float> electricity_network;
	MinSpanTree T;//����һ����С����������
	while (1) {
	    cout << "�밴˳��ѡ�������";
		while (1) {//���봦��
			cin >> menu;
			if ((menu >= 'A' && menu <= 'E') || (menu >= 'a' && menu <= 'e')) {
				if (menu >= 'a' && menu <= 'e')
					menu -= 'a' - 'A';
				break;
			}
			else {
				cout << "����������������룡";
				cin.ignore(20, '\n');
			}
		}
		switch (menu) {
		case 'A': {
			cout << "�����붥��ĸ���(С��10)��";
			while (1) {//���봦��
				cin >> num;
				if (cin.fail() || num <= 0) {
					cout << "����������������룡";
					cin.clear();
					cin.ignore(20, '\n');
				}
				else
					break;
			}
			cout << "�������������������ƣ�" << endl;
			for (int i = 0; i < num; i++) {
				char* name = new char[20];
				cin >> name;
				electricity_network.InsertVertex(name);//���붥��
			}
			break;
		}
		case 'B': {
			int n = 0;//��¼����ı���
			char* v1=new char[20], * v2=new char[20];//����������
			float length;//��Ȩ
			cout << "��������еıߣ��ԣ� �� 0��β" << endl;
			while (1) {
				cout << "�������������㼰�ߣ�";
				cin >> v1 >> v2 >> length;
				if (n >= num - 1 && *v1 == '?')
					break;
				else if (*v1 == '?') {
					cout << "�����������������������" << num - 1 - n << "���ߣ��ԣ� �� 0��β" << endl;
					continue;
				}
				assert(electricity_network.find(v1));
				assert(electricity_network.find(v2));
				electricity_network.InsertEdge(v1, v2, length);//�����
				n++;
			}
			break;
		}
		case 'C':
			cout << "��������ʼ���㣺";
			while (1) {
				cin >> start;
				if (electricity_network.find(start))
					break;
				else {
					cout << "���������룺";
					cin.ignore(100, '\n');
				}
			}
			electricity_network.Prim(T, start);
			cout << "����Prim��С��������" << endl;
			break;
		case 'D':
			cout << "��С�������Ķ��㼰��Ϊ��" << endl;
			T.print(electricity_network);
			break;
		case 'E':
			cout << "�������!" << endl;
			return 0;
		}
		cout << endl;
	}
	return 0;
}
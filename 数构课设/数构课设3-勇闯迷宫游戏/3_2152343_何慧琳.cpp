#include <iostream>
using namespace std;
template <class Type> class Queue;
template <class Type>
class QueueNode {//���н����
	friend class Queue<Type>;
	friend class Map;
	Type data;//���н������
	QueueNode* link;//�����ָ��
	QueueNode() :link(NULL) {};//Ĭ�Ϲ��캯��
	QueueNode(Type d, QueueNode* l = NULL) :data(d), link(l) {}//�������Ĺ��캯��
};
template <class Type>
class Queue {//����
public:
	Queue() :rear(NULL), front(NULL) {}//���й��캯��
	~Queue();//������������
	void push(const Type item);//��dataΪitem�Ľ��������
	Type pop();//ɾ����ͷ���
	QueueNode<Type>* top();//ȡ����ͷ���
	QueueNode<Type>* operator[](int i);//���ص�i+1�����
	void MakeEmpty();//�������ÿ�
	int IsEmpty()const { return front == NULL; }//�ж϶����Ƿ�Ϊ��
private:
	QueueNode<Type>* front, * rear;//����ͷָ���βָ��
};
template <class Type> Queue<Type>::~Queue()
{
	MakeEmpty();
}
template <class Type> void Queue<Type>::push(const Type item)
{//����itemΪdata���½����뵽���еĶ�β
	if (front == NULL)//�ӿգ�������һ�����
		front = rear = new QueueNode<Type>(item);
	else//���в��գ�����
		rear = rear->link = new QueueNode<Type>(item);
}
template <class Type> Type Queue<Type>::pop()
{//ɾȥͷ�ڵ㣬�����ض�ͷԪ�ص�ֵ
	Type error;
	if (!IsEmpty()) {//�ӷǿ�
		QueueNode<Type>* temp = front;
		Type value = temp->data;//�����ͷ��ֵ
		front = front->link;//�¶�ͷ
		delete temp;//�ͷ�ԭ��ͷ���
		return value;
	}
	else
		return error;
}
template <class Type> QueueNode<Type>* Queue<Type>::top()
{//���Ӳ��գ��������ض�ͷԪ�ص�ֵ; ���ӿգ���������0
	if (!IsEmpty())//�ӷǿ�
		return front;
	else//�ӿ�
		return 0;
}
template <class Type> QueueNode<Type>* Queue<Type>::operator[](int i)
{//ȡ��i+1�����
	QueueNode<Type>* p;
	if (i < 0) {
		p = new QueueNode<Type>;
		return p;//���ؿս��
	}
	p = top();//���ָ��ָ���ͷ���
	while (p&&i) {//��ǰ��㲻Ϊ����i>0
		p = p->link;//���ָ��ָ����һ�����
		i--;
	}
	if (i) {//i����0,�������ѷ�����
		cout << "��"<<i+1<<"����㲻����!" << endl;
		p = new QueueNode<Type>;
		return p;//���ؿս��
	}
	return p;//���ص�ǰ���
}
template <class Type> void Queue<Type>::MakeEmpty()
{
	QueueNode<Type>* current;
	while (front != NULL) {//��ǰ�����������ͷ�
		current = front;
		front = front->link;
		delete current;
	}
}

template <class Type>
class MyMatrix {//��ά������Ķ���
	friend class Map;
	Type** elements; //����Ԫ�ش�ſռ�
	int colSize; //��ǰ�����еĴ�С
	int rowSize; //��ǰ�����Ĵ�С
public:
	MyMatrix() :elements(NULL),colSize(INT_MAX),rowSize(INT_MAX) {};//�޲ι��캯��
	MyMatrix(int rowsz,int colsz,Type **elmts=NULL);//���캯��
	MyMatrix(const MyMatrix<Type>& Matrix);//���ƹ��캯��
	~MyMatrix();//��������
	void getMatrix(int rowsz=0,int colsz=0); //��������ռ�ͬʱ����������ʱδ��ʼ��rowSIze��colSize���ڴ˿ɸ����Ǹ���Чֵ
	Type* operator [ ](int i) const;//ȡԪ��ֵ
};
template<class Type> void MyMatrix<Type>::getMatrix(int rowsz, int colsz)
{//������ά����洢�ռ䣬ͬʱ�ɸ�rowSize��colSize����Чֵ
	if (rowsz && colsz) {//rowsz��colszֵ��Ч���������ǳ�ʼ��rowSize��colSize
		rowSize = rowsz;
		colSize = colsz;
	}
	if (rowSize <= 0 || colSize <= 0)
		return;
	elements = new Type * [rowSize];//����rowSize���пռ�
	for(int i=0;i<rowSize;i++){//���п���colSize���пռ�(��β��)
	    elements[i]= new Type[colSize+1];
	}
}
template<class Type> MyMatrix<Type>::MyMatrix(int rowsz, int colsz, Type** elmts)
{//���캯��
	if (rowsz <= 0 || colsz <= 0) {
		cout << "�Ƿ������С" << endl;
		return;
	}
	rowSize = rowsz;
	colSize = colsz;
	getMatrix();//���پ���ռ�
	if (elmts != NULL) {//�Ծ����е�Ԫ�������ֵ
		for(int i=0;i<rowSize;i++)
		    for(int j=0;j<colSize+1;j++)
				elements[i][j] = elmts[i][j];
	}
}
template<class Type> MyMatrix<Type>::MyMatrix(const MyMatrix<Type>& Matrix)
{//���ƹ��캯��
	colSize = Matrix.colSize;
	rowSize = Matrix.rowSize;
	getMatrix();//���پ���ռ�
	for (int i = 0; i < rowSize; i++)//�Ծ����е�Ԫ�������ֵ
		for (int j = 0; j < colSize+1; j++)
			elements[i][j] = Matrix.elements[i][j];
}
template<class Type> MyMatrix<Type>::~MyMatrix()//��������
{
	for (int i = 0; i < rowSize; i++)
		delete[]elements[i];
	delete[]elements;
}
template<class Type>Type* MyMatrix<Type>::operator[ ](int i) const
{//���±꣨i��j��ȡ����Ԫ�ص�ֵ
	return elements[i];
}

class Map {//��ͼ��
public:
	Map(int ro, int co, int en_x, int en_y, int ex_x, int ex_y, MyMatrix<char> matrix);//���캯��
	Map(const Map& copymap);//���ƹ��캯��
	void EnMap(char val, int y, int x) { map_matrix[y][x] = val; };//��ֵval����map[y][x]
	void print();//��ӡ��ͼ
	void find_path();//�Ҵ���ڵ����ڵ����·��
	struct coordinate {//����
		int x, y;//����
		int step;//����ĳ��ʱ�Ĳ���
		coordinate(int x1=0,int y1=0,int step1=0) :x(x1), y(y1),step(step1) {}//���캯��
	};
private:
	
	int row, col;//����������
	int entrance_x, entrance_y, exit_x, exit_y;//��ںͳ��ڵ�����
	MyMatrix<char> map_matrix;//Map���ڲ�����
	Queue<coordinate> path;//�洢·���Ķ���
};
Map::Map(int ro, int co, int en_x, int en_y, int ex_x, int ex_y,MyMatrix<char> matrix)
{
	row = ro;
	col = co;
	entrance_x = en_x;
	entrance_y = en_y;
	exit_x = ex_x;
	exit_y = ex_y;
	map_matrix =* new MyMatrix<char>(matrix);//��matrix���Ƹ�map_matrix
}
Map::Map(const Map& copymap)
{//���ƹ��캯��
	row = copymap.row;
	col = copymap.col;
	entrance_x = copymap.entrance_x;
	entrance_y = copymap.entrance_y;
	exit_x = copymap.exit_x;
	exit_y = copymap.exit_y;
	map_matrix.getMatrix(row, col);//�����ȴ�С�ľ���
	for (int i = 0; i < row; i++)//��copymap�ľ����е�Ԫ����һ���Ƹ�this�еľ���
		for (int j = 0; j < col; j++)
			map_matrix[i][j] = copymap.map_matrix[i][j];
}
void Map::print()
{//��ӡ��ͼ
	int i, j;
	cout << "     ";
	for (j = 0; j < col; j++) //��ӡ��������
		cout << j << "��  ";
	cout << endl;
	for (i = 0; i < row; i++) {//���д�ӡ����Ԫ��
		cout << i << "��  ";
		for (j = 0; j < col; j++)
			cout << map_matrix[i][j]<<"    ";
		cout << endl;
	}
	cout << endl;
}
void Map::find_path()
{//�Ҵ���ڵ����ڵ����·��(�����������)
	coordinate *current=new coordinate(entrance_x, entrance_y,1);//��ǰλ��ָ��ָ�����λ��,��ʼ����Ϊ1
	path.push(*current);//���λ����ջ
	int find = 0;//�Ƿ��ҵ��յ���
	int n = 0;//����path��Ľ�����
	int i, j;
	MyMatrix<int> mark(row, col);//������Ǿ��󣬱��ĳλ���Ƿ��߹�����Ӧλ��Ԫ�ص�ֵΪ������λ��ʱ�Ĳ���
	for (i = 0; i < row; i++)//��ʼ����Ǿ���
		for (j = 0; j < col; j++)
			mark[i][j] = 0;
	while (path.top()!=NULL) {
		*current = path.top()->data;//ȡ��ͷ����ֵ�����꣩
		int step = current->step;//ȡ��ǰ�ڵ��߹��Ĳ���
		path.pop();//��ͷ������
	    int x = current->x;
	    int y = current->y;
		mark[y][x] = step;
		if (x == exit_x && y == exit_y) {//�ҵ��յ�
			find = 1;//����find���
			path.MakeEmpty();//path�����ÿ�
			path.push(*current);//��ǰλ�ý�㣨�յ�)���
			n++;//��������1
			while (step>0) {//���ݲ����ݼ�����֮ǰ������·���������·������λ�ô���path
				step--;
				map_matrix[y][x] = '*';//�����·������λ����map�����б�ǳ���
				if (step == 1)
					break;
				if (y>0&&mark[y - 1][x] == step) {
					path.push(coordinate(x, y - 1));
					y -= 1;
				}
				else if (y<row&&mark[y + 1][x] == step) {
					path.push(coordinate(x, y + 1));
					y += 1;
				}
				else if (x>0&&mark[y][x - 1] == step) {
					path.push(coordinate(x - 1, y));
					x -= 1;
				}
				else if (x<col&&mark[y][x + 1] == step) {
					path.push(coordinate(x + 1, y));
					x += 1;
				}
				n++;
			}
			break;//�˳�ѭ��
		}
		if (y > 0 && map_matrix[y - 1][x] != '#'&&mark[y-1][x]==0) {//���Ͽ���
			path.push(coordinate(x, y - 1, step + 1));//�����λ�����
		}
		if (y < row - 1 && map_matrix[y + 1][x] != '#' && mark[y + 1][x] == 0) {//���¿���
			path.push(coordinate(x, y + 1, step + 1));//�����λ�����
		}
		if (x > 0 && map_matrix[y ][x-1] != '#' && mark[y][x - 1] == 0) {//�������
			path.push(coordinate(x - 1, y, step + 1));//��ߵ�λ�����
		}
		if (x < col-1 && map_matrix[y][x + 1] != '#' && mark[y][x + 1] == 0){//���ҿ���
			path.push(coordinate(x + 1, y, step + 1));//�ұߵ�λ�����
		}
	}
	delete current;
	if (!find) {//û�ҵ��յ�
		cout << "��㵽�յ�䲻����ͨ·��" << endl;
		return;
	}
	else {//�ҵ��յ㣬��ӡ·����ͼ
		cout << "·����ͼ��" << endl;
		cout << "     ";
		for (j = 0; j < col; j++) {
			cout << j << "��  ";
		}
		cout << endl;
		for (i = 0; i < row; i++) {
			cout << i << "��  ";
			for (j = 0; j < col; j++) {
				cout << map_matrix[i][j] << "    ";
			}
			cout << endl;
		}
		cout << endl;
		cout << "�Թ�·����" << endl;
		cout << "<" << entrance_x << "," << entrance_y << ">-->";
		for (n-=1; n >= 0; n--) {//��ӡ�Թ�·������
			int x = path[n]->data.x;
			int y = path[n]->data.y;
			cout << "<" << y << "," << x << ">";
			if (n)//��ǰ��ӡ�����겻�����һ��
				cout << "-->";
		}
		cout << endl;
		cout << endl;
	}
}

//�Թ�1
char **elements1 =new char*[7]
{new char[8]{'#','#','#','#','#','#','#','\0'},
 new char[8]{'#','0','#','0','0','0','#','\0'},
 new char[8]{'#','0','#','0','#','#','#','\0'},
 new char[8]{'#','0','0','0','#','0','#','\0'},
 new char[8]{'#','0','#','0','0','0','#','\0'},
 new char[8]{'#','0','#','0','#','0','#','\0'},
 new char[8]{'#','#','#','#','#','#','#','\0'} };
MyMatrix<char> map_matrix1(7, 7,elements1);//��ͼ����1
Map map1(7,7,1,1,5,5,map_matrix1);//��ͼ1

//�Թ�2
char** elements2 = new char* [9]
{new char[10] {'0','0','0','#','0','0','0','0','0','\0'},
 new char[10] {'0','#','0','#','#','#','#','#','0','\0'},
 new char[10] {'0','#','0','0','0','0','0','#','0','\0'},
 new char[10] {'0','#','#','#','#','#','0','#','0','\0'},
 new char[10] {'0','#','0','0','0','#','0','0','0','\0'},
 new char[10] {'0','#','0','#','#','#','#','#','0','\0'},
 new char[10] {'0','#','0','0','0','#','0','#','0','\0'},
 new char[10] {'0','#','#','#','0','#','0','#','0','\0'},
 new char[10] {'0','0','0','0','0','#','0','0','0','\0'}};
MyMatrix<char> map_matrix2(9, 9, elements2);//��ͼ����2
Map map2(9, 9, 0, 0, 8, 8, map_matrix2);//��ͼ2

//�Թ�3
char** elements3 = new char* [5]
{new char[] {'0','0','0','#','0','\0'},
 new char[] {'0','#','0','#','#','\0'},
 new char[] {'0','#','0','0','0','\0'},
 new char[] {'0','#','#','#','#','\0'},
 new char[] {'0','#','0','0','0','\0'} };
MyMatrix<char> map_matrix3(5, 5, elements3);//��ͼ����3
Map map3(5, 5, 0, 0, 4, 4, map_matrix3);//��ͼ3

int main()
{
	cout << "��ӭ�����Թ���ʾ�棬�������Թ���׼�����밴�س�����" << endl;
	while (getchar() != '\n')
		;
	cout << "�Թ�1 ��ڣ�1��1�� ���ڣ�5��5����" << endl;
	map1.print();
	map1.find_path();
	delete[]elements1;
	cout << "���س���������" << endl;
	while (getchar() != '\n')
		;
	cout << "�Թ�2 ��ڣ�0.0�� ���ڣ�8.8����" << endl;
	map2.print();
	map2.find_path();
	delete[]elements2;
	cout << "���س���������" << endl;
	while (getchar() != '\n')
		;
	cout << "�Թ�3 ��ڣ�0.0�� ���ڣ�4.4����" << endl;
	map3.print();
	map3.find_path();
	delete[]elements3;
	cout << "���س���������" << endl;
	while (getchar() != '\n')
	return 0;
}
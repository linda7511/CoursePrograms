#include <iostream>
using namespace std;
template <class Type> class Queue;
template <class Type>
class QueueNode {//队列结点类
	friend class Queue<Type>;
	friend class Map;
	Type data;//队列结点数据
	QueueNode* link;//结点链指针
	QueueNode() :link(NULL) {};//默认构造函数
	QueueNode(Type d, QueueNode* l = NULL) :data(d), link(l) {}//带参数的构造函数
};
template <class Type>
class Queue {//队列
public:
	Queue() :rear(NULL), front(NULL) {}//队列构造函数
	~Queue();//队列析构函数
	void push(const Type item);//将data为item的结点加入队列
	Type pop();//删除队头结点
	QueueNode<Type>* top();//取出队头结点
	QueueNode<Type>* operator[](int i);//返回第i+1个结点
	void MakeEmpty();//将队列置空
	int IsEmpty()const { return front == NULL; }//判断队列是否为空
private:
	QueueNode<Type>* front, * rear;//队列头指针和尾指针
};
template <class Type> Queue<Type>::~Queue()
{
	MakeEmpty();
}
template <class Type> void Queue<Type>::push(const Type item)
{//将以item为data的新结点插入到队列的队尾
	if (front == NULL)//队空，创建第一个结点
		front = rear = new QueueNode<Type>(item);
	else//队列不空，插入
		rear = rear->link = new QueueNode<Type>(item);
}
template <class Type> Type Queue<Type>::pop()
{//删去头节点，并返回队头元素的值
	Type error;
	if (!IsEmpty()) {//队非空
		QueueNode<Type>* temp = front;
		Type value = temp->data;//保存队头的值
		front = front->link;//新队头
		delete temp;//释放原队头结点
		return value;
	}
	else
		return error;
}
template <class Type> QueueNode<Type>* Queue<Type>::top()
{//若队不空，则函数返回队头元素的值; 若队空，则函数返回0
	if (!IsEmpty())//队非空
		return front;
	else//队空
		return 0;
}
template <class Type> QueueNode<Type>* Queue<Type>::operator[](int i)
{//取第i+1个结点
	QueueNode<Type>* p;
	if (i < 0) {
		p = new QueueNode<Type>;
		return p;//返回空结点
	}
	p = top();//检测指针指向队头结点
	while (p&&i) {//当前结点不为空且i>0
		p = p->link;//检测指针指向下一个结点
		i--;
	}
	if (i) {//i大于0,而队列已访问完
		cout << "第"<<i+1<<"个结点不存在!" << endl;
		p = new QueueNode<Type>;
		return p;//返回空结点
	}
	return p;//返回当前结点
}
template <class Type> void Queue<Type>::MakeEmpty()
{
	QueueNode<Type>* current;
	while (front != NULL) {//从前往后逐个结点释放
		current = front;
		front = front->link;
		delete current;
	}
}

template <class Type>
class MyMatrix {//二维数组类的定义
	friend class Map;
	Type** elements; //数组元素存放空间
	int colSize; //当前数组列的大小
	int rowSize; //当前数组宽的大小
public:
	MyMatrix() :elements(NULL),colSize(INT_MAX),rowSize(INT_MAX) {};//无参构造函数
	MyMatrix(int rowsz,int colsz,Type **elmts=NULL);//构造函数
	MyMatrix(const MyMatrix<Type>& Matrix);//复制构造函数
	~MyMatrix();//析构函数
	void getMatrix(int rowsz=0,int colsz=0); //建立数组空间同时若声明对象时未初始化rowSIze和colSize则在此可给它们赋有效值
	Type* operator [ ](int i) const;//取元素值
};
template<class Type> void MyMatrix<Type>::getMatrix(int rowsz, int colsz)
{//创建二维数组存储空间，同时可给rowSize，colSize赋有效值
	if (rowsz && colsz) {//rowsz、colsz值有效，则用它们初始化rowSize、colSize
		rowSize = rowsz;
		colSize = colsz;
	}
	if (rowSize <= 0 || colSize <= 0)
		return;
	elements = new Type * [rowSize];//开辟rowSize个行空间
	for(int i=0;i<rowSize;i++){//逐行开辟colSize个列空间(含尾零)
	    elements[i]= new Type[colSize+1];
	}
}
template<class Type> MyMatrix<Type>::MyMatrix(int rowsz, int colsz, Type** elmts)
{//构造函数
	if (rowsz <= 0 || colsz <= 0) {
		cout << "非法数组大小" << endl;
		return;
	}
	rowSize = rowsz;
	colSize = colsz;
	getMatrix();//开辟矩阵空间
	if (elmts != NULL) {//对矩阵中的元素逐个赋值
		for(int i=0;i<rowSize;i++)
		    for(int j=0;j<colSize+1;j++)
				elements[i][j] = elmts[i][j];
	}
}
template<class Type> MyMatrix<Type>::MyMatrix(const MyMatrix<Type>& Matrix)
{//复制构造函数
	colSize = Matrix.colSize;
	rowSize = Matrix.rowSize;
	getMatrix();//开辟矩阵空间
	for (int i = 0; i < rowSize; i++)//对矩阵中的元素逐个赋值
		for (int j = 0; j < colSize+1; j++)
			elements[i][j] = Matrix.elements[i][j];
}
template<class Type> MyMatrix<Type>::~MyMatrix()//析构函数
{
	for (int i = 0; i < rowSize; i++)
		delete[]elements[i];
	delete[]elements;
}
template<class Type>Type* MyMatrix<Type>::operator[ ](int i) const
{//按下标（i，j）取数组元素的值
	return elements[i];
}

class Map {//地图类
public:
	Map(int ro, int co, int en_x, int en_y, int ex_x, int ex_y, MyMatrix<char> matrix);//构造函数
	Map(const Map& copymap);//复制构造函数
	void EnMap(char val, int y, int x) { map_matrix[y][x] = val; };//将值val赋给map[y][x]
	void print();//打印地图
	void find_path();//找从入口到出口的最短路径
	struct coordinate {//坐标
		int x, y;//坐标
		int step;//经过某点时的步数
		coordinate(int x1=0,int y1=0,int step1=0) :x(x1), y(y1),step(step1) {}//构造函数
	};
private:
	
	int row, col;//行数和列数
	int entrance_x, entrance_y, exit_x, exit_y;//入口和出口的坐标
	MyMatrix<char> map_matrix;//Map的内部矩阵
	Queue<coordinate> path;//存储路径的队列
};
Map::Map(int ro, int co, int en_x, int en_y, int ex_x, int ex_y,MyMatrix<char> matrix)
{
	row = ro;
	col = co;
	entrance_x = en_x;
	entrance_y = en_y;
	exit_x = ex_x;
	exit_y = ex_y;
	map_matrix =* new MyMatrix<char>(matrix);//将matrix复制给map_matrix
}
Map::Map(const Map& copymap)
{//复制构造函数
	row = copymap.row;
	col = copymap.col;
	entrance_x = copymap.entrance_x;
	entrance_y = copymap.entrance_y;
	exit_x = copymap.exit_x;
	exit_y = copymap.exit_y;
	map_matrix.getMatrix(row, col);//创建等大小的矩阵
	for (int i = 0; i < row; i++)//将copymap的矩阵中的元素逐一复制给this中的矩阵
		for (int j = 0; j < col; j++)
			map_matrix[i][j] = copymap.map_matrix[i][j];
}
void Map::print()
{//打印地图
	int i, j;
	cout << "     ";
	for (j = 0; j < col; j++) //打印首行坐标
		cout << j << "列  ";
	cout << endl;
	for (i = 0; i < row; i++) {//逐行打印各行元素
		cout << i << "行  ";
		for (j = 0; j < col; j++)
			cout << map_matrix[i][j]<<"    ";
		cout << endl;
	}
	cout << endl;
}
void Map::find_path()
{//找从入口到出口的最短路径(广度优先搜索)
	coordinate *current=new coordinate(entrance_x, entrance_y,1);//当前位置指针指向起点位置,起始步数为1
	path.push(*current);//起点位置入栈
	int find = 0;//是否找到终点标记
	int n = 0;//最终path里的结点个数
	int i, j;
	MyMatrix<int> mark(row, col);//创建标记矩阵，标记某位置是否走过，对应位置元素的值为经过该位置时的步数
	for (i = 0; i < row; i++)//初始化标记矩阵
		for (j = 0; j < col; j++)
			mark[i][j] = 0;
	while (path.top()!=NULL) {
		*current = path.top()->data;//取队头结点的值（坐标）
		int step = current->step;//取当前节点走过的步数
		path.pop();//队头结点出队
	    int x = current->x;
	    int y = current->y;
		mark[y][x] = step;
		if (x == exit_x && y == exit_y) {//找到终点
			find = 1;//更改find标记
			path.MakeEmpty();//path队列置空
			path.push(*current);//当前位置结点（终点)入队
			n++;//结点个数加1
			while (step>0) {//根据步数递减回溯之前经过的路径，将最短路径所经位置存入path
				step--;
				map_matrix[y][x] = '*';//将最短路径所经位置在map矩阵中标记出来
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
			break;//退出循环
		}
		if (y > 0 && map_matrix[y - 1][x] != '#'&&mark[y-1][x]==0) {//向上可走
			path.push(coordinate(x, y - 1, step + 1));//上面的位置入队
		}
		if (y < row - 1 && map_matrix[y + 1][x] != '#' && mark[y + 1][x] == 0) {//向下可走
			path.push(coordinate(x, y + 1, step + 1));//下面的位置入队
		}
		if (x > 0 && map_matrix[y ][x-1] != '#' && mark[y][x - 1] == 0) {//向左可走
			path.push(coordinate(x - 1, y, step + 1));//左边的位置入队
		}
		if (x < col-1 && map_matrix[y][x + 1] != '#' && mark[y][x + 1] == 0){//向右可走
			path.push(coordinate(x + 1, y, step + 1));//右边的位置入队
		}
	}
	delete current;
	if (!find) {//没找到终点
		cout << "起点到终点间不存在通路！" << endl;
		return;
	}
	else {//找到终点，打印路径地图
		cout << "路径地图：" << endl;
		cout << "     ";
		for (j = 0; j < col; j++) {
			cout << j << "列  ";
		}
		cout << endl;
		for (i = 0; i < row; i++) {
			cout << i << "行  ";
			for (j = 0; j < col; j++) {
				cout << map_matrix[i][j] << "    ";
			}
			cout << endl;
		}
		cout << endl;
		cout << "迷宫路径：" << endl;
		cout << "<" << entrance_x << "," << entrance_y << ">-->";
		for (n-=1; n >= 0; n--) {//打印迷宫路径坐标
			int x = path[n]->data.x;
			int y = path[n]->data.y;
			cout << "<" << y << "," << x << ">";
			if (n)//当前打印的坐标不是最后一个
				cout << "-->";
		}
		cout << endl;
		cout << endl;
	}
}

//迷宫1
char **elements1 =new char*[7]
{new char[8]{'#','#','#','#','#','#','#','\0'},
 new char[8]{'#','0','#','0','0','0','#','\0'},
 new char[8]{'#','0','#','0','#','#','#','\0'},
 new char[8]{'#','0','0','0','#','0','#','\0'},
 new char[8]{'#','0','#','0','0','0','#','\0'},
 new char[8]{'#','0','#','0','#','0','#','\0'},
 new char[8]{'#','#','#','#','#','#','#','\0'} };
MyMatrix<char> map_matrix1(7, 7,elements1);//地图矩阵1
Map map1(7,7,1,1,5,5,map_matrix1);//地图1

//迷宫2
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
MyMatrix<char> map_matrix2(9, 9, elements2);//地图矩阵2
Map map2(9, 9, 0, 0, 8, 8, map_matrix2);//地图2

//迷宫3
char** elements3 = new char* [5]
{new char[] {'0','0','0','#','0','\0'},
 new char[] {'0','#','0','#','#','\0'},
 new char[] {'0','#','0','0','0','\0'},
 new char[] {'0','#','#','#','#','\0'},
 new char[] {'0','#','0','0','0','\0'} };
MyMatrix<char> map_matrix3(5, 5, elements3);//地图矩阵3
Map map3(5, 5, 0, 0, 4, 4, map_matrix3);//地图3

int main()
{
	cout << "欢迎来到迷宫演示版，共三个迷宫，准备好请按回车键！" << endl;
	while (getchar() != '\n')
		;
	cout << "迷宫1 入口（1，1） 出口（5，5）：" << endl;
	map1.print();
	map1.find_path();
	delete[]elements1;
	cout << "按回车键继续！" << endl;
	while (getchar() != '\n')
		;
	cout << "迷宫2 入口（0.0） 出口（8.8）：" << endl;
	map2.print();
	map2.find_path();
	delete[]elements2;
	cout << "按回车键继续！" << endl;
	while (getchar() != '\n')
		;
	cout << "迷宫3 入口（0.0） 出口（4.4）：" << endl;
	map3.print();
	map3.find_path();
	delete[]elements3;
	cout << "按回车键继续！" << endl;
	while (getchar() != '\n')
	return 0;
}
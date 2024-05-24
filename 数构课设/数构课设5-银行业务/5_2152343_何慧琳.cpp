#include <iostream>
using namespace std;

template<class Type> class Queue;
template <class Type>
class QueueNode {//队列结点类
	friend class Queue<Type>;
	Type data;//结点数据
	QueueNode* link;//链接指针
	QueueNode(Type d = 0, QueueNode* l = NULL) :data(d), link(l) {};//构造函数
};
template <class Type>
class Queue {
public:
	Queue():first(NULL),rear(NULL) {};//构造函数
	~Queue();//队列析构函数
	void push(const Type item);//结点入队
	Type top();//取队头结点
	Type pop();//队头出队，返回队头元素值
	int IsEmpty()const {return first == NULL;};//判断队列是否为空，空返回1，非空返回0
	void MakeEmpty();//清空队列
private:
	QueueNode<Type>* first, * rear;//队列指针
};
template <class Type> Queue<Type>::~Queue()
{//队列析构函数，操作与清空函数同
	MakeEmpty();
}
template <class Type> void Queue<Type>::push(const Type item)
{//元素入队
	if (first==NULL) {//插入第一个元素
		first = rear = new QueueNode<Type>(item);
	}
	else {
		rear->link = new QueueNode<Type>(item);
		rear = rear->link;
	}
}
template <class Type> Type Queue<Type>:: top()
{//返回第一个结点
	Type error;
	if (!IsEmpty())
		return first->data;
	else
		return error;
}
template <class Type> Type Queue<Type>::pop()
{//删除队头结点，返回删除结点的data
	if (!IsEmpty()) {
		QueueNode<Type>* temp = first;
		first = first->link;
		Type retdata = temp->data;
		delete temp;
		return retdata;
	}
	else
		return NULL;
}
template <class Type> void Queue<Type>::MakeEmpty()
{//清空队列
	QueueNode<Type>* temp;
	while (first != NULL) {
		temp = first;
		first = first->link;
		delete temp;
	}
}

class banking_bussiness {//银行业务类
public:
	banking_bussiness() :total(0) {};//银行业务构造函数
	void read();//输入顾客队列
	void operation();//按照业务处理完成的顺序输出顾客的编号
private:
	int total;//顾客总数
	Queue<int> queue;//顾客队列
};
void banking_bussiness::read()
{////读入顾客队列
	cout<<"请输入一行顾客编号队列，第一个数表示总人数(≤1000)，每个数之间以空格结尾："<<endl;
	while (1) {
		cin >> total;
		if (cin.fail() || total <= 0) {
			cout << "输入错误，请重新输入！" << endl;
			cin.ignore(1000, '\n');
			cin.clear();
		}
		else
			break;
	}
	int ord,num;//分别表示正在读入的顾客的序号和编号
	for (ord = 1; ord <= total; ord++) {
		while (1) {//输入工作
			cin >> num;
			if (cin.fail() || num <= 0) {
				cout << "第" << ord << "个顾客编号输入错误，请从该顾客开始重新输入！" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			else
				break;
		}
		queue.push(num);//输入正确，该顾客入队
	}
}
void banking_bussiness::operation()
{//按照业务处理完成的顺序输出顾客的编号
	Queue<int> A_queue,B_queue;//A、B窗口还在排队的顾客队列
	int first = 1;//是否是第一个输出的编号
	while (!queue.IsEmpty()) {//将所有顾客分到A、B窗口
		int num = queue.pop();//弹出队头编号并返回给num
		if (num % 2 == 1) //编号为奇数进入A队列
			A_queue.push(num);
		else//编号为偶数进入B队列
			B_queue.push(num);
	}
	int t = 0;//记录时间
	while (!A_queue.IsEmpty()) {
		if (!first)//不是第一个被输出的顾客编号则在编号前输出空格
			cout << " ";
		cout << A_queue.pop();//弹出出A队头并输出其编号
		t++;//A窗口处理完一个顾客，时间+1
		if (t == 2) {//A处理完两个顾客，B处理完一个顾客
			if (!B_queue.IsEmpty()) {
				cout << " " << B_queue.pop();//弹出B队头并输出其编号
			}
			t = 0;//一个周期结束时间，清零。
		}
		first = 0;//第一个输出标志清零
	}
	while (!B_queue.IsEmpty()) {
		if (!first)//不是第一个被输出的顾客编号则在编号前输出空格
			cout << " ";
		cout << B_queue.pop();
		first = 0;
	}
	cout << endl;
}


int main()
{
	banking_bussiness bank;
	while (1) {
		bank.read();
		bank.operation();
		char yn;
		cout << "是否继续？（y/n）：";
		while (1) {
			cin >> yn;
			if (yn != 'y' && yn != 'n') {
				cout << "输入错误，请重新输入！";
				cin.ignore(100, '\n');
				cin.clear();
			}
			else
				break;
		}
		if (yn == 'n')
			break;
	}
	return 0;
}
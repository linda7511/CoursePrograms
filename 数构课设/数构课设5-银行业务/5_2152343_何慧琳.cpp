#include <iostream>
using namespace std;

template<class Type> class Queue;
template <class Type>
class QueueNode {//���н����
	friend class Queue<Type>;
	Type data;//�������
	QueueNode* link;//����ָ��
	QueueNode(Type d = 0, QueueNode* l = NULL) :data(d), link(l) {};//���캯��
};
template <class Type>
class Queue {
public:
	Queue():first(NULL),rear(NULL) {};//���캯��
	~Queue();//������������
	void push(const Type item);//������
	Type top();//ȡ��ͷ���
	Type pop();//��ͷ���ӣ����ض�ͷԪ��ֵ
	int IsEmpty()const {return first == NULL;};//�ж϶����Ƿ�Ϊ�գ��շ���1���ǿշ���0
	void MakeEmpty();//��ն���
private:
	QueueNode<Type>* first, * rear;//����ָ��
};
template <class Type> Queue<Type>::~Queue()
{//����������������������պ���ͬ
	MakeEmpty();
}
template <class Type> void Queue<Type>::push(const Type item)
{//Ԫ�����
	if (first==NULL) {//�����һ��Ԫ��
		first = rear = new QueueNode<Type>(item);
	}
	else {
		rear->link = new QueueNode<Type>(item);
		rear = rear->link;
	}
}
template <class Type> Type Queue<Type>:: top()
{//���ص�һ�����
	Type error;
	if (!IsEmpty())
		return first->data;
	else
		return error;
}
template <class Type> Type Queue<Type>::pop()
{//ɾ����ͷ��㣬����ɾ������data
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
{//��ն���
	QueueNode<Type>* temp;
	while (first != NULL) {
		temp = first;
		first = first->link;
		delete temp;
	}
}

class banking_bussiness {//����ҵ����
public:
	banking_bussiness() :total(0) {};//����ҵ���캯��
	void read();//����˿Ͷ���
	void operation();//����ҵ������ɵ�˳������˿͵ı��
private:
	int total;//�˿�����
	Queue<int> queue;//�˿Ͷ���
};
void banking_bussiness::read()
{////����˿Ͷ���
	cout<<"������һ�й˿ͱ�Ŷ��У���һ������ʾ������(��1000)��ÿ����֮���Կո��β��"<<endl;
	while (1) {
		cin >> total;
		if (cin.fail() || total <= 0) {
			cout << "����������������룡" << endl;
			cin.ignore(1000, '\n');
			cin.clear();
		}
		else
			break;
	}
	int ord,num;//�ֱ��ʾ���ڶ���Ĺ˿͵���źͱ��
	for (ord = 1; ord <= total; ord++) {
		while (1) {//���빤��
			cin >> num;
			if (cin.fail() || num <= 0) {
				cout << "��" << ord << "���˿ͱ�����������Ӹù˿Ϳ�ʼ�������룡" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			else
				break;
		}
		queue.push(num);//������ȷ���ù˿����
	}
}
void banking_bussiness::operation()
{//����ҵ������ɵ�˳������˿͵ı��
	Queue<int> A_queue,B_queue;//A��B���ڻ����ŶӵĹ˿Ͷ���
	int first = 1;//�Ƿ��ǵ�һ������ı��
	while (!queue.IsEmpty()) {//�����й˿ͷֵ�A��B����
		int num = queue.pop();//������ͷ��Ų����ظ�num
		if (num % 2 == 1) //���Ϊ��������A����
			A_queue.push(num);
		else//���Ϊż������B����
			B_queue.push(num);
	}
	int t = 0;//��¼ʱ��
	while (!A_queue.IsEmpty()) {
		if (!first)//���ǵ�һ��������Ĺ˿ͱ�����ڱ��ǰ����ո�
			cout << " ";
		cout << A_queue.pop();//������A��ͷ���������
		t++;//A���ڴ�����һ���˿ͣ�ʱ��+1
		if (t == 2) {//A�����������˿ͣ�B������һ���˿�
			if (!B_queue.IsEmpty()) {
				cout << " " << B_queue.pop();//����B��ͷ���������
			}
			t = 0;//һ�����ڽ���ʱ�䣬���㡣
		}
		first = 0;//��һ�������־����
	}
	while (!B_queue.IsEmpty()) {
		if (!first)//���ǵ�һ��������Ĺ˿ͱ�����ڱ��ǰ����ո�
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
		cout << "�Ƿ��������y/n����";
		while (1) {
			cin >> yn;
			if (yn != 'y' && yn != 'n') {
				cout << "����������������룡";
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
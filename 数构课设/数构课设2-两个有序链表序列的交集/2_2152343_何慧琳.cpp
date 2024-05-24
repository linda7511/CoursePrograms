#include <iostream>
using namespace std;
class List;
class Listnode {//链表结点类
	friend List;
	int data;//结点值
	Listnode* link;//指向当前节点的下一个结点
public:
	Listnode() :link(NULL) {};//链表结点构造函数
	Listnode(int i) :data(i), link(NULL) {};//链表结点构造函数
};
class List {
public:
	List() { first = new Listnode(); };//链表构造函数
	~List();//析构函数
	void read();//将输入数据读入链表的函数
	void AND(List &list2);//取交集函数并输出
	void Makeempty();//删除除表头外的所有结点
private:
	Listnode* first;//头指针
};
List::~List()
{//析构函数
	Makeempty();
	delete first;
}
void List::read()
{//将输入数据读入链表
	cout << "请输入一个由若干正整数构成的非降序序列（以-1结尾）：";
	int i;//表示当前读到的数
	Listnode* current=first;
	while (1) {
		cin >> i;
		if (cin.fail() || (i <= 0 && i != -1)) {
			cout << "输入错误，请重新输入这个序列：";
			cin.clear();
			cin.ignore(INT_MAX,'\n');//清空流 
			Makeempty();//将已输入部分数据的链表置空
			current = first;//current重新指向头结点
			continue;
		}
		if (i == -1)
			break;
		current -> link = new Listnode(i);
		current = current->link;
	}
}
void List::AND(List& list2)
{//取交集函数并输出
	List ans;//存储输出序列
	Listnode* current = ans.first;//指向ans链表的指针
	Listnode* cur1=first->link,* cur2=list2.first->link;//this链表和list2链表的检测指针
	while (cur1 != NULL && cur2 != NULL) {//两个序列均未读完
		if (cur1->data == cur2->data) {//一个数在两个链表中都出现则存入输出链表
			current->link = new Listnode(cur1->data);
			current = current-> link;//ans指针向后移一位
			cur1 = cur1->link;//cur1指针向后移一位
			cur2 = cur2->link;//cur2指针向后移一位
		}
		else if (cur1->data < cur2->data) {//cur1指向的数小于cur2指向的数，cur1指针移一位cur2不动
			cur1 = cur1->link;
		}
		else if (cur1->data > cur2->data) //cur1指向的数小于cur2指向的数，cur2指针移一位cur1不动
			cur2 = cur2->link;
	}
	cout << "交集S3：";
	current = ans.first->link;//current再次指向第一个结点
	if (current == NULL) {//ans为空表
		cout << "NULL" << endl;
	}
	while (current != NULL) {
		cout << current->data;
		if ((current = current->link) != NULL)//current指向下一个结点，下一个结点非空则输出一个空格
			cout << " ";
		else
			cout << endl;
	}
	cout << endl;
}
void List::Makeempty()
{//链表置空函数，删除除表头外的所有节点
	Listnode* current;
	while (first->link != NULL) {
		current = first->link;//跳过了表头结点
		first->link = current->link;//将第一个结点从链表中摘下
		delete current;//释放该结点
	}
}
int main()
{
	List S1, S2;
	while (1) {
		cout << "请输入S1" << endl;
		S1.read();
		cout << "请输入S2" << endl;
		S2.read();
		S1.AND(S2);
		cout << "是否继续？（y/n）";
		char go_on;
		cin >> go_on;
		while (go_on != 'y' && go_on != 'n') {//输入错误
			cout << "输入错误，请重新输入（y/n）";
			cin.ignore(100, '\n');
			cin.clear();
			cin >> go_on;
		}
		if (go_on == 'n')
			break;
		else {//继续则置空S1、S2
			S1.Makeempty();
			S2.Makeempty();
		}
	}
	return 0;
}
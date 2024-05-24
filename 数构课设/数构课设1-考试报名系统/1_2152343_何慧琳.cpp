#include <iostream>
#include <cstring>
using namespace std;
class linklist;
class listnode {
	friend class linklist;
	char *num;//准考证号
	char *name;//姓名
	char *sex;//性别
	char *age;//年龄
	char *work;//报考类别
	listnode* link;//结点指针
public:
	listnode() :link(NULL) {};//链表结点构造函数
	listnode(char* nu, char* na, char* se, char *ag, char* wo, listnode* li = NULL) :num(nu), name(na), sex(se), age(ag), work(wo), link(li) {};//链表结点构造函数
	listnode(const listnode& ln);//链表结点复制构造构造函数	
};
class linklist {
public:
	linklist() { last = first = new listnode(); };//链表构造函数（带表头结点）
	~linklist();//析构函数
	void add(listnode l, int pos = NULL);//将l项插入位置i，若未向i传递参数则在末尾添加l结点
	int del(const char* n);//将考号为n的考生信息删除
	listnode* find(const char* n);//查找考号为n的考生信息
	int modify(const char* n, listnode newnode);//将考号为n的考生信息改为newnode
	int sum();//统计链表中考生的总人数并打印链表
	void MakeEmpty();//删链表置空
	int print(char *nu = NULL);//打印链表内容，若向*nu传递了参数则只打印学号为*nu的考生信息
private:
	listnode* first, * last;//表头指针，表尾指针
};
listnode::listnode(const listnode& ln)
{//将ln深复制
	num = new char[20];
	name = new char[20];
	sex = new char[2];
	age = new char[3];
	work = new char[20];
	strcpy(num, ln.num);
	strcpy(name, ln.name);
	strcpy(sex, ln.sex);
	strcpy(age, ln.age);
	strcpy(work, ln.work);
}
linklist::~linklist()
{//析构函数
	MakeEmpty();//链表置空
	delete first;//删去表头结点
}
void linklist::add(listnode l, int pos)
{//将listnode l插入到链表第pos个位置,若未向pos传值，则插入到末尾
	if (pos == NULL) {
		last->link = new listnode(l);
		last = last->link;
		return;
	}
	listnode* current = first;//检测指针current指示表头结点
	int i = 0;
	while (i < pos-1 && current->link != NULL) {//将p指针移至插入位置前一位或链表末尾
		i++;
		current = current->link;
	}
	listnode *n=new listnode(l);//创建新结点
	n->link = current->link;
	current->link = n;//实现插入新结点
	if (n->link == NULL)//更新末尾指针
		last = n;
}
int linklist::del(const char* n)
{//删除考号为n的考生信息
	listnode* current = find(n);//current指向目标结点前一个结点
	if (current == NULL) {//p指针为NULL，说明查找对象不存在
		cout << "该考生不存在！" << endl;
		return 0;
	}
	listnode* q = current->link;//q指针指向待删除结点
	current->link = q->link;
	cout << "你删除的考生信息是：" << q->num << "   " << q->name << "   " << q->sex << "   " << q->age << "   " << q->work << endl;
	delete q;//删除目标节点
	return 1;
}
listnode* linklist::find(const char* n)
{//在链表中从头搜索学号num为n的结点。若存在，返回该结点前一个结点地址；若不存在，返回NULL
	listnode * current = first;//检测指针current指项表头结点
	while (current != NULL) {
		if (current->link!=NULL&&strcmp(current->link->num, n) == 0)
			return current;//current的下一个结点为目标结点时返回p；
		current = current->link;
	}
	return current;
}
int linklist::modify(const char* n, listnode newnode)
{//将考号为n的考生信息改为newnode中的信息
	listnode* current = find(n);//current指向目标结点前一个结点
	if (current == NULL) {//current指针为NULL，说明查找对象不存在
		cout << "该考生不存在！" << endl;
		return 0;
	}
	current = current->link;//current指向待修改结点
	strcpy(current->num,newnode.num);//修改current指向结点的内容
	strcpy(current->name, newnode.name);
	strcpy(current->sex, newnode.sex);
	strcpy(current->age, newnode.age);
	strcpy(current->work, newnode.work);
	return 1;
}
int linklist::sum()
{
	int sum = 0;
	listnode* current = first;
	while (current->link != NULL) {
		current = current->link;
		sum++;
	}
	return sum;
}
void linklist::MakeEmpty()
{//删去链表中除表头结点外的所有其它结点
	listnode* current;
	while (first->link != NULL) {
		current = first->link;
		first->link = current->link;//将第一个结点从链表中摘下
		delete current;//删除摘下的结点
	}
	last = first;//修改表尾指针
}
int linklist::print(char *nu)//无参传递则打印整个数组，有参则打印考号为nu的考生信息
{
	if (first->link == NULL)//表空
		return 0;
	listnode* current;
	if (nu != NULL) {
		current = find(nu);
		if(current ==NULL)
			return 0;
		else {
			current = current->link;
			cout << "考号                姓名      性别  年龄  报考类别" << endl;
			printf("%-20s%-10s%-6s%-6s%s\n", current->num, current->name, current->sex, current->age, current->work);
			return 1;
		}
	}
	current = first;//无参数传递，打印整个链表，检测指针p指向表头结点
	cout << "考号                姓名      性别  年龄  报考类别" << endl;
	while (current->link != NULL) {
		current = current->link;
		printf("%-20s%-10s%-6s%-6s%s\n", current->num, current->name, current->sex, current->age, current->work);
	}
	return 1;
}

int main()
{
	int stu_num, program;//分别表示考生人数和选择操作的编号
	linklist ll;//建立一个链表对象
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生人数：" ;
	while (1) {
		cin >> stu_num;
		if (cin.good()&&stu_num>0)
			break;
		else {
			cout << "输入错误，请输入一个正整数：";
			cin.clear();
			cin.ignore(100, '\n');
		}
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	char *num=new char[20], * name = new char[20], * sex = new char[2],*age=new char[3], * work = new char[20];//分别储存输入的学号、姓名、性别、年龄、报考类别
	for (int i = 0; i < stu_num; i++) {
 		cin >> num >> name >> sex >> age >> work;
		while (!(age > 0)) {
			cout << "考号为" << num << "的考生年龄输入错误，请重新输入该考生信息！" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cin >> num >> name >> sex >> age >> work;
		}
		listnode newnode(num, name, sex, age, work);
		ll.add(newnode);
	}//!!!如果多输入了数据后面会读错
	ll.print();
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
	while (1) {
		cout << "请选择您要进行的操作：";
		cin >> program;
		switch (program) {
		case 1:
			int pos;//要插入的位置
			cout << "请您输入你要插入的考生的位置：";
			cin >> pos;
			{int length = ll.sum();
			while (pos<1 || pos>length + 1) {
				cout << "位置输入错误，请输入1-" << length + 1 << "的整数！\n";
				cin >> pos;
			}
			}
			cout << "请依次输入要插入考生的考号、姓名、性别、年龄及报考类别！\n";
			cin >> num >> name >> sex >> age >> work;
			{listnode newnode(num, name, sex, age, work);//创建一个以刚输入的信息为内容的新结点
			ll.add(newnode, pos); }//插入新结点
			cout << endl;
			ll.print();//打印链表
			break;
		case 2:
			cout << "请输入要删除的考生的考号：";
			cin >> num;
			if(ll.del(num)) {//del函数返回不为0，说明删除成功，打印链表
				cout << endl;
				ll.print();//打印链表
			}
			break;
		case 3:
			cout << "请输入要查找的考生的考号：";
			cin >> num;
			cout << endl;
			if (!ll.print(num))
				cout << "该考号不存在！" << endl;
			break;
		case 4:
			cout << "请输入要修改的考生的考号：";
			cin >> num;
			cout << endl;
			if (!ll.print(num))
				cout << "该考号不存在！" << endl;
			else {
				char* newnum=new char[20];
				cout << "请依次输入该考生的新信息：考号、姓名、性别、年龄及报考类别\n";
				cin >> newnum >> name >> sex >> age >> work;
				listnode newnode(newnum, name, sex, age, work);//创建以新输入的信息为内容的结点
				ll.modify(num, newnode);//在链表中修改原考号为num的结点信息为newnode
				cout << "修改成功！\n";
				ll.print();
			}
			break;
		case 5:
			cout <<"当前考生总人数："<< ll.sum() << endl;//输出统计的考生人数
			ll.print();//打印当前全部考生信息
			break;
		case 0:
			return 0;
			break;
		default: 
			cout << "您输入的操作码不存在，请重新输入！" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			break;
		}
	}
	return 0;
}
#include <iostream>
using namespace std;

template <class Type>
class stack {//自定义栈类
	class stacknode {//栈的结点类
	public:
		Type data;//结点数据
		stacknode* link;
		stacknode(Type d=NULL,stacknode* l=NULL) :data(d),link(l) {};//栈的结点构造函数
	};
	stacknode* top;//栈顶指针
public:
	stack() :top(NULL) {};//无参构造函数
	stack(Type d) { top = new stacknode(d); }//带参构造函数
	~stack();//析构函数，与make_empty操作同
	void push(Type d) { top = new stacknode(d, top); }//将以d为值的结点入栈
	Type pop();//删除栈顶结点
	Type gettop() {return top->data;}//取栈顶结点
	void make_empty();//清空栈
	int is_empty() { return top == NULL; }//判断栈是否为空
};
template <class Type> stack<Type>::~stack()
{
	make_empty();
}
template <class Type> Type stack<Type>::pop()
{//删除栈顶结点,返回被删结点的值
	stacknode* temp = top;//用temp暂存结点
	top = top->link;//更新top指针
	Type reval = temp->data;//reval暂存要返回的结点的值
	delete temp;//删除栈顶结点
	return reval;//返回原栈顶结点的值
}
template <class Type> void stack<Type>::make_empty()
{//清空栈
	while (top) {//重复操作直至top==NULL
		stacknode* temp = top;
		top = top->link;
		delete temp;
	}
}



class family_tree;
class family_treenode {//家谱树结点（家谱成员）类
	friend class family_tree;
	char* name;//成员名
	family_treenode* first_child, * next_sibling;//指向左长子，右兄弟
	int visit=0;//删除成员后序遍历时经过次数
	family_treenode(char* n=NULL) :name(n),first_child(NULL),next_sibling(NULL) {};//构造函数
	family_treenode(family_treenode* ftn) :name(ftn->name),first_child(ftn->first_child),next_sibling(ftn->next_sibling) {};//复制构造函数
};
class family_tree {
public:
	family_tree() :ancestor(NULL), current(NULL) {};//无参构造函数
	family_tree(char *n);//以祖先名为参数的构造函数
	~family_tree();//析构函数，操作同make_empty()
	void add_member(int build_or_add);//为成员建立家庭或添加子女
	void dissolve_family(int all=0);//解散某人的家庭,若all为1，则解散祖先的家庭
	void change_name();//更改某人的姓名
	void make_empty();//清空家谱
private:
	family_treenode* ancestor,*current;//定义指向根节点的指针和指向当前节点的指针
	family_treenode* preorder(char *n);//前序遍历查找名为*n的结点位置
};
family_tree::family_tree(char* n) 
{//以祖先名为参数的构造函数
	ancestor = current = new family_treenode(n);
}
family_tree::~family_tree()
{
	make_empty();
}
family_treenode* family_tree::preorder(char* n)
{//前序遍历查找名为*n的结点
	current = ancestor;//从根节点开始查找
	stack<family_treenode*> st;
	while (current||!st.is_empty()) {
		while (current != NULL && strcmp(current->name,n)!=0) {//一左到底
			st.push(current);//经历过的结点都入栈
			current = current->first_child;//进入左子树
		}
		if (current!=NULL&&strcmp(current->name, n)==0)//找到目标结点
			return current;
		//current==NULL
		current = st.pop()->next_sibling;//current指向最近未被访问的根节点的右子树
	}
	return current;
}
void family_tree::add_member(int build_or_add)
{//build_or_and为0，建立家庭；为1，为某个人在家谱中添加儿女
	char* parent=new char[20];//要建立家庭的人的姓名
	int num=1;//要添加的子女数
	family_treenode* temp=current;//一开始指向长子，方便最后遍历输出parent的第一代子孙
	if(build_or_add==0)
	    cout << "请输入要建立家庭的人的姓名：";
	else
		cout << "请输入要添加儿子或女儿的人的姓名：";
	cin >> parent;
	preorder(parent);//查找parent，使current指向其位置
	if (current == NULL) {
		cout << parent << "不存在！" << endl;
			return;
	}
	if (build_or_add == 0) {
		cout << "请输入" << parent << "的儿女人数：";
		cin.ignore(20, '\n');
		while (1) {
			cin >> num;
			if (!cin.good()||num <= 0  ) {
				cout << "输入错误，请重新输入:";
				cin.ignore(100, '\n');
				cin.clear();
			}
			else
				break;
		}
	}
	if (build_or_add == 0)
		cout << "请依次输入" << parent << " 的儿女的姓名：";
	else
		cout << "请输入" << parent << "新添加的儿子（或女儿）的姓名：";
	for (int i = 0; i < num; i++) {//逐个完成缓冲区儿女姓名的读取和在家谱中的插入
        char* child = new char[20];//子女的姓名
		cin >> child;
		if (i == 0) {//插入第一个孩子
			if (build_or_add == 1) {
				if (current->first_child!=NULL) {
					current = current->first_child;
					temp = current;//temp指向长子
				    while (current->next_sibling!=NULL) //在最后一个孩子后插入新孩子
						current = current->next_sibling;
					current->next_sibling = new family_treenode(child);//完成插入新孩子
				}
				else {
					current->first_child = new family_treenode(child);//完成插入新孩子
					temp = current->first_child;
				}
				
			}
			else {
				current->first_child = new family_treenode(child);//插入parent的长子
				temp = current->first_child;//指向长子
				current = current->first_child;//current指向刚被插入的孩子，为插入下一个孩子做准备
			}
		}
		else {
			current->next_sibling = new family_treenode(child);//插入parent非长子的孩子即插入长子的右兄弟
			current = current->next_sibling;//current指向刚被插入的孩子，为插入下一个孩子做准备
		}
	}
	cout << parent << "的第一代子孙是：";
	for (int i = 0;temp!=NULL; i++) {//遍历输出parent的第一代子孙
		cout << temp->name<<"     ";//输出当前孩子的姓名
		temp = temp->next_sibling;//temp指向下一个孩子
	}
	cout << endl;
}
void family_tree::dissolve_family(int all) 
{//解散以*parent为名的人的家庭,当all==1时相当于清空整个家谱树（除祖先）
	char* parent = new char[20];//要解散家庭的人的姓名
	family_treenode* p;//用于保存parent的位置
	if (all == 1)
		parent = ancestor->name;
	if (all == 1) {
		parent = ancestor->name;
		p = preorder(parent);//查找parent，使p指向其位置
	}
	else {
		cout << "请输入要解散家庭的人的姓名：";
		cin >> parent;
	    p=preorder(parent);//查找parent，使p指向其位置
	    if (current == NULL) {
			cout << parent << "不存在！" << endl;
		return;
		}
		cout << "要解散家庭的人是：" << parent << endl;
		cout << parent << "的第一代子孙是：";
	}
	family_treenode* temp;
	if (!all) {//不是用于清空功能，需要输出被解散家庭的人的第一代子孙
	    temp = current->first_child;//temp指向长子
		for (int i = 0; temp; i++) {//遍历输出parent的第一代子孙
			cout << temp->name << "     ";//输出当前孩子的姓名
			temp = temp->next_sibling;//temp指向下一个孩子
		}
		cout << endl;
	}
	current= p->first_child;//current指向长子
	stack<family_treenode*> st;//存储遍历途中经过但未被访问的结点
	while (current || !st.is_empty()) {//删除工作
		while (current) {//一左到底
			if (current->visit >= 2)//右子树也遍历完毕该节点成为叶结点
				break;
			st.push(current);//经历过的结点都入栈
			current = current->first_child;//进入左子树
		}
		current = st.gettop();
		current->visit++;
		if (current->next_sibling==NULL) {//当前节点既无左子树也无右子树，是叶节点，若不是parent则删除
			family_treenode* temp1;
			temp1 = current;
			if(!st.is_empty())
				st.pop();//结点出栈
			if (st.is_empty())//栈空则所有元素已处理完，退出循环
				break;
			current = st.gettop();//current指向下一个未被访问的结点
			current->next_sibling = temp1->next_sibling;//current的兄弟置空
			p->first_child= temp1->next_sibling;//使parent的长子为空
			if(current)
			    current->visit++;
			delete temp1;//释放temp结点
		}
		else//当前结点存在右孩子，则进入右子树
		    current = current->next_sibling;//current指向右孩子
	}
}
void family_tree::change_name()
{//更改当前姓名为*cur_name的人的姓名
	char* name = new char[20];//要修改的人的姓名；
	char* toname = new char[20];//更改后的姓名
	cout << "请输入要更改姓名的人的目前姓名：";
	cin >> name;
	preorder(name);////前序遍历查找名为*name的结点位置
	if (current == NULL) {
		cout << name << "不存在！" << endl;
		return;
	}
	cout << "请输入更改后的姓名：";
	cin >> toname;
	current->name = toname;
	cout << name << "已更名为" << toname<<endl;
}
void family_tree::make_empty()
{
	dissolve_family(1);//删除ancestor的所有子代
	delete ancestor;//释放ancestor
}


int main()
{
	char* ancestor_name = new char[20];//祖先姓名
	char menu_chocie;//菜单选项
	cout << "**          家谱管理系统          **"<<endl;
	cout << "=====================================" << endl;
	cout << "**       请选择要执行的操作：     **" << endl;
	cout << "**         A---完善家庭           **" << endl;
	cout << "**         B---添加家庭成员       **" << endl;
	cout << "**         C---解散局部家庭       **" << endl;
	cout << "**         D---更改家庭成员姓名   **" << endl;
	cout << "**         E---退出程序           **" << endl;
	cout << "=====================================" << endl;
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	cin >> ancestor_name;
	family_tree ft(ancestor_name);//创建一个以ancestors_name为祖先的家谱
	cout << "此家谱的祖先是：" << ancestor_name<<endl;
	cout << endl;
	while (1) {
		cout << "请选择要执行的操作：";
		while (1) {//输入处理
			cin >> menu_chocie;
			if (menu_chocie >= 'A' && menu_chocie <= 'E')
				break;
			else if (menu_chocie >= 'a' && menu_chocie <= 'e'){
				menu_chocie -= 'a' - 'A';
				break;
			}
			else {
				cin.ignore(100, '\n');
				cin.clear();
				cout << "输入错误，请重新输入：";
			}
		}
		switch (menu_chocie) {
		case 'A':
			ft.add_member(0);
			cout << endl;
			break;
		case 'B':
			ft.add_member(1);
			cout << endl;
			break;
		case 'C':
			ft.dissolve_family();
			cout << endl;
			break;
		case 'D':
			ft.change_name();
			cout << endl;
			break;
		case 'E':
			cout << "程序结束！";
			return 0;
		default:
			break;
		}
	}
	return 0;
}
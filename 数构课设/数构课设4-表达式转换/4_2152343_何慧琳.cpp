#include <iostream>
#include <string>
#include <assert.h>
using namespace std;
template <class Type> class Stack;
template <class Type> class StackNode {
	friend class Stack<Type>;
private:
	Type data; //结点数据
	StackNode<Type>* link; //结点链指针
	StackNode(Type d = 0, StackNode<Type>* l = NULL) : data(d), link(l) { }//结点构造函数
};
template <class Type> class Stack {
public:
	Stack() : top(NULL) { }//栈构造函数
	~Stack();//栈析构函数
	void Push(const Type& item);//将data为的item结点入栈
	Type Pop();//将栈顶结点删除
	Type Top();//取栈顶元素
	void MakeEmpty(); //将栈置空
	int IsEmpty() const//判断栈是否为空
	{
		return top == NULL;
	}
private:
	StackNode<Type>* top; //栈顶指针
};
template <class Type> Stack<Type>::~Stack()
{//栈的析构函数
	StackNode<Type>* temp;
	while (top != NULL) {//逐结点回收
		temp = top;
		top = top->link;
		delete temp;
	}
}
template<class Type>void Stack<Type>::Push(const Type& item)
{
	top = new StackNode<Type>(item, top);//新结点链入top之前，并成为新栈顶
}
template <class Type> Type Stack<Type>::Pop() {//删除栈顶元素
	assert(!IsEmpty());
	StackNode<Type>* temp = top;
	Type retvalue = temp->data; //暂存栈顶数据
	top = top->link; //修改栈顶指针
	delete temp; //释放原栈顶结点
	return retvalue; //释放,返回数据
}
template <class Type> Type Stack<Type>::Top() {//取栈顶数据
	assert(!IsEmpty());
	return top->data;
}
template <class Type> void Stack<Type>::MakeEmpty()
{//清空栈
	StackNode<Type>* temp;
	while (top != NULL) {//逐结点回收
		temp = top;
		top = top->link;
		delete temp;
	}
}

class expression_in_to_post {//表达式中缀转后缀类
public:
	expression_in_to_post(char* str=NULL) :expression_str(str) {};//表达式类构造函数
	void read();//读入表达式字符串，初始化expression_str
	void conversion();//实现中缀转后缀功能
	void optr_enStack(char opt);//将读到的运算符入栈
private:
	struct optr_priority {
		char optr;
		int priority;
		optr_priority(char opt)//构造函数
		{
			optr = opt;
			switch (opt) {
			case '+':
				priority = 2;
				break;
			case '-':
				priority = 2;
				break;
			case '*':
				priority = 3;
				break;
			case '/':
				priority = 3;
				break;
			case '(':
				priority = 4;
				break;
			case ')':
				priority = 4;
				break;
			default:
				break;
			}
		}
	};
	char* expression_str;//算数表达式字符串
	Stack<optr_priority> optrs;//存运算符的栈
};
void expression_in_to_post::read()
{//读入表达式字符串，初始化expression_str
	cout << "请输入一个中缀表达式，用空格分割不同对象：" << endl;
	while (1) {
		char* p;//检测指针
		char* temp=new char[50];//暂存表达式
		cin.getline(temp,50);//输入表达式
		p = temp;
		int ifcontinue = 0;//是否继续标志
		while (*p) {//字符串没读完
			if (*p == ' '|| *p == '+'|| *p == '-'|| *p == '*'|| *p == '/'|| *p == '('|| *p == ')'|| *p == '.' ||(*p >= '0'&& *p <= '9'))//有效字符
				p++;
			else {//出现非法字符，需要重新输入，ifcontinue置1
				ifcontinue = 1;
				break;
			}
		}
		if (!ifcontinue) {//输入合法，初始化expression_str，退出输入大循环
			expression_str = temp;
			break;
		}
		else {//输入非法，重新输入
			delete[] temp;
			cout << "表达式输入非法，请重新输入！" << endl;
			continue;
		}
	}
}
void expression_in_to_post::conversion()
{//实现中缀转后缀功能
	char* p = expression_str;//扫描指针
	int first=1;//是否是第一个算数的标记，1为是，0为不是，不是则在前面输出空格
	while (*p) {
		if (*p == ' ')
			p++;
		else if (*p >= '0' && *p <= '9') {
			if (!first)//非第一个数的数前面都输出一个空格
				cout << " ";
			while (*p&&*p != ' ') {//遇到小数点也会输出
				cout << *p;
				p++;
			}
			first = 0;//第一个数已访问过，first标记置零
		}
		else {
			if ((*p == '+' || *p == '-') && (*(p + 1) >= '0' && *(p + 1) <= '9')) {
				if (!first)//非第一个数的数前面都输出一个空格
					cout << " ";
				if (*p == '-')//为负号则输出，为正好不输出
					cout << "-";
				p++;
				while (*p && *p != ' ') {//输出数字
					cout << *p;
					p++;
				}
				first = 0;//第一个数已访问过，first标记置零
			}
			else {
				optr_enStack(*p);//运算符入栈操作
				p++;
			}
		}
	}
	while (!optrs.IsEmpty()) {
		cout << " "<<optrs.Pop().optr;
	}
	cout << endl;
}
void expression_in_to_post::optr_enStack(char opt)
{//将读到的运算符入栈
	optr_priority current_opt(opt);
	int priority = current_opt.priority;
	if (optrs.IsEmpty())
		optrs.Push(optr_priority(opt));
	else {
		if (priority > optrs.Top().priority) {//当前符号优先级高于栈顶符号
			if (opt == ')') {
				while (optrs.Top().optr != '(') {//弹出运算符并输出直到遇到（
					cout << " ";
					cout << optrs.Pop().optr;
				}
				optrs.Pop();//（出栈
			}
			else
				optrs.Push(optr_priority(opt));//当前符号入栈
		}
		else {
			if (optrs.Top().optr == '(') {//“（”只在遇到“）”时出栈
				if (opt == ')')
					optrs.Pop();
				else
				    optrs.Push(optr_priority(opt));//当前符号入栈
			}
			else {
				while (!optrs.IsEmpty()&&optrs.Top().priority >= priority&&optrs.Top().optr!='(') {//弹出运算符并输出直到栈顶符号优先级比当前符号优先级小或栈空或栈顶元素是（
					cout << " ";
					cout << optrs.Pop().optr;
				}
				optrs.Push(optr_priority(opt));//当前符号入栈
			}
		}
	}
}
//测试用例
expression_in_to_post s1((char *)"2 + 3 * ( 7 - 4 ) + 8 / 4");
expression_in_to_post s2((char*)"( ( 2 + 3 ) * 4 - ( 8 + 2 ) ) / 5");
expression_in_to_post s3((char*)"1314 + 25.5 * 12");
expression_in_to_post s4((char*)"-2 * ( +3 )");
expression_in_to_post s5((char*)"123");

int main()
{
	expression_in_to_post s;
	cout << "欢迎来到表达式转换程序！" << endl;
	cout << "想使用测试样例（5个）请输入a，想自行输入表达式请输入b：";
	char choice;
	while (1) {
		cin >> choice;
		cin.get() != '\n';//将\n读掉
		if (cin.fail() || (choice != 'a' && choice != 'b')) {//输入错误情况
			cout << "输入错误！请重新输入！";
			cin.ignore(100, '\n');
			cin.clear();
			continue;
		}
		else if (choice == 'a') {//使用测试用例
			cout << "s1: 2 + 3 * ( 7 - 4 ) + 8 / 4" << endl;
			cout << "转换结果：";
			s1.conversion();
			cout << endl;
			cout << "s2: ( ( 2 + 3 ) * 4 - ( 8 + 2 ) ) / 5" << endl;
			cout << "转换结果：";
			s2.conversion();
			cout << endl;
			cout << "s3: 1314 + 25.5 * 12" << endl;
			cout << "转换结果：";
			s3.conversion();
			cout << endl;
			cout << "s4: -2 * ( +3 )" << endl;
			cout << "转换结果：";
			s4.conversion();
			cout << endl;
			cout << "s5: 123" << endl;
			cout << "转换结果：";
			s5.conversion();
			cout << endl;
			cout<<"程序结束！"<<endl;
			cout << "按回车键退出！" << endl;
			cin.ignore(100, '\n');
			while (getchar() != '\n')
				;
			break;
		}
		else {//自行输入算式
			while (1) {
				s.read();//输入中缀算式
				s.conversion();//中缀转后缀
				cout << "是否继续输入？（y/n）";
				char yn;
				while (1) {
					cin >> yn;
					if (yn != 'y' && yn != 'n') {//输入错误
						cout << "输入错误！请重新输入！";
						cin.ignore(100, '\n');
						cin.clear();
						continue;
					}
					else
						break;
				}
				if (yn == 'n') {
					cout << "程序结束！" << endl;
					cout << "按回车键退出！" << endl;
					cin.ignore(100, '\n');
					while (getchar() != '\n')
						;
					return 0;
				}
			}
		}
	}

}
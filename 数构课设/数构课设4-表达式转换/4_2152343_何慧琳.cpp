#include <iostream>
#include <string>
#include <assert.h>
using namespace std;
template <class Type> class Stack;
template <class Type> class StackNode {
	friend class Stack<Type>;
private:
	Type data; //�������
	StackNode<Type>* link; //�����ָ��
	StackNode(Type d = 0, StackNode<Type>* l = NULL) : data(d), link(l) { }//��㹹�캯��
};
template <class Type> class Stack {
public:
	Stack() : top(NULL) { }//ջ���캯��
	~Stack();//ջ��������
	void Push(const Type& item);//��dataΪ��item�����ջ
	Type Pop();//��ջ�����ɾ��
	Type Top();//ȡջ��Ԫ��
	void MakeEmpty(); //��ջ�ÿ�
	int IsEmpty() const//�ж�ջ�Ƿ�Ϊ��
	{
		return top == NULL;
	}
private:
	StackNode<Type>* top; //ջ��ָ��
};
template <class Type> Stack<Type>::~Stack()
{//ջ����������
	StackNode<Type>* temp;
	while (top != NULL) {//�������
		temp = top;
		top = top->link;
		delete temp;
	}
}
template<class Type>void Stack<Type>::Push(const Type& item)
{
	top = new StackNode<Type>(item, top);//�½������top֮ǰ������Ϊ��ջ��
}
template <class Type> Type Stack<Type>::Pop() {//ɾ��ջ��Ԫ��
	assert(!IsEmpty());
	StackNode<Type>* temp = top;
	Type retvalue = temp->data; //�ݴ�ջ������
	top = top->link; //�޸�ջ��ָ��
	delete temp; //�ͷ�ԭջ�����
	return retvalue; //�ͷ�,��������
}
template <class Type> Type Stack<Type>::Top() {//ȡջ������
	assert(!IsEmpty());
	return top->data;
}
template <class Type> void Stack<Type>::MakeEmpty()
{//���ջ
	StackNode<Type>* temp;
	while (top != NULL) {//�������
		temp = top;
		top = top->link;
		delete temp;
	}
}

class expression_in_to_post {//���ʽ��׺ת��׺��
public:
	expression_in_to_post(char* str=NULL) :expression_str(str) {};//���ʽ�๹�캯��
	void read();//������ʽ�ַ�������ʼ��expression_str
	void conversion();//ʵ����׺ת��׺����
	void optr_enStack(char opt);//���������������ջ
private:
	struct optr_priority {
		char optr;
		int priority;
		optr_priority(char opt)//���캯��
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
	char* expression_str;//�������ʽ�ַ���
	Stack<optr_priority> optrs;//���������ջ
};
void expression_in_to_post::read()
{//������ʽ�ַ�������ʼ��expression_str
	cout << "������һ����׺���ʽ���ÿո�ָͬ����" << endl;
	while (1) {
		char* p;//���ָ��
		char* temp=new char[50];//�ݴ���ʽ
		cin.getline(temp,50);//������ʽ
		p = temp;
		int ifcontinue = 0;//�Ƿ������־
		while (*p) {//�ַ���û����
			if (*p == ' '|| *p == '+'|| *p == '-'|| *p == '*'|| *p == '/'|| *p == '('|| *p == ')'|| *p == '.' ||(*p >= '0'&& *p <= '9'))//��Ч�ַ�
				p++;
			else {//���ַǷ��ַ�����Ҫ�������룬ifcontinue��1
				ifcontinue = 1;
				break;
			}
		}
		if (!ifcontinue) {//����Ϸ�����ʼ��expression_str���˳������ѭ��
			expression_str = temp;
			break;
		}
		else {//����Ƿ�����������
			delete[] temp;
			cout << "���ʽ����Ƿ������������룡" << endl;
			continue;
		}
	}
}
void expression_in_to_post::conversion()
{//ʵ����׺ת��׺����
	char* p = expression_str;//ɨ��ָ��
	int first=1;//�Ƿ��ǵ�һ�������ı�ǣ�1Ϊ�ǣ�0Ϊ���ǣ���������ǰ������ո�
	while (*p) {
		if (*p == ' ')
			p++;
		else if (*p >= '0' && *p <= '9') {
			if (!first)//�ǵ�һ��������ǰ�涼���һ���ո�
				cout << " ";
			while (*p&&*p != ' ') {//����С����Ҳ�����
				cout << *p;
				p++;
			}
			first = 0;//��һ�����ѷ��ʹ���first�������
		}
		else {
			if ((*p == '+' || *p == '-') && (*(p + 1) >= '0' && *(p + 1) <= '9')) {
				if (!first)//�ǵ�һ��������ǰ�涼���һ���ո�
					cout << " ";
				if (*p == '-')//Ϊ�����������Ϊ���ò����
					cout << "-";
				p++;
				while (*p && *p != ' ') {//�������
					cout << *p;
					p++;
				}
				first = 0;//��һ�����ѷ��ʹ���first�������
			}
			else {
				optr_enStack(*p);//�������ջ����
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
{//���������������ջ
	optr_priority current_opt(opt);
	int priority = current_opt.priority;
	if (optrs.IsEmpty())
		optrs.Push(optr_priority(opt));
	else {
		if (priority > optrs.Top().priority) {//��ǰ�������ȼ�����ջ������
			if (opt == ')') {
				while (optrs.Top().optr != '(') {//��������������ֱ��������
					cout << " ";
					cout << optrs.Pop().optr;
				}
				optrs.Pop();//����ջ
			}
			else
				optrs.Push(optr_priority(opt));//��ǰ������ջ
		}
		else {
			if (optrs.Top().optr == '(') {//������ֻ������������ʱ��ջ
				if (opt == ')')
					optrs.Pop();
				else
				    optrs.Push(optr_priority(opt));//��ǰ������ջ
			}
			else {
				while (!optrs.IsEmpty()&&optrs.Top().priority >= priority&&optrs.Top().optr!='(') {//��������������ֱ��ջ���������ȼ��ȵ�ǰ�������ȼ�С��ջ�ջ�ջ��Ԫ���ǣ�
					cout << " ";
					cout << optrs.Pop().optr;
				}
				optrs.Push(optr_priority(opt));//��ǰ������ջ
			}
		}
	}
}
//��������
expression_in_to_post s1((char *)"2 + 3 * ( 7 - 4 ) + 8 / 4");
expression_in_to_post s2((char*)"( ( 2 + 3 ) * 4 - ( 8 + 2 ) ) / 5");
expression_in_to_post s3((char*)"1314 + 25.5 * 12");
expression_in_to_post s4((char*)"-2 * ( +3 )");
expression_in_to_post s5((char*)"123");

int main()
{
	expression_in_to_post s;
	cout << "��ӭ�������ʽת������" << endl;
	cout << "��ʹ�ò���������5����������a��������������ʽ������b��";
	char choice;
	while (1) {
		cin >> choice;
		cin.get() != '\n';//��\n����
		if (cin.fail() || (choice != 'a' && choice != 'b')) {//����������
			cout << "����������������룡";
			cin.ignore(100, '\n');
			cin.clear();
			continue;
		}
		else if (choice == 'a') {//ʹ�ò�������
			cout << "s1: 2 + 3 * ( 7 - 4 ) + 8 / 4" << endl;
			cout << "ת�������";
			s1.conversion();
			cout << endl;
			cout << "s2: ( ( 2 + 3 ) * 4 - ( 8 + 2 ) ) / 5" << endl;
			cout << "ת�������";
			s2.conversion();
			cout << endl;
			cout << "s3: 1314 + 25.5 * 12" << endl;
			cout << "ת�������";
			s3.conversion();
			cout << endl;
			cout << "s4: -2 * ( +3 )" << endl;
			cout << "ת�������";
			s4.conversion();
			cout << endl;
			cout << "s5: 123" << endl;
			cout << "ת�������";
			s5.conversion();
			cout << endl;
			cout<<"���������"<<endl;
			cout << "���س����˳���" << endl;
			cin.ignore(100, '\n');
			while (getchar() != '\n')
				;
			break;
		}
		else {//����������ʽ
			while (1) {
				s.read();//������׺��ʽ
				s.conversion();//��׺ת��׺
				cout << "�Ƿ�������룿��y/n��";
				char yn;
				while (1) {
					cin >> yn;
					if (yn != 'y' && yn != 'n') {//�������
						cout << "����������������룡";
						cin.ignore(100, '\n');
						cin.clear();
						continue;
					}
					else
						break;
				}
				if (yn == 'n') {
					cout << "���������" << endl;
					cout << "���س����˳���" << endl;
					cin.ignore(100, '\n');
					while (getchar() != '\n')
						;
					return 0;
				}
			}
		}
	}

}
#include <iostream>
using namespace std;

template <class Type>
class stack {//�Զ���ջ��
	class stacknode {//ջ�Ľ����
	public:
		Type data;//�������
		stacknode* link;
		stacknode(Type d=NULL,stacknode* l=NULL) :data(d),link(l) {};//ջ�Ľ�㹹�캯��
	};
	stacknode* top;//ջ��ָ��
public:
	stack() :top(NULL) {};//�޲ι��캯��
	stack(Type d) { top = new stacknode(d); }//���ι��캯��
	~stack();//������������make_empty����ͬ
	void push(Type d) { top = new stacknode(d, top); }//����dΪֵ�Ľ����ջ
	Type pop();//ɾ��ջ�����
	Type gettop() {return top->data;}//ȡջ�����
	void make_empty();//���ջ
	int is_empty() { return top == NULL; }//�ж�ջ�Ƿ�Ϊ��
};
template <class Type> stack<Type>::~stack()
{
	make_empty();
}
template <class Type> Type stack<Type>::pop()
{//ɾ��ջ�����,���ر�ɾ����ֵ
	stacknode* temp = top;//��temp�ݴ���
	top = top->link;//����topָ��
	Type reval = temp->data;//reval�ݴ�Ҫ���صĽ���ֵ
	delete temp;//ɾ��ջ�����
	return reval;//����ԭջ������ֵ
}
template <class Type> void stack<Type>::make_empty()
{//���ջ
	while (top) {//�ظ�����ֱ��top==NULL
		stacknode* temp = top;
		top = top->link;
		delete temp;
	}
}



class family_tree;
class family_treenode {//��������㣨���׳�Ա����
	friend class family_tree;
	char* name;//��Ա��
	family_treenode* first_child, * next_sibling;//ָ�����ӣ����ֵ�
	int visit=0;//ɾ����Ա�������ʱ��������
	family_treenode(char* n=NULL) :name(n),first_child(NULL),next_sibling(NULL) {};//���캯��
	family_treenode(family_treenode* ftn) :name(ftn->name),first_child(ftn->first_child),next_sibling(ftn->next_sibling) {};//���ƹ��캯��
};
class family_tree {
public:
	family_tree() :ancestor(NULL), current(NULL) {};//�޲ι��캯��
	family_tree(char *n);//��������Ϊ�����Ĺ��캯��
	~family_tree();//��������������ͬmake_empty()
	void add_member(int build_or_add);//Ϊ��Ա������ͥ�������Ů
	void dissolve_family(int all=0);//��ɢĳ�˵ļ�ͥ,��allΪ1�����ɢ���ȵļ�ͥ
	void change_name();//����ĳ�˵�����
	void make_empty();//��ռ���
private:
	family_treenode* ancestor,*current;//����ָ����ڵ��ָ���ָ��ǰ�ڵ��ָ��
	family_treenode* preorder(char *n);//ǰ�����������Ϊ*n�Ľ��λ��
};
family_tree::family_tree(char* n) 
{//��������Ϊ�����Ĺ��캯��
	ancestor = current = new family_treenode(n);
}
family_tree::~family_tree()
{
	make_empty();
}
family_treenode* family_tree::preorder(char* n)
{//ǰ�����������Ϊ*n�Ľ��
	current = ancestor;//�Ӹ��ڵ㿪ʼ����
	stack<family_treenode*> st;
	while (current||!st.is_empty()) {
		while (current != NULL && strcmp(current->name,n)!=0) {//һ�󵽵�
			st.push(current);//�������Ľ�㶼��ջ
			current = current->first_child;//����������
		}
		if (current!=NULL&&strcmp(current->name, n)==0)//�ҵ�Ŀ����
			return current;
		//current==NULL
		current = st.pop()->next_sibling;//currentָ�����δ�����ʵĸ��ڵ��������
	}
	return current;
}
void family_tree::add_member(int build_or_add)
{//build_or_andΪ0��������ͥ��Ϊ1��Ϊĳ�����ڼ�������Ӷ�Ů
	char* parent=new char[20];//Ҫ������ͥ���˵�����
	int num=1;//Ҫ��ӵ���Ů��
	family_treenode* temp=current;//һ��ʼָ���ӣ��������������parent�ĵ�һ������
	if(build_or_add==0)
	    cout << "������Ҫ������ͥ���˵�������";
	else
		cout << "������Ҫ��Ӷ��ӻ�Ů�����˵�������";
	cin >> parent;
	preorder(parent);//����parent��ʹcurrentָ����λ��
	if (current == NULL) {
		cout << parent << "�����ڣ�" << endl;
			return;
	}
	if (build_or_add == 0) {
		cout << "������" << parent << "�Ķ�Ů������";
		cin.ignore(20, '\n');
		while (1) {
			cin >> num;
			if (!cin.good()||num <= 0  ) {
				cout << "�����������������:";
				cin.ignore(100, '\n');
				cin.clear();
			}
			else
				break;
		}
	}
	if (build_or_add == 0)
		cout << "����������" << parent << " �Ķ�Ů��������";
	else
		cout << "������" << parent << "����ӵĶ��ӣ���Ů������������";
	for (int i = 0; i < num; i++) {//�����ɻ�������Ů�����Ķ�ȡ���ڼ����еĲ���
        char* child = new char[20];//��Ů������
		cin >> child;
		if (i == 0) {//�����һ������
			if (build_or_add == 1) {
				if (current->first_child!=NULL) {
					current = current->first_child;
					temp = current;//tempָ����
				    while (current->next_sibling!=NULL) //�����һ�����Ӻ�����º���
						current = current->next_sibling;
					current->next_sibling = new family_treenode(child);//��ɲ����º���
				}
				else {
					current->first_child = new family_treenode(child);//��ɲ����º���
					temp = current->first_child;
				}
				
			}
			else {
				current->first_child = new family_treenode(child);//����parent�ĳ���
				temp = current->first_child;//ָ����
				current = current->first_child;//currentָ��ձ�����ĺ��ӣ�Ϊ������һ��������׼��
			}
		}
		else {
			current->next_sibling = new family_treenode(child);//����parent�ǳ��ӵĺ��Ӽ����볤�ӵ����ֵ�
			current = current->next_sibling;//currentָ��ձ�����ĺ��ӣ�Ϊ������һ��������׼��
		}
	}
	cout << parent << "�ĵ�һ�������ǣ�";
	for (int i = 0;temp!=NULL; i++) {//�������parent�ĵ�һ������
		cout << temp->name<<"     ";//�����ǰ���ӵ�����
		temp = temp->next_sibling;//tempָ����һ������
	}
	cout << endl;
}
void family_tree::dissolve_family(int all) 
{//��ɢ��*parentΪ�����˵ļ�ͥ,��all==1ʱ�൱����������������������ȣ�
	char* parent = new char[20];//Ҫ��ɢ��ͥ���˵�����
	family_treenode* p;//���ڱ���parent��λ��
	if (all == 1)
		parent = ancestor->name;
	if (all == 1) {
		parent = ancestor->name;
		p = preorder(parent);//����parent��ʹpָ����λ��
	}
	else {
		cout << "������Ҫ��ɢ��ͥ���˵�������";
		cin >> parent;
	    p=preorder(parent);//����parent��ʹpָ����λ��
	    if (current == NULL) {
			cout << parent << "�����ڣ�" << endl;
		return;
		}
		cout << "Ҫ��ɢ��ͥ�����ǣ�" << parent << endl;
		cout << parent << "�ĵ�һ�������ǣ�";
	}
	family_treenode* temp;
	if (!all) {//����������չ��ܣ���Ҫ�������ɢ��ͥ���˵ĵ�һ������
	    temp = current->first_child;//tempָ����
		for (int i = 0; temp; i++) {//�������parent�ĵ�һ������
			cout << temp->name << "     ";//�����ǰ���ӵ�����
			temp = temp->next_sibling;//tempָ����һ������
		}
		cout << endl;
	}
	current= p->first_child;//currentָ����
	stack<family_treenode*> st;//�洢����;�о�����δ�����ʵĽ��
	while (current || !st.is_empty()) {//ɾ������
		while (current) {//һ�󵽵�
			if (current->visit >= 2)//������Ҳ������ϸýڵ��ΪҶ���
				break;
			st.push(current);//�������Ľ�㶼��ջ
			current = current->first_child;//����������
		}
		current = st.gettop();
		current->visit++;
		if (current->next_sibling==NULL) {//��ǰ�ڵ����������Ҳ������������Ҷ�ڵ㣬������parent��ɾ��
			family_treenode* temp1;
			temp1 = current;
			if(!st.is_empty())
				st.pop();//����ջ
			if (st.is_empty())//ջ��������Ԫ���Ѵ����꣬�˳�ѭ��
				break;
			current = st.gettop();//currentָ����һ��δ�����ʵĽ��
			current->next_sibling = temp1->next_sibling;//current���ֵ��ÿ�
			p->first_child= temp1->next_sibling;//ʹparent�ĳ���Ϊ��
			if(current)
			    current->visit++;
			delete temp1;//�ͷ�temp���
		}
		else//��ǰ�������Һ��ӣ������������
		    current = current->next_sibling;//currentָ���Һ���
	}
}
void family_tree::change_name()
{//���ĵ�ǰ����Ϊ*cur_name���˵�����
	char* name = new char[20];//Ҫ�޸ĵ��˵�������
	char* toname = new char[20];//���ĺ������
	cout << "������Ҫ�����������˵�Ŀǰ������";
	cin >> name;
	preorder(name);////ǰ�����������Ϊ*name�Ľ��λ��
	if (current == NULL) {
		cout << name << "�����ڣ�" << endl;
		return;
	}
	cout << "��������ĺ��������";
	cin >> toname;
	current->name = toname;
	cout << name << "�Ѹ���Ϊ" << toname<<endl;
}
void family_tree::make_empty()
{
	dissolve_family(1);//ɾ��ancestor�������Ӵ�
	delete ancestor;//�ͷ�ancestor
}


int main()
{
	char* ancestor_name = new char[20];//��������
	char menu_chocie;//�˵�ѡ��
	cout << "**          ���׹���ϵͳ          **"<<endl;
	cout << "=====================================" << endl;
	cout << "**       ��ѡ��Ҫִ�еĲ�����     **" << endl;
	cout << "**         A---���Ƽ�ͥ           **" << endl;
	cout << "**         B---��Ӽ�ͥ��Ա       **" << endl;
	cout << "**         C---��ɢ�ֲ���ͥ       **" << endl;
	cout << "**         D---���ļ�ͥ��Ա����   **" << endl;
	cout << "**         E---�˳�����           **" << endl;
	cout << "=====================================" << endl;
	cout << "���Ƚ���һ�����ף�" << endl;
	cout << "���������ȵ�������";
	cin >> ancestor_name;
	family_tree ft(ancestor_name);//����һ����ancestors_nameΪ���ȵļ���
	cout << "�˼��׵������ǣ�" << ancestor_name<<endl;
	cout << endl;
	while (1) {
		cout << "��ѡ��Ҫִ�еĲ�����";
		while (1) {//���봦��
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
				cout << "����������������룺";
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
			cout << "���������";
			return 0;
		default:
			break;
		}
	}
	return 0;
}
#include <iostream>
#include <cstring>
using namespace std;
class linklist;
class listnode {
	friend class linklist;
	char *num;//׼��֤��
	char *name;//����
	char *sex;//�Ա�
	char *age;//����
	char *work;//�������
	listnode* link;//���ָ��
public:
	listnode() :link(NULL) {};//�����㹹�캯��
	listnode(char* nu, char* na, char* se, char *ag, char* wo, listnode* li = NULL) :num(nu), name(na), sex(se), age(ag), work(wo), link(li) {};//�����㹹�캯��
	listnode(const listnode& ln);//�����㸴�ƹ��칹�캯��	
};
class linklist {
public:
	linklist() { last = first = new listnode(); };//�����캯��������ͷ��㣩
	~linklist();//��������
	void add(listnode l, int pos = NULL);//��l�����λ��i����δ��i���ݲ�������ĩβ���l���
	int del(const char* n);//������Ϊn�Ŀ�����Ϣɾ��
	listnode* find(const char* n);//���ҿ���Ϊn�Ŀ�����Ϣ
	int modify(const char* n, listnode newnode);//������Ϊn�Ŀ�����Ϣ��Ϊnewnode
	int sum();//ͳ�������п���������������ӡ����
	void MakeEmpty();//ɾ�����ÿ�
	int print(char *nu = NULL);//��ӡ�������ݣ�����*nu�����˲�����ֻ��ӡѧ��Ϊ*nu�Ŀ�����Ϣ
private:
	listnode* first, * last;//��ͷָ�룬��βָ��
};
listnode::listnode(const listnode& ln)
{//��ln���
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
{//��������
	MakeEmpty();//�����ÿ�
	delete first;//ɾȥ��ͷ���
}
void linklist::add(listnode l, int pos)
{//��listnode l���뵽�����pos��λ��,��δ��pos��ֵ������뵽ĩβ
	if (pos == NULL) {
		last->link = new listnode(l);
		last = last->link;
		return;
	}
	listnode* current = first;//���ָ��currentָʾ��ͷ���
	int i = 0;
	while (i < pos-1 && current->link != NULL) {//��pָ����������λ��ǰһλ������ĩβ
		i++;
		current = current->link;
	}
	listnode *n=new listnode(l);//�����½��
	n->link = current->link;
	current->link = n;//ʵ�ֲ����½��
	if (n->link == NULL)//����ĩβָ��
		last = n;
}
int linklist::del(const char* n)
{//ɾ������Ϊn�Ŀ�����Ϣ
	listnode* current = find(n);//currentָ��Ŀ����ǰһ�����
	if (current == NULL) {//pָ��ΪNULL��˵�����Ҷ��󲻴���
		cout << "�ÿ��������ڣ�" << endl;
		return 0;
	}
	listnode* q = current->link;//qָ��ָ���ɾ�����
	current->link = q->link;
	cout << "��ɾ���Ŀ�����Ϣ�ǣ�" << q->num << "   " << q->name << "   " << q->sex << "   " << q->age << "   " << q->work << endl;
	delete q;//ɾ��Ŀ��ڵ�
	return 1;
}
listnode* linklist::find(const char* n)
{//�������д�ͷ����ѧ��numΪn�Ľ�㡣�����ڣ����ظý��ǰһ������ַ���������ڣ�����NULL
	listnode * current = first;//���ָ��currentָ���ͷ���
	while (current != NULL) {
		if (current->link!=NULL&&strcmp(current->link->num, n) == 0)
			return current;//current����һ�����ΪĿ����ʱ����p��
		current = current->link;
	}
	return current;
}
int linklist::modify(const char* n, listnode newnode)
{//������Ϊn�Ŀ�����Ϣ��Ϊnewnode�е���Ϣ
	listnode* current = find(n);//currentָ��Ŀ����ǰһ�����
	if (current == NULL) {//currentָ��ΪNULL��˵�����Ҷ��󲻴���
		cout << "�ÿ��������ڣ�" << endl;
		return 0;
	}
	current = current->link;//currentָ����޸Ľ��
	strcpy(current->num,newnode.num);//�޸�currentָ���������
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
{//ɾȥ�����г���ͷ�����������������
	listnode* current;
	while (first->link != NULL) {
		current = first->link;
		first->link = current->link;//����һ������������ժ��
		delete current;//ɾ��ժ�µĽ��
	}
	last = first;//�޸ı�βָ��
}
int linklist::print(char *nu)//�޲δ������ӡ�������飬�в����ӡ����Ϊnu�Ŀ�����Ϣ
{
	if (first->link == NULL)//���
		return 0;
	listnode* current;
	if (nu != NULL) {
		current = find(nu);
		if(current ==NULL)
			return 0;
		else {
			current = current->link;
			cout << "����                ����      �Ա�  ����  �������" << endl;
			printf("%-20s%-10s%-6s%-6s%s\n", current->num, current->name, current->sex, current->age, current->work);
			return 1;
		}
	}
	current = first;//�޲������ݣ���ӡ�����������ָ��pָ���ͷ���
	cout << "����                ����      �Ա�  ����  �������" << endl;
	while (current->link != NULL) {
		current = current->link;
		printf("%-20s%-10s%-6s%-6s%s\n", current->num, current->name, current->sex, current->age, current->work);
	}
	return 1;
}

int main()
{
	int stu_num, program;//�ֱ��ʾ����������ѡ������ı��
	linklist ll;//����һ���������
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼��������" ;
	while (1) {
		cin >> stu_num;
		if (cin.good()&&stu_num>0)
			break;
		else {
			cout << "�������������һ����������";
			cin.clear();
			cin.ignore(100, '\n');
		}
	}
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	char *num=new char[20], * name = new char[20], * sex = new char[2],*age=new char[3], * work = new char[20];//�ֱ𴢴������ѧ�š��������Ա����䡢�������
	for (int i = 0; i < stu_num; i++) {
 		cin >> num >> name >> sex >> age >> work;
		while (!(age > 0)) {
			cout << "����Ϊ" << num << "�Ŀ������������������������ÿ�����Ϣ��" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cin >> num >> name >> sex >> age >> work;
		}
		listnode newnode(num, name, sex, age, work);
		ll.add(newnode);
	}//!!!��������������ݺ�������
	ll.print();
	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
	while (1) {
		cout << "��ѡ����Ҫ���еĲ�����";
		cin >> program;
		switch (program) {
		case 1:
			int pos;//Ҫ�����λ��
			cout << "����������Ҫ����Ŀ�����λ�ã�";
			cin >> pos;
			{int length = ll.sum();
			while (pos<1 || pos>length + 1) {
				cout << "λ���������������1-" << length + 1 << "��������\n";
				cin >> pos;
			}
			}
			cout << "����������Ҫ���뿼���Ŀ��š��������Ա����估�������\n";
			cin >> num >> name >> sex >> age >> work;
			{listnode newnode(num, name, sex, age, work);//����һ���Ը��������ϢΪ���ݵ��½��
			ll.add(newnode, pos); }//�����½��
			cout << endl;
			ll.print();//��ӡ����
			break;
		case 2:
			cout << "������Ҫɾ���Ŀ����Ŀ��ţ�";
			cin >> num;
			if(ll.del(num)) {//del�������ز�Ϊ0��˵��ɾ���ɹ�����ӡ����
				cout << endl;
				ll.print();//��ӡ����
			}
			break;
		case 3:
			cout << "������Ҫ���ҵĿ����Ŀ��ţ�";
			cin >> num;
			cout << endl;
			if (!ll.print(num))
				cout << "�ÿ��Ų����ڣ�" << endl;
			break;
		case 4:
			cout << "������Ҫ�޸ĵĿ����Ŀ��ţ�";
			cin >> num;
			cout << endl;
			if (!ll.print(num))
				cout << "�ÿ��Ų����ڣ�" << endl;
			else {
				char* newnum=new char[20];
				cout << "����������ÿ���������Ϣ�����š��������Ա����估�������\n";
				cin >> newnum >> name >> sex >> age >> work;
				listnode newnode(newnum, name, sex, age, work);//���������������ϢΪ���ݵĽ��
				ll.modify(num, newnode);//���������޸�ԭ����Ϊnum�Ľ����ϢΪnewnode
				cout << "�޸ĳɹ���\n";
				ll.print();
			}
			break;
		case 5:
			cout <<"��ǰ������������"<< ll.sum() << endl;//���ͳ�ƵĿ�������
			ll.print();//��ӡ��ǰȫ��������Ϣ
			break;
		case 0:
			return 0;
			break;
		default: 
			cout << "������Ĳ����벻���ڣ����������룡" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			break;
		}
	}
	return 0;
}
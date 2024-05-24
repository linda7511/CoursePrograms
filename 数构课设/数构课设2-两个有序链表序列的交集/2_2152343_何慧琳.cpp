#include <iostream>
using namespace std;
class List;
class Listnode {//��������
	friend List;
	int data;//���ֵ
	Listnode* link;//ָ��ǰ�ڵ����һ�����
public:
	Listnode() :link(NULL) {};//�����㹹�캯��
	Listnode(int i) :data(i), link(NULL) {};//�����㹹�캯��
};
class List {
public:
	List() { first = new Listnode(); };//�����캯��
	~List();//��������
	void read();//���������ݶ�������ĺ���
	void AND(List &list2);//ȡ�������������
	void Makeempty();//ɾ������ͷ������н��
private:
	Listnode* first;//ͷָ��
};
List::~List()
{//��������
	Makeempty();
	delete first;
}
void List::read()
{//���������ݶ�������
	cout << "������һ�����������������ɵķǽ������У���-1��β����";
	int i;//��ʾ��ǰ��������
	Listnode* current=first;
	while (1) {
		cin >> i;
		if (cin.fail() || (i <= 0 && i != -1)) {
			cout << "�����������������������У�";
			cin.clear();
			cin.ignore(INT_MAX,'\n');//����� 
			Makeempty();//�������벿�����ݵ������ÿ�
			current = first;//current����ָ��ͷ���
			continue;
		}
		if (i == -1)
			break;
		current -> link = new Listnode(i);
		current = current->link;
	}
}
void List::AND(List& list2)
{//ȡ�������������
	List ans;//�洢�������
	Listnode* current = ans.first;//ָ��ans�����ָ��
	Listnode* cur1=first->link,* cur2=list2.first->link;//this�����list2����ļ��ָ��
	while (cur1 != NULL && cur2 != NULL) {//�������о�δ����
		if (cur1->data == cur2->data) {//һ���������������ж�����������������
			current->link = new Listnode(cur1->data);
			current = current-> link;//ansָ�������һλ
			cur1 = cur1->link;//cur1ָ�������һλ
			cur2 = cur2->link;//cur2ָ�������һλ
		}
		else if (cur1->data < cur2->data) {//cur1ָ�����С��cur2ָ�������cur1ָ����һλcur2����
			cur1 = cur1->link;
		}
		else if (cur1->data > cur2->data) //cur1ָ�����С��cur2ָ�������cur2ָ����һλcur1����
			cur2 = cur2->link;
	}
	cout << "����S3��";
	current = ans.first->link;//current�ٴ�ָ���һ�����
	if (current == NULL) {//ansΪ�ձ�
		cout << "NULL" << endl;
	}
	while (current != NULL) {
		cout << current->data;
		if ((current = current->link) != NULL)//currentָ����һ����㣬��һ�����ǿ������һ���ո�
			cout << " ";
		else
			cout << endl;
	}
	cout << endl;
}
void List::Makeempty()
{//�����ÿպ�����ɾ������ͷ������нڵ�
	Listnode* current;
	while (first->link != NULL) {
		current = first->link;//�����˱�ͷ���
		first->link = current->link;//����һ������������ժ��
		delete current;//�ͷŸý��
	}
}
int main()
{
	List S1, S2;
	while (1) {
		cout << "������S1" << endl;
		S1.read();
		cout << "������S2" << endl;
		S2.read();
		S1.AND(S2);
		cout << "�Ƿ��������y/n��";
		char go_on;
		cin >> go_on;
		while (go_on != 'y' && go_on != 'n') {//�������
			cout << "����������������루y/n��";
			cin.ignore(100, '\n');
			cin.clear();
			cin >> go_on;
		}
		if (go_on == 'n')
			break;
		else {//�������ÿ�S1��S2
			S1.Makeempty();
			S2.Makeempty();
		}
	}
	return 0;
}
#include <iostream>
using namespace std;

int C(int a, int b)
{//���µ�Ϊa�ϵ�Ϊb�������
	int ans=1,j=1;
	for (; j <= b; a--, j++)
		ans=ans* a / j;
	return ans;
}

int main()
{
	int choice,m,n;
	cout << "����������1/2ѡ��汾Q1/Q2��";
	while (1) {
		cin >> choice;
		if (cin.fail() || (choice != 1 && choice != 2)) {
			cout << "����������������룺";
			cin.clear();
			cin.ignore();
		}
		else
			break;
	}
	cout << "�����벽��m�Ϳ�·����n���ÿո��������س���β����";
	while (1) {
		cin >> m>>n;
		if (cin.fail()) {
			cout << "������������������������֣�";
			cin.clear();
			cin.ignore();
		}
		else
			break;
	}
	if (m<0 || m>n) {
		cout << 0;
		return 0;
	}
	if (choice == 1) {//���������m�����Ŀ�·�ﲻ����n�ķ�����
		int t = min(m / 2, n / 3),s,ans=0;//tΪ�������ĸ���,sΪ��һ���ĸ�����ans��¼���з�����
		while (t >= 0) {
			s = m - 2 * t;
			if (s + 3 * t <= n)//��s��һ����t���������Ŀ�·�ﲻ����n�����У�ans��¼����ϵ�����
				ans += C(s + t, t);
			t--;//t����0�����ÿ��s��t�Ĵ����Ƿ����
		}
		cout << ans;
	}
	else {//�����m�����Ŀ�·����󵫲�����n�ķ�����
		int t = min(m / 2, n / 3), s, ans = 0;//tΪ�������ĸ���,sΪ��һ���ĸ�����ans��¼���з�����
		while (t >= 0) {
			s = m - 2 * t;
			if (s + 3 * t <= n) {
				//tԽС���ĵĿ�·����ԽС����������Ŀ�·�������з���
				//���ҵ���һ�����������ķ���������������
				ans = C(s + t, t);
				break;
			}
			t--;
		}
		cout << ans;
	}
	return 0;
}
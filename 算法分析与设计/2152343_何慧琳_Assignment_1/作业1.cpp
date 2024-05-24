#include <iostream>
using namespace std;

int C(int a, int b)
{//求下底为a上底为b的组合数
	int ans=1,j=1;
	for (; j <= b; a--, j++)
		ans=ans* a / j;
	return ans;
}

int main()
{
	int choice,m,n;
	cout << "请输入数字1/2选择版本Q1/Q2：";
	while (1) {
		cin >> choice;
		if (cin.fail() || (choice != 1 && choice != 2)) {
			cout << "输入错误！请重新输入：";
			cin.clear();
			cin.ignore();
		}
		else
			break;
	}
	cout << "请输入步数m和卡路里数n（用空格间隔，按回车结尾）：";
	while (1) {
		cin >> m>>n;
		if (cin.fail()) {
			cout << "输入错误！请重新输入两个数字：";
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
	if (choice == 1) {//输出所有走m步消耗卡路里不超过n的方案数
		int t = min(m / 2, n / 3),s,ans=0;//t为跨两步的个数,s为走一步的个数，ans记录可行方案数
		while (t >= 0) {
			s = m - 2 * t;
			if (s + 3 * t <= n)//走s个一步和t个两步消耗卡路里不超过n，可行，ans记录该组合的数量
				ans += C(s + t, t);
			t--;//t逐渐至0，检查每种s、t的搭配是否可行
		}
		cout << ans;
	}
	else {//输出走m步消耗卡路里最大但不超过n的方案数
		int t = min(m / 2, n / 3), s, ans = 0;//t为跨两步的个数,s为走一步的个数，ans记录可行方案数
		while (t >= 0) {
			s = m - 2 * t;
			if (s + 3 * t <= n) {
				//t越小消耗的卡路里数越小，欲输出消耗卡路里最大可行方案
				//即找到第一个满足条件的方案并输出其组合数
				ans = C(s + t, t);
				break;
			}
			t--;
		}
		cout << ans;
	}
	return 0;
}
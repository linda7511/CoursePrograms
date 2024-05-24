#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
using namespace std;
clock_t start_, end_;

vector<vector<int > > grid;
int Max = 0, m, n;


// 判断是否越界 或 走到了无金子位置
bool ifNotEnd(int x, int y) {
	if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 0) {
		return false;
	}
	return true;
}

//判断某位置上下左右有几个方向邻接了有矿位置
int OpenDerection(int x, int y) {
	int ans = 0;
	ans += ifNotEnd(x + 1, y);
	ans += ifNotEnd(x - 1, y);
	ans += ifNotEnd(x, y + 1);
	ans += ifNotEnd(x, y - 1);
	return ans;
}

void dfs(int NowGold, int x, int y) {
	if (!ifNotEnd(x, y)) { // 判断是否越界或到无金子位置，结束
		return;
	}
	int temp = grid[x][y];
	NowGold += grid[x][y];
	Max = max(Max, NowGold); // 更新最大值
	grid[x][y] = 0; // 防止出现重复遍历
	dfs(NowGold, x + 1, y); //向上
	dfs(NowGold, x - 1, y); //向下
	dfs(NowGold, x, y + 1); //向左
	dfs(NowGold, x, y - 1); // 向右
	grid[x][y] = temp; // 回溯
}
//求最大受益
void getMaximumGold() {
	m = grid.size(), n = grid[0].size();
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (grid[i][j] && OpenDerection(i, j) != 2) {//从每个非0且通路方向不为2的位置开始dfs 
				dfs(0, i, j);
			}
}


int main() {

	//	读取测试数据 
	string lineStr;
	cin >> lineStr;

	start_ = clock();


	//	初始化grid 
	int i = 0;
	vector<int> line;
	bool num_end = false;
	bool line_end = false;
	string number;
	while (lineStr[i])
	{
		if ((lineStr[i] >= 'a' && lineStr[i] <= 'z') || lineStr[i] == '=') {
			i++;
			continue;
		}
		if (!num_end) {
			if (lineStr[i] == '[') {
				line_end = false;
				line.clear();
			}
			else if (lineStr[i] == ']' && line_end) {
				number = "";
				num_end = true;
			}
			else if (lineStr[i] == ']' && !num_end) {
				line.push_back(atoi(number.c_str()));
				grid.push_back(line);
				line_end = true;
				number = "";
			}

			else if (lineStr[i] >= '0' && lineStr[i] <= '9')number += lineStr[i];
			else if (lineStr[i] == ',' && !line_end) {
				line.push_back(atoi(number.c_str()));
				number = "";
			}
		}
		i++;
	}
	getMaximumGold();
	cout << Max<<endl;

	end_ = clock();
	double endtime = (double)(end_ - start_) / CLOCKS_PER_SEC;


	cout << "用时:" << endtime * 1000 << "ms" << endl;

	system("pause");

	return 0;
}

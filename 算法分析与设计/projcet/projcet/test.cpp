#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

clock_t start_,end_;

using namespace std;

bool if_find(vector<vector<int> >& matrix, int target,int left,int right,int top,int bottom,int row_or_col)
{
	int midi=(top+bottom)/2,midj = (right + left) / 2; 
	if (left > right || top > bottom)
		return 0;
	if (row_or_col == 0) {//竖向二分
		int bottom1 = bottom, top1 = top;
		while ( bottom1- top1 >= 0) {
			midi = (top1 + bottom1) / 2;
			if (target == matrix[midi][midj])
				return 1;
			else if (target < matrix[midi][midj]) {
				bottom1 = midi;
			}
			else if (target > matrix[midi][midj]) {
				top1 = midi + 1;
			}
		}
		if(if_find(matrix, target, left, midj - 1, top1, bottom, 0))
			return 1;
		if(if_find(matrix, target, midj + 1, right, top1 - 1, top, 0))
			return 1;
	}
	else{//横向二分
		int left1 = left, right1 = right;
		while (right1 - left1>=0) {
			midj = (right1 + left1) / 2;
			if (target == matrix[midi][midj])
				return 1;
			else if (target < matrix[midi][midj]) {
				right1 = midj;
			}
			else if (target > matrix[midi][midj]) {
				left1 = midj + 1;
			}
		}
		if(if_find(matrix, target, left, right1, midi-1, bottom, 0))
			return 1;
		if(if_find(matrix, target, left1 + 1, right, top, midi + 1, 0))
			return 1;
	}
	return 0;
}

bool searchMatrix(vector<vector<int> >& matrix, int target){
        //TODO  二分法
	int m = matrix.size(),n=matrix[0].size();//获取行列数
	int left = 0, right = n-1,top=0,bottom=m-1,row_or_col=m<n?0:1;
	return if_find(matrix, target, left, right, top,bottom,row_or_col);
}


int main(){
	
//	读取测试数据 
    ifstream inFile("testcase.csv", ios::in);
    string lineStr;
    
    start_ = clock();
    

	if (!inFile.is_open())
	{
		cout<<"Error!"<<endl;
	}
	
//	测试结果标记
	int correct_num = 0;
	int error_num = 0;
	

//	运行测试数据，输出结果 
    while (getline(inFile, lineStr))
    {
    	vector<vector<int>> matrix;
		
    	string number;
    	bool num_end = false;
    	bool line_end = false;
    	int target = -1;
    	bool result;
    	vector<int> line;
    	for(int i=0; i<lineStr.size(); i++){
    		if (!num_end){
	    		if (lineStr[i] == '['){
	    			line_end = false;
	    			line.clear();
				}
				else if (lineStr[i] == ']' && line_end){
					number = "";
					num_end = true;
				}
	    		else if (lineStr[i] == ']' && !num_end){
	    			line.push_back(atoi(number.c_str()));
	    			matrix.push_back(line);
	    			line_end = true;
	    			number = "";
				}
				
				else if (lineStr[i] >= '0' && lineStr[i] <= '9')number += lineStr[i];
				else if (lineStr[i] == ',' && !line_end){
					line.push_back(atoi(number.c_str()));
					number = "";
				}
			}
			else{
				if (target == -1){
					if (lineStr[i] >= '0' && lineStr[i] <= '9')number += lineStr[i];
					else if (lineStr[i] == ',' && number != "")target = atoi(number.c_str());
				}
				else result = lineStr[i]-'0';
			}
		}
		if (result == searchMatrix(matrix,target))correct_num += 1;
		else error_num += 1;
	}
	end_ = clock();
	double endtime = (double)(end_ - start_)/CLOCKS_PER_SEC;
	inFile.close();
	
	cout<<"correct:"<<correct_num<<endl;
	cout<<"error:"<<error_num<<endl;
	cout<<"用时:"<<endtime*1000<<"ms"<<endl;
	
	system("pause");
	
	return 0;
}

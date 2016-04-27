/*created by LRC-cheng*/
#include<iostream>
#define NUM 50
using namespace std;

int PARTITION(int[], int, int);		//划分
int SELECT(int[], int, int, int);

int main(){
	cout << "===============选择算法=============" << endl;
	cout << "请输入数值：" << endl;
	int *A;
	int z,x;
	A = new int[NUM];
	int p = 0, r = -2;		//r为数组下标

	for (int i = 0;; i++){
		cin >> A[i];
		r++;
		if (cin.fail()){		//当输入的不是数字时退出输入,但错误数据还在缓冲区！
			break;
		}
	}
	cin.clear();		//重置错误输入
	cin.sync();		//清空缓冲区  
	cout << "要找的元素序：";
	cin >> z;
	x = SELECT(A, p, r, z);
	cout << "结果为：" << x << endl;

	delete[]A;
	system("pause");
	return 0;
}

int PARTITION(int A[], int p, int r){
	int x, i, temp;
	x = A[r];
	i = p - 1;
	for (int j = p; j <= r - 1; j++){
		if (A[j] <= x){				//A[j]<=A[r]时，把A[j]移到p前一格,修改符号即可改变升降序
			i++;
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}
	temp = A[i + 1];
	A[i + 1] = A[r];
	A[r] = temp;

	return i + 1;
}

int SELECT(int A[], int p, int r, int i){	//选择数据
	int q, k;
	if (p == r)
		return A[p];
	q = PARTITION(A, p, r);
	k = q - p + 1;
	if (i == k)
		return A[q];
	else if (i < k)
		return SELECT(A, p, q - 1, i);
	else return SELECT(A, q + 1, r, i - k);
}

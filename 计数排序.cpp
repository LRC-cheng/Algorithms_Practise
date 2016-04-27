/*created by LRC-cheng*/
#include<iostream>
using namespace std;

void COUNTING_SORT(int[], int[], int);		//计数排序，初始值：数组A[],B[],C的下标k
int l;									//数组A的下标

int main(){
	int A[8] = { 2, 5, 3, 0, 2, 4, 1, 3 }, B[8] = {0};
	cout << "==================计数排序==================" << endl;
	cout << "请输入排序数据：" << endl;
	l = 7;
	for (int i = 0; i < 8; i++){
		cout << A[i] << "  ";
	}
	cout << endl;
	COUNTING_SORT(A, B, 6);
	for (int i = 0; i < 8; i++){
		cout << B[i] << "  ";
	}
	cout << endl;

	system("pause");
	return 0;
}

void COUNTING_SORT(int A[], int B[], int k){		//计数排序，初始值：数组A[],B[],C的下标k
	int *C;
	C = new int[k];
	for (int i = 0; i < k; i++){		//初始化数组C
		C[i] = 0;
	}
	for (int j = 0; j <= l; j++){		//计算数据个数
		C[A[j]] = C[A[j]] + 1;
	}
	for (int i = 1; i < k; i++){		//计算其序号
		C[i] = C[i] + C[i - 1];
	}
	for (int j = l; j >= 0; j--){
		C[A[j]] = C[A[j]] - 1;		//C[A[j]]为A[j]在输出数组的位置
		B[C[A[j]]] = A[j];		//把A[j]输出到B中
	}

	delete[]C;
}

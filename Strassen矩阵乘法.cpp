#include<iostream>
#define SIZE 30
#include"Function.h"
using namespace std;

int main(){
	int n;
	cout << "----------------Strassen矩阵乘法运算------------------" << endl;
	cout << "请输入方阵规模（n=2^x）：" << endl;
	cin >> n;
	int **A, **B, **C;
	//动态申请二维数组
	A = new int *[SIZE];
	B = new int *[SIZE];
	C = new int *[SIZE];			
	for (int i = 0; i < n; i++){
		A[i] = new int[SIZE];
		B[i] = new int[SIZE];
		C[i] = new int[SIZE];
	}

	cout << "请输入矩阵A：" << endl;
	for (int i = 0; i < n; i++){				//输入矩阵A
		for (int j = 0; j < n; j++){
			cin >> A[i][j];
		}
	}
	cout << "请输入矩阵B：" << endl;
	for (int i = 0; i < n; i++){				//输入矩阵A
		for (int j = 0; j < n; j++){
			cin >> B[i][j];
		}
	}

	system("cls");	//清屏

	cout << "本次计算的矩阵A：" << endl;
	for (int i = 0; i < n; i++){				//显示矩阵A
		for (int j = 0; j < n; j++){
			cout << A[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	cout << "本次计算的矩阵B：" << endl;
	for (int i = 0; i < n; i++){				//显示矩阵B
		for (int j = 0; j < n; j++){
			cout << B[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << endl;

	Strassen(A, B, C, n);

	cout << "结果为：" << endl;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cout << C[i][j] << "\t";
		}
		cout << endl;
	}
	cout<<endl;

	for (int i = 0; i < n; i++){
		delete[] A[i];
		delete[] B[i];
		delete[] C[i];
	}
	delete[] A; 
	delete[] B;
	delete[] C;

	system("pause");
	return 0;
}

//made by lrc
#include<iostream>
#define NUM 1000
using namespace std;

void BUBBLESORT(int[],int);

int main(){

	cout << "================冒泡排序===============" << endl;

	int *Array;
	Array = new int[NUM];
	int l = -1;				//r为数组长度
	for (int i = 0;; i++){
		cin >> Array[i];
		l++;
		if (cin.fail()){		//当输入的不是数字时退出输入
			break;
		}
	}

	BUBBLESORT(Array, l);		//冒泡排序

	cout << "结果为：";
	for (int i = 0; i < l; i++){
		cout << Array[i] << "   ";
	}
	cout << endl;

	delete[]Array;
	system("pause");
	return 0;
}

void BUBBLESORT(int A[],int lenght){			//由小到大排序
	int temp;
	for (int i = 1; i < lenght ; i++){
		for (int j = 0; j < lenght; j++){
			if (A[i] < A[j]){
				temp = A[i];
				A[i] = A[j];
				A[j] = temp;
			}
		}
	}
}
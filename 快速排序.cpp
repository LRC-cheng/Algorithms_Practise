#include<iostream>
#define NUM 1000
using namespace std;

void QUICKSORT(int[], int, int);
int PARTITION(int[], int, int);

int main(){
	cout << "=================快速排序================" << endl;
	cout << "请输入排序数值：" << endl;
	int *A;
	A = new int[NUM];
	int p = 0, r = -2;		//r为数组下标

	for (int i = 0;; i++){
		cin >> A[i];
		r++;
		if (cin.fail()){		//当输入的不是数字时退出输入
			break;
		}
	}
	QUICKSORT(A, p, r);		//快速排序


	cout <<"-------------------------------------------"<< endl;	//输出
	for (int i = 0; i < r + 1; i++){
		cout << A[i] << "  ";
	}
	cout << endl;


	delete[]A;
	system("pause");
	return 0;
}



void QUICKSORT(int A[], int p, int r){
	int q;
	if (p < r){
		q = PARTITION(A, p, r);
		QUICKSORT(A, p, q - 1);	//分组，q是中间值，不用再排
		QUICKSORT(A, q + 1, r);	//分组
	}
}

int PARTITION(int A[], int p, int r){
	int x,i,temp;
	x = A[r];
	i = p - 1;
	for (int j = p; j <= r - 1; j++){
		if (A[j] <= x){				//A[j]<=A[r]时，把A[j]移到p前一格,修改符号即可改变升降序
			i++;
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;

			cout << "A: ";
			for (int i = p; i < r + 1; i++){
				cout << A[i] << "  ";
			}
			cout << endl;
		}
	}
	temp = A[i + 1];
	A[i + 1] = A[r];
	A[r] = temp;

	cout << "B:  ";
	for (int i = p; i < r + 1; i++){
		cout << A[i] << "  ";
	};
	cout << endl;

	return i + 1;
}
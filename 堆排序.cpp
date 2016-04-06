//made by LRC
#include<iostream>
#define NUM 1000
using namespace std;

int A_Heap_Size;
int A_length = -2;
int largest;
void HEAPSORT(int[]);
void BUILD_MAX_HEAP(int []);
void MAX_HEAPIFY(int[], int);
inline int PARENT(int);
inline int LEFT(int);
inline int RIGHT(int);

int main(){
	int *A;
	A = new int[NUM];
	cout << "------------堆排序-------------" << endl;
	for (int i = 0;; i++){
		cin >> A[i];
		A_length++;
		if (cin.fail()){		//当输入的不是数字时退出输入
			break;
		}
	}

	HEAPSORT(A);
	for (int i = 0; i < A_length+1; i++){
		cout << A[i] << " ";
	}
	cout << endl;

	delete[]A;
	system("pause");
	return 0;
}

void HEAPSORT(int A[]){		//堆排序
	BUILD_MAX_HEAP(A);			//建堆
	int temp;
	for (int i = A_length; i > 0; i--){
		temp = A[0];				//与树根（第一个数据）交换
		A[0] = A[i];
		A[i] = temp;

		A_Heap_Size--;
		MAX_HEAPIFY(A, 0);		//维护堆
	}
}

void BUILD_MAX_HEAP(int A[]){		//建堆
	A_Heap_Size = A_length;
	for (int i = A_length / 2; i >= 0; i--){
		MAX_HEAPIFY(A, i);
	}
}

void MAX_HEAPIFY(int A[],int i){		//维护堆性质
	int temp;
	int l = LEFT(i);
	int r = RIGHT(i);
	if (l <= A_Heap_Size&&A[l] > A[i]){
		largest = l;
	}
	else{
		largest = i;
	}
	if (r <= A_Heap_Size&&A[r] > A[largest])
		largest = r;
	if (largest != i){
		temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;

		MAX_HEAPIFY(A, largest);
	}
}

int PARENT(int i){	//父结点
	return (i-1) / 2;
}
int LEFT(int i){		//左孩子下标
	return i * 2+1;
}
int RIGHT(int i){		//右孩子下标
	return 2 * i+2;
}

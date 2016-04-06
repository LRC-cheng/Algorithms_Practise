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
	cout << "------------������-------------" << endl;
	for (int i = 0;; i++){
		cin >> A[i];
		A_length++;
		if (cin.fail()){		//������Ĳ�������ʱ�˳�����
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

void HEAPSORT(int A[]){		//������
	BUILD_MAX_HEAP(A);			//����
	int temp;
	for (int i = A_length; i > 0; i--){
		temp = A[0];				//����������һ�����ݣ�����
		A[0] = A[i];
		A[i] = temp;

		A_Heap_Size--;
		MAX_HEAPIFY(A, 0);		//ά����
	}
}

void BUILD_MAX_HEAP(int A[]){		//����
	A_Heap_Size = A_length;
	for (int i = A_length / 2; i >= 0; i--){
		MAX_HEAPIFY(A, i);
	}
}

void MAX_HEAPIFY(int A[],int i){		//ά��������
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

int PARENT(int i){	//�����
	return (i-1) / 2;
}
int LEFT(int i){		//�����±�
	return i * 2+1;
}
int RIGHT(int i){		//�Һ����±�
	return 2 * i+2;
}
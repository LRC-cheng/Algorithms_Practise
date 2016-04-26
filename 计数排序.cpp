#include<iostream>
using namespace std;

void COUNTING_SORT(int[], int[], int);		//�������򣬳�ʼֵ������A[],B[],C���±�k
int l;									//����A���±�

int main(){
	int A[8] = { 2, 5, 3, 0, 2, 4, 1, 3 }, B[8] = {0};
	cout << "==================��������==================" << endl;
	cout << "�������������ݣ�" << endl;
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

void COUNTING_SORT(int A[], int B[], int k){		//�������򣬳�ʼֵ������A[],B[],C���±�k
	int *C;
	C = new int[k];
	for (int i = 0; i < k; i++){		//��ʼ������C
		C[i] = 0;
	}
	for (int j = 0; j <= l; j++){		//�������ݸ���
		C[A[j]] = C[A[j]] + 1;
	}
	for (int i = 1; i < k; i++){		//���������
		C[i] = C[i] + C[i - 1];
	}
	for (int j = l; j >= 0; j--){
		C[A[j]] = C[A[j]] - 1;		//C[A[j]]ΪA[j]����������λ��
		B[C[A[j]]] = A[j];		//��A[j]�����B��
	}

	delete[]C;
}
#include<iostream>
#define NUM 1000
using namespace std;

void QUICKSORT(int[], int, int);
int PARTITION(int[], int, int);

int main(){
	cout << "=================��������================" << endl;
	cout << "������������ֵ��" << endl;
	int *A;
	A = new int[NUM];
	int p = 0, r = -2;		//rΪ�����±�

	for (int i = 0;; i++){
		cin >> A[i];
		r++;
		if (cin.fail()){		//������Ĳ�������ʱ�˳�����
			break;
		}
	}
	QUICKSORT(A, p, r);		//��������


	cout <<"-------------------------------------------"<< endl;	//���
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
		QUICKSORT(A, p, q - 1);	//���飬q���м�ֵ����������
		QUICKSORT(A, q + 1, r);	//����
	}
}

int PARTITION(int A[], int p, int r){
	int x,i,temp;
	x = A[r];
	i = p - 1;
	for (int j = p; j <= r - 1; j++){
		if (A[j] <= x){				//A[j]<=A[r]ʱ����A[j]�Ƶ�pǰһ��,�޸ķ��ż��ɸı�������
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
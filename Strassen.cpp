#include<iostream>
#define SIZE 30
#include"Function.h"
using namespace std;

int main(){
	int n;
	cout << "----------------Strassen����˷�����------------------" << endl;
	cout << "�����뷽���ģ��n=2^x����" << endl;
	cin >> n;
	int **A, **B, **C;
	//��̬�����ά����
	A = new int *[SIZE];
	B = new int *[SIZE];
	C = new int *[SIZE];			
	for (int i = 0; i < n; i++){
		A[i] = new int[SIZE];
		B[i] = new int[SIZE];
		C[i] = new int[SIZE];
	}

	cout << "���������A��" << endl;
	for (int i = 0; i < n; i++){				//�������A
		for (int j = 0; j < n; j++){
			cin >> A[i][j];
		}
	}
	cout << "���������B��" << endl;
	for (int i = 0; i < n; i++){				//�������A
		for (int j = 0; j < n; j++){
			cin >> B[i][j];
		}
	}

	system("cls");	//����

	cout << "���μ���ľ���A��" << endl;
	for (int i = 0; i < n; i++){				//��ʾ����A
		for (int j = 0; j < n; j++){
			cout << A[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	cout << "���μ���ľ���B��" << endl;
	for (int i = 0; i < n; i++){				//��ʾ����B
		for (int j = 0; j < n; j++){
			cout << B[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << endl;

	Strassen(A, B, C, n);

	cout << "���Ϊ��" << endl;
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
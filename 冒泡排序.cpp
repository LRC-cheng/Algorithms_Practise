//made by lrc
#include<iostream>
#define NUM 1000
using namespace std;

void BUBBLESORT(int[],int);

int main(){

	cout << "================ð������===============" << endl;

	int *Array;
	Array = new int[NUM];
	int l = -1;				//rΪ���鳤��
	for (int i = 0;; i++){
		cin >> Array[i];
		l++;
		if (cin.fail()){		//������Ĳ�������ʱ�˳�����
			break;
		}
	}

	BUBBLESORT(Array, l);		//ð������

	cout << "���Ϊ��";
	for (int i = 0; i < l; i++){
		cout << Array[i] << "   ";
	}
	cout << endl;

	delete[]Array;
	system("pause");
	return 0;
}

void BUBBLESORT(int A[],int lenght){			//��С��������
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
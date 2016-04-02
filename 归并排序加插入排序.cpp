#include<iostream>
#define NUM 1000
#define TEST1 1		//������������;
#define TEST2 1		//�������������
using namespace std;

void MERGE(int[], int, int, int);		//��������
void MERGE_SORT(int[], int, int);		//��������

int main(){
	int *Array;
	Array = new int[NUM];
	int p = 0, r = -2;

	cout << "--------���η����鲢����Ӳ�������---------" << endl;
	cout << "������������ֵ��" << endl;

	for (int i = 0;; i++){
		cin >> Array[i];
		r++;
		if (cin.fail()){		//������Ĳ�������ʱ�˳�����
			break;
		}
	}

	if (TEST1){
		cout << "���β��������С��" << endl;
		cout << p << " " << r << endl;
	}

	cout << endl;
	cout << "--------------------------------------------" << endl;
	MERGE_SORT(Array, p, r);
	cout << endl;
	for (int i = 0; i <= r; i++)
		cout << Array[i] << "  ";
		cout << endl;

	delete[]Array;

	system("pause");
	return 0;
}



void MERGE_SORT(int A[], int p, int r){		//����������
	int q;
	q = (p + r) / 2;
	if (r - p > 5){
			if (TEST1) {
				cout << "������: " << p << "  " << q << "  " << endl;  //������������
			}
			MERGE_SORT(A, p, q);
			if (TEST1){
				cout << "������: " << q + 1 << "  " << r << "  " << endl;	//������������
			}
			MERGE_SORT(A, q + 1, r);
		}
	 MERGE(A, p, q, r);	//����
	}

void MERGE(int A[], int p, int q, int r){		//����
	if (r - p > 5){
		int n1, n2, i = 0, j = 0, k;		//��p=0,q=4,r=9ʱ
		int *L, *R;
		L = new int[NUM];
		R = new int[NUM];

		n1 = q - p + 1;			//n1=5
		n2 = r - q;				//n2=5

		for (i = 0; i < n1; i++){
			L[i] = A[p + i];		//A[0]��ʼ��A[4]�����������L[0]��L[4]
		}
		for (j = 0; j < n2; j++){
			R[j] = A[q + j + 1];	//A[5]��ʼ��A[9]�����ұ�����R[0]��L[4]
		}

		L[n1] = 99999999;			//�����ڱ�
		R[n2] = 99999999;			//�����ڱ�

		i = j = 0;
		for (k = p; k <= r; k++){	//k=p=0,r=9,ʹʮ���������е�A[]��
			if (L[i] <= R[j]){	//��L[i]��R[j]Сʱ����L[i]�ŵ�A[K]�У���֮��Ȼ
				A[k] = L[i];
				i++;
			}
			else{
				A[k] = R[j];
				j++;
			}
		}

		//�������������
		if (TEST2){
			cout << endl;
			cout << "���Բ������������" << endl;
			for (i = 0; i < k; i++){
				cout << A[i] << "   ";
			}
			cout << endl;
		}
		delete[]L;	//�ͷſռ�
		delete[]R;
	}
	else{						//��������
		int temp, i;
//		cout <<"test:"<< p << "  " << r;
		for (int j=p+1; j <= r; j++){
			temp = A[j];
			i = j - 1;
			while (i >= p && A[i] > temp){
				A[i + 1] = A[i];
				i--;
				A[i + 1] = temp;
			}
		}
		if (TEST2){
			cout << endl;
			cout << "���Բ������������" << endl;
			for (i = 0; i <= r; i++){
				cout << A[i] << "   ";
			}
			cout << endl;
		}
	}
}
//�������� 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
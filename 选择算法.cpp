#include<iostream>
#define NUM 50
using namespace std;

int PARTITION(int[], int, int);		//����
int SELECT(int[], int, int, int);

int main(){
	cout << "===============ѡ���㷨=============" << endl;
	cout << "��������ֵ��" << endl;
	int *A;
	int z,x;
	A = new int[NUM];
	int p = 0, r = -2;		//rΪ�����±�

	for (int i = 0;; i++){
		cin >> A[i];
		r++;
		if (cin.fail()){		//������Ĳ�������ʱ�˳�����,���������ݻ��ڻ�������
			break;
		}
	}
	cin.clear();		//���ô�������
	cin.sync();		//��ջ�����  
	cout << "Ҫ�ҵ�Ԫ����";
	cin >> z;
	x = SELECT(A, p, r, z);
	cout << "���Ϊ��" << x << endl;

	delete[]A;
	system("pause");
	return 0;
}

int PARTITION(int A[], int p, int r){
	int x, i, temp;
	x = A[r];
	i = p - 1;
	for (int j = p; j <= r - 1; j++){
		if (A[j] <= x){				//A[j]<=A[r]ʱ����A[j]�Ƶ�pǰһ��,�޸ķ��ż��ɸı�������
			i++;
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}
	temp = A[i + 1];
	A[i + 1] = A[r];
	A[r] = temp;

	return i + 1;
}

int SELECT(int A[], int p, int r, int i){	//ѡ������
	int q, k;
	if (p == r)
		return A[p];
	q = PARTITION(A, p, r);
	k = q - p + 1;
	if (i == k)
		return A[q];
	else if (i < k)
		return SELECT(A, p, q - 1, i);
	else return SELECT(A, q + 1, r, i - k);
}
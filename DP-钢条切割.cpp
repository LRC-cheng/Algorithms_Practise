//Created by LRC-cheng
#include<iostream>
#define TEST 4

using namespace std;

const int p[11] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
template < typename T >
T MAX(const T a, const T b){
	return a >= b ? a : b;
}

void test1();						//���Է���
int CUT_ROD(const int[], int);		//�������µݹ�ʵ�֣��Ƕ�̬�滮������

int Memoized_Cut_Rod(const int[], int);					//�������Զ����·�����̬�滮��
int Memoized_Cut_Rod_Aux(const int[], int, int[]);		//�������Զ����·�����̬�滮����������
int Bottom_up_Cut_Rod(const int[], int);					//�Ե����Ϸ�������̬�滮��
int Extended_Bottom_up_Cut_Rod(const int[], int, int[]);	//�ع��⣬�������ŷ���

int main(){
	test1();

	system("pause");
	return 0;
}


//�������µݹ�ʵ�֣��Ƕ�̬�滮������,p:�۸����飻n:��������
int CUT_ROD(const int p[], int n){
	if (n == 0)
		return 0;
	int q = -199999;			//���������
	for (int i = 1; i <= n; ++i)
		q = MAX(q, p[i%12] + CUT_ROD(p, n - i));
	return q;
}
//�������Զ����·�����̬�滮��
int Memoized_Cut_Rod(const int p[],int n){
	int *r = new int[n + 5];
	for (int i = 0; i <= n + 5; i++){
		r[i] = -1999999;
	}
	return Memoized_Cut_Rod_Aux(p,n,r);
}
//�������Զ����·�����̬�滮����������
int Memoized_Cut_Rod_Aux(const int p[], int n, int r[]){
	int q;
	if (r[n] >= 0)
		return r[n];
	if (n == 0)
		q = 0;
	else{
		q = -199999;
		for (int i = 1; i <= n; i++)
			q = MAX(q, p[i%12] + Memoized_Cut_Rod_Aux(p, n - i, r));
	}
	r[n] = q;
	return q;
}
//�Ե����Ϸ�������̬�滮��
int Bottom_up_Cut_Rod(const int p[], int n){
	int q;
	int *r = new int[n + 1];
	r[0] = 0;
	for (int j = 1; j <= n; ++j){
		q = -1099999;
		for (int i = 1; i <= j; ++i){
			q = MAX(q, p[i%12] + r[j - i]);
		}
		r[j] = q;
	}
	return r[n];
}


//���Է���
void test1(){
	int a, n;
	cout << "�����ܳ���";
	cin >> n;
	if (TEST == 1)
		a = CUT_ROD(p, n);
	else if (TEST == 2)
		a = Memoized_Cut_Rod(p, n);
	else if (TEST == 3)
		a = Bottom_up_Cut_Rod(p, n);
	else if (TEST == 4){
		int *s = new int[n + 1];
		a = Extended_Bottom_up_Cut_Rod(p, n, s);
		cout << "�����и��(�ֶγ���)��";
		while (n > 0){
			cout << s[n] << " ";
			n = n - s[n];
		}
	}
	cout << endl;
	cout << "��������Ϊ��";
	cout << a << endl;
}
//�ع��⣬�������ŷ���
int Extended_Bottom_up_Cut_Rod(const int p[], int n, int s[]){
	int q;
	int *r = new int[n + 1];
	r[0] = 0;
	for (int j = 1; j <= n; ++j){
		q = -10999;
		for (int i = 1; i <= j; i++){
			if (q < p[i % 12] + r[j - i]){
				q = p[i % 12] + r[j - i];
				s[j] = i;
			}
		}
		r[j] = q;
	}
	return r[n];
}
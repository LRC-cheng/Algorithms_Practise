//Created by LRC-cheng
#include<iostream>
#define TEST 4

using namespace std;

const int p[11] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
template < typename T >
T MAX(const T a, const T b){
	return a >= b ? a : b;
}

void test1();						//测试方法
int CUT_ROD(const int[], int);		//至顶向下递归实现（非动态规划方法）

int Memoized_Cut_Rod(const int[], int);					//带备忘自顶向下法（动态规划）
int Memoized_Cut_Rod_Aux(const int[], int, int[]);		//带备忘自顶向下法（动态规划）辅助过程
int Bottom_up_Cut_Rod(const int[], int);					//自底向上法方（动态规划）
int Extended_Bottom_up_Cut_Rod(const int[], int, int[]);	//重构解，返回最优方案

int main(){
	test1();

	system("pause");
	return 0;
}


//至顶向下递归实现（非动态规划方法）,p:价格数组；n:钢条长度
int CUT_ROD(const int p[], int n){
	if (n == 0)
		return 0;
	int q = -199999;			//设置无穷大
	for (int i = 1; i <= n; ++i)
		q = MAX(q, p[i%12] + CUT_ROD(p, n - i));
	return q;
}
//带备忘自顶向下法（动态规划）
int Memoized_Cut_Rod(const int p[],int n){
	int *r = new int[n + 5];
	for (int i = 0; i <= n + 5; i++){
		r[i] = -1999999;
	}
	return Memoized_Cut_Rod_Aux(p,n,r);
}
//带备忘自顶向下法（动态规划）辅助过程
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
//自底向上法方（动态规划）
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


//测试方法
void test1(){
	int a, n;
	cout << "钢条总长：";
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
		cout << "最优切割方案(分段长度)：";
		while (n > 0){
			cout << s[n] << " ";
			n = n - s[n];
		}
	}
	cout << endl;
	cout << "最优收益为：";
	cout << a << endl;
}
//重构解，返回最优方案
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
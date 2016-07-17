#include<iostream>
#define MAX 100
using namespace std;

void OPTIMAL_BST(double *, double *, int, double **, int**);

int main(){
	double *p = new double[MAX];
	double *q = new double[MAX];
	double **e;
	int **root;
	int n;

	p[0] = 0;
	cout << "输入规模n：";
	cin >> n;
	cout << "输入关键字搜索频率pi：";
	for (int i = 1; i <= n; i++){
		cin >> p[i];
	}
	cout << endl;
	cout << "输入伪关键字搜索频率qi：";
	for (int i = 0; i <= n; i++){
		cin >> q[i];
	}

	e = new double*[n + 5];
	root = new int*[n + 5];
	for (int i = 0; i < n + 5; i++){
		e[i] = new double[n];
		root[i] = new int[n];
	}

	OPTIMAL_BST(p, q, n, e, root);

	for (int i = 1; i < 6; i++){
		for (int j = 1; j < 6; j++){
			if (j < i)
				cout << '\t';
			else cout << root[i][j] << '\t';
		}
		cout << endl;
	}
	for (int i = 1; i <= 6; i++){
		for (int j = 0; j < 6; j++){
			if (j < i - 1)
				cout << '\t';
			else cout << e[i][j] << '\t';
		}
		cout << endl;
	}

	system("pause");
	return 0;
}
//p、q关键字概率，n：输入规模，e搜索代价，root:包含关键字的子树根
void OPTIMAL_BST(double *p, double *q, int n, double **e, int**root){
	int j = 0;
	double t = 0;
	double **w = new double*[n + 5];
	for (int i = 0; i < n + 5; i++){
		w[i] = new double[n];
	}
	for (int i = 1; i <= n + 1; i++){
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}
	for (int l = 1; l <= n; l++){
		for (int i = 1; i <= n - l + 1; i++){
			j = i + l - 1;	
			e[i][j] = 0x3f3f3f3f;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for (int r = i; r <= j; r++){
				t = e[i][r - 1] + e[r + 1][j] + w[i][j];
				if (t < e[i][j]){
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
}

/*
5
0.15 0.10 0.05 0.10 0.20
0.05 0.10 0.05 0.05 0.05 0.10
*/
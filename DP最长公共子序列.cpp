#include<iostream>
#define MAX 100
using namespace std;

typedef struct table{
	int length;
	int direction;
}table;
void LCS_LENGTH(char[], int, char[], int, table**);		//计算LCS长度
void PRINT_LCS(table**, char[], int, int);			//构造LCS

int main(){
	char *x = new char[MAX];
	char *y = new char[MAX];
	x[0] = '\n';
	y[0] = '\n';
	int m, n;
	m = n = 0;
	table **b;
	b = new table*[MAX];
	for (int i = 0; i < MAX; i++)
		b[i] = new table[MAX];

	cout << "输入两个字符串（均以‘#’结束）：";
	for (int i=1;;i++){
		cin >> x[i];
		if (x[i] == '#'){
			break;
		}
		m++;
	}
	for (int i = 1;; i++){
		cin >> y[i];
		if (y[i] == '#'){
			break;
		}
		n++;
	}
	LCS_LENGTH(x, m, y, n, b);
	PRINT_LCS(b, x, m, n);

	cout << endl;
	system("pause");
	return 0;
}

//计算LCS长度
void LCS_LENGTH(char x[], int m, char y[], int n, table **b){
	for (int i = 0; i <= m; i++)			//初始化表格
		for (int j = 0; j <= n; j++)
			b[i][j].length = 0;

	for (int i = 1; i <= m; i++){
		for (int j = 1; j <= n; j++){
			if (x[i] == y[j]){
				b[i][j].length = b[i - 1][j - 1].length + 1;
				b[i][j].direction = 1;
			}
			else if (b[i - 1][j].length >= b[i][j - 1].length){
				b[i][j].length = b[i - 1][j].length;
				b[i][j].direction = 2;
			}
			else{
				b[i][j].length = b[i][j - 1].length;
				b[i][j].direction = 3;
			}
		}
	}
}
//构造LCS
void PRINT_LCS(table **b, char x[], int m, int n){
	if (m == 0 || n == 0)
		return;
	if (b[m][n].direction == 1){
		PRINT_LCS(b, x, m - 1, n - 1);
		cout << x[m];
	}
	else if (b[m][n].direction == 2)
		PRINT_LCS(b, x, m - 1, n);
	else PRINT_LCS(b, x, m, n - 1);
}


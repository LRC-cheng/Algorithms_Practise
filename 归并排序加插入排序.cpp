/*created by LRC-cheng*/
#include<iostream>
#define NUM 1000
#define TEST1 1		//测试输入区间;
#define TEST2 1		//测试排序情况：
using namespace std;

void MERGE(int[], int, int, int);		//并归排序
void MERGE_SORT(int[], int, int);		//分离数据

int main(){
	int *Array;
	Array = new int[NUM];
	int p = 0, r = -2;

	cout << "--------分治法：归并排序加插入排序---------" << endl;
	cout << "请输入排序数值：" << endl;

	for (int i = 0;; i++){
		cin >> Array[i];
		r++;
		if (cin.fail()){		//当输入的不是数字时退出输入
			break;
		}
	}

	if (TEST1){
		cout << "本次测试数组大小：" << endl;
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



void MERGE_SORT(int A[], int p, int r){		//分离数据树
	int q;
	q = (p + r) / 2;
	if (r - p > 5){
			if (TEST1) {
				cout << "左区间: " << p << "  " << q << "  " << endl;  //测试输入区间
			}
			MERGE_SORT(A, p, q);
			if (TEST1){
				cout << "右区间: " << q + 1 << "  " << r << "  " << endl;	//测试输入区间
			}
			MERGE_SORT(A, q + 1, r);
		}
	 MERGE(A, p, q, r);	//排序
	}

void MERGE(int A[], int p, int q, int r){		//排序
	if (r - p > 5){
		int n1, n2, i = 0, j = 0, k;		//当p=0,q=4,r=9时
		int *L, *R;
		L = new int[NUM];
		R = new int[NUM];

		n1 = q - p + 1;			//n1=5
		n2 = r - q;				//n2=5

		for (i = 0; i < n1; i++){
			L[i] = A[p + i];		//A[0]开始到A[4]赋给左边数组L[0]到L[4]
		}
		for (j = 0; j < n2; j++){
			R[j] = A[q + j + 1];	//A[5]开始到A[9]赋给右边数组R[0]到L[4]
		}

		L[n1] = 99999999;			//设置哨兵
		R[n2] = 99999999;			//设置哨兵

		i = j = 0;
		for (k = p; k <= r; k++){	//k=p=0,r=9,使十个数都排列到A[]中
			if (L[i] <= R[j]){	//当L[i]比R[j]小时，把L[i]放到A[K]中，反之亦然
				A[k] = L[i];
				i++;
			}
			else{
				A[k] = R[j];
				j++;
			}
		}

		//测试排序情况：
		if (TEST2){
			cout << endl;
			cout << "测试并归排序情况：" << endl;
			for (i = 0; i < k; i++){
				cout << A[i] << "   ";
			}
			cout << endl;
		}
		delete[]L;	//释放空间
		delete[]R;
	}
	else{						//插入排序
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
			cout << "测试插入排序情况：" << endl;
			for (i = 0; i <= r; i++){
				cout << A[i] << "   ";
			}
			cout << endl;
		}
	}
}
//测试数据 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1

/*Created by LRC-cheng*/
#include<iostream>
#define SIZE 10
#define NUM 105
using namespace std;

typedef struct Recond{
	int data;
	struct Recond *pre;
	struct Recond *next;
}Recond, *LRecond;

typedef struct HasH{
	int key;
	struct Recond *next;
}Hash;

int Push(Hash[], int);
void Sort(Hash[], int[]);
void InitHash(Hash [], int);
inline int h(int);


int main(){
	cout << "===============基于散列表的桶排序=================" << endl;
	cout << "输入排序数据(0~99)：" << endl;
	int *A;
	LRecond p = new Recond;
	Hash T[10];
	InitHash(T, 10);
	A = new int[NUM];
	int r = -2;		//r为数组下标

	for (int i = 0;; i++){
		cin >> A[i];
		r++;
		if (cin.fail()){		//当输入的不是数字时退出输入
			break;
		}
	}
	cin.clear();
	for (int i = 0; i <= r; i++){
		Push(T, A[i]);
	}

	Sort(T, A);
	cout << "结果为：";
	for (int i = 0; i <= r; i++){
		cout << A[i] << "  ";
	}
	cout << endl;

	delete[] A;
	system("pause");
	return 0;
}

//散列函数 e：原始数据
inline int h(int e){
	return e / 10;
}
//初始化 Hash H[]:哈希表
void InitHash(Hash H[],int n){
	for (int i = 0; i < n; i++){
		LRecond p = new Recond;
		p->next = NULL;
		H[i].key = 0;
		H[i].next = p;
	}
}
//入表 Hash H[]:哈希表 e:入表元素
int Push(Hash H[], int e){
	LRecond p = new Recond;
	LRecond s = new Recond;
	int y;	
	y = h(e);
	p->data = e;
	p->next = NULL;
	p->pre = NULL;

	if (!H[y].key){
		H[y].next = p;
		H[y].key = 1;
		delete s;
		return 0;
	}
	s = H[y].next;
	while (s){
		if (p->data > s->data){
			if (!s->pre){
				H[y].next = p;
				p->next = s;
				s->pre = p;
				return 0;
			}
			else{
				p->pre = s->pre;
				s->pre->next = p;
				p->next = s;
				s->pre = p;
				return 0;
			}
		}
		else if(!s->next){
			s->next = p;
			p->pre = s;
			p->next = NULL;
			return 0;
		}
		else{
			s = s->next;
		}
	}
	
}
//排序 Hash H[]:哈希表 把排序结果放进A[n];
void Sort(Hash H[], int A[]){
	LRecond p = new Recond;
	int j = 0;
	for (int i = 9; i >= 0; i--){
		if (H[i].key){
			p = H[i].next;
			while (p){
				A[j] = p->data;
				j++;
				p = p->next;
			}
		}
	}
}

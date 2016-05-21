//made by lrc
#include<iostream>
#define NUM 30
#define TEST 1
using namespace std;
//待排序的数据类型
typedef int KeyType;
typedef char OtherData;
typedef struct{
	KeyType key;
	OtherData data;
}RedType;
typedef struct{
	RedType r[NUM + 1];
	int lenght;
}SqList;

void BubbleSort(SqList &, int);

int main(){
	cout << "================冒泡排序===============" << endl;
	SqList S;
	S.lenght = 0;
	cout << "请输入数据（任意字母键结束）：";
	for (int i = 0;; i++){
		cin >> S.r[i].key;
		if (cin.fail()){		//当输入的不是数字时退出输入
			cin.clear();
			cin.sync();
			break;
		}
		++S.lenght;
	}

	BubbleSort(S, S.lenght);		//冒泡排序

	cout << "结果为：";
	for (int j = 0; j < S.lenght; j++){
		cout << S.r[j].key << "   ";
	}
	cout << endl;

	system("pause");
	return 0;
}

void BubbleSort(SqList &S, int lenght){			//由小到大排序
	RedType temp;
	short flag = 1;							//标志位记录本趟排序是否发生了交换
	for (int i = 1; i < lenght; i++){
		if (flag = 1){
			flag = 0;
			for (int j = 0; j < lenght; j++){
				if (S.r[i].key < S.r[j].key){	//交换前后数据
					temp = S.r[i];
					S.r[i] = S.r[j];
					S.r[j] = temp;
					flag = 1;				//标志位置为1，表示本趟排序发生了交换
				}
			}
			if (TEST){
				cout << "第" << i << "趟排序：";
				for (int k = 0; k < S.lenght; k++){
					cout << S.r[k].key << "  ";
				}
				cout << endl;
			}

		}
		else
			break;
	}
}
//49 38 65 97 76 13 27 49 

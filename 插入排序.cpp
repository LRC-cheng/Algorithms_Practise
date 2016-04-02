#include<iostream>
using namespace std;
int main(){
	int A[6] = { 2, 6, 1, 3, 5, 4 };
	int key,i;
	for (int j = 1; j < 6; j++){
		key = A[j];
//Insert A[j] into the sorted sequence A[1...j-1].
		i = j - 1;
		while (i>=0 && A[i] < key){
			A[i + 1] = A[i];
			i--;
			A[i + 1] = key;
		}
	}
	for (i = 0; i < 6; i++){
		cout << A[i] << "\t";
	}
	cout << endl;
	system("pause");
	return 0;
}
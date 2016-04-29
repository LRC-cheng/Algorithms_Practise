#include"Function.h"
using namespace std;

int Strassen(int **A, int **B, int **Result, int Size){
	if (Size == 1){
		Result[0][0] = A[0][0] * B[0][0];
		return 0;
	}
	int NewSize = Size / 2;
	/*分块矩阵*/
	int **A11, **A12, **A21, **A22;
	int **B11, **B12, **B21, **B22;
	int **C11, **C12, **C21, **C22;

	int **P1, **P2, **P3, **P4, **P5, **P6, **P7;
	/*存放数组A、B（i、j）的临时变量*/
	int **AResult, **BResult;

	A11 = new int*[NewSize];
	A12 = new int*[NewSize];
	A21 = new int*[NewSize];
	A22 = new int*[NewSize];

	B11 = new int*[NewSize];
	B12 = new int*[NewSize];
	B21 = new int*[NewSize];
	B22 = new int*[NewSize];

	C11 = new int*[NewSize];
	C12 = new int*[NewSize];
	C21 = new int*[NewSize];
	C22 = new int*[NewSize];

	P1 = new int*[NewSize];
	P2 = new int*[NewSize];
	P3 = new int*[NewSize];
	P4 = new int*[NewSize];
	P5 = new int*[NewSize];
	P6 = new int*[NewSize];
	P7 = new int*[NewSize];

	AResult = new int*[NewSize];
	BResult = new int*[NewSize];

	for (int i = 0; i < NewSize; i++)
	{
		A11[i] = new int[NewSize];
		A12[i] = new int[NewSize];
		A21[i] = new int[NewSize];
		A22[i] = new int[NewSize];

		B11[i] = new int[NewSize];
		B12[i] = new int[NewSize];
		B21[i] = new int[NewSize];
		B22[i] = new int[NewSize];

		C11[i] = new int[NewSize];
		C12[i] = new int[NewSize];
		C21[i] = new int[NewSize];
		C22[i] = new int[NewSize];

		P1[i] = new int[NewSize];
		P2[i] = new int[NewSize];
		P3[i] = new int[NewSize];
		P4[i] = new int[NewSize];
		P5[i] = new int[NewSize];
		P6[i] = new int[NewSize];
		P7[i] = new int[NewSize];

		AResult[i] = new int[NewSize];
		BResult[i] = new int[NewSize];


	}

	//对分块矩阵赋值
	for (int i = 0; i < NewSize; i++)
	{
		for (int j = 0; j < NewSize; j++)
		{
			A11[i][j] = A[i][j];
			A12[i][j] = A[i][j + NewSize];
			A21[i][j] = A[i + NewSize][j];
			A22[i][j] = A[i + NewSize][j + NewSize];

			B11[i][j] = B[i][j];
			B12[i][j] = B[i][j + NewSize];
			B21[i][j] = B[i + NewSize][j];
			B22[i][j] = B[i + NewSize][j + NewSize];

		}
	}

	//计算P1 = A11*(B12-B22)
	Sub(B12, B22, BResult, NewSize);
	Strassen(A11, BResult, P1, NewSize);

	//计算P2 = (A11+A12)*B22
	Add(A11, A12, AResult, NewSize);
	Strassen(AResult, B22, P2, NewSize);

	//计算P3 = (A21+A22)*B11
	Add(A21, A22, AResult, NewSize);
	Strassen(AResult, B11, P3, NewSize);

	//计算P4 = A22*(B21-B11)
	Sub(B21, B11, BResult, NewSize);
	Strassen(A22, BResult, P4, NewSize);

	//计算P5 = (A11+A22)*(B11+B22)
	Add(A11, A22, AResult, NewSize);
	Add(B11, B22, BResult, NewSize);
	Strassen(AResult, BResult, P5, NewSize);

	//计算P6 = (A11-A21)*(B11+B12)
	Sub(A11, A21, AResult, NewSize);
	Add(B11, B12, BResult, NewSize);
	Strassen(AResult, BResult, P6, NewSize);

	//计算P7 = (A11-A21)*(B11+B12)
	Sub(A11, A21, AResult, NewSize);
	Add(B11, B12, BResult, NewSize);
	Strassen(AResult, BResult, P7, NewSize);

	//计算C11，C12，C21，C22
	//C11 = P5 + P4 - P2 + P6;
	Add(P5, P4, C11, NewSize);
	Sub(C11, P2, C11, NewSize);
	Add(C11, P6, C11, NewSize);

	//C12=P1+P2
	Add(P1, P2, C12, NewSize);

	//C21=P3+P4
	Add(P3, P4, C21, NewSize);

	//C22=P5+P1-P3-P7
	Add(P5, P1, C22, NewSize);
	Sub(C22, P3, C22, NewSize);
	Sub(C22, P7, C22, NewSize);

	//合并C11，C12，C21，C22
	for (int i = 0; i < NewSize; i++)
	{
		for (int j = 0; j < NewSize; j++)
		{
			Result[i][j] = C11[i][j];
			Result[i][j + NewSize] = C12[i][j];
			Result[i + NewSize][j] = C21[i][j];
			Result[i + NewSize][j + NewSize] = C22[i][j];
		}
	}

	//删除数组，回收资源
	for (int i = 0; i < NewSize; i++){
		delete[] A11[i]; delete[] A12[i]; delete[] A21[i]; delete[] A22[i];
		delete[] B11[i]; delete[] B12[i]; delete[] B21[i]; delete[] B22[i];
		delete[] C11[i]; delete[] C12[i]; delete[] C21[i]; delete[] C22[i];
		delete[] P1[i]; delete[] P2[i]; delete[] P3[i]; delete[] P4[i]; delete[] P5[i]; delete[] P6[i]; delete[] P7[i];
		delete[] AResult[i]; delete[] BResult[i];
	}
	delete[] A11; delete[] A12; delete[] A21; delete[] A22;
	delete[] B11; delete[] B12; delete[] B21; delete[] B22;
	delete[] C11; delete[] C12; delete[] C21; delete[] C22;
	delete[] P1; delete[] P2; delete[] P3; delete[] P4; delete[] P5; delete[] P6; delete[] P7;
	delete[] AResult; delete[] BResult;
	return 0;
}



//矩阵相加
void Add(int **A, int **B, int **Q, int Size){
	for (int i = 0; i < Size; i++){
		for (int j = 0; j < Size; j++){
			Q[i][j] = A[i][j] + B[i][j];
		}
	}
}

//矩阵相减
void Sub(int**A, int**B, int **Q, int Size){
	for (int i = 0; i < Size; i++){
		for (int j = 0; j < Size; j++){
			Q[i][j] = A[i][j] - B[i][j];
		}
	}
}
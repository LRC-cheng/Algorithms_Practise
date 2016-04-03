//made by LRC
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

	cout << "--------分治法：归并排序---------" << endl;
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
	cout << "-------------------------------------" << endl;
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
	if (r - p > 0){
		q = (p + r) / 2;
		if (TEST1) {
			cout << "左区间: " << p << "  " << q << "  " << endl;  //测试输入区间
		}
		MERGE_SORT(A, p, q);
		if (TEST1){
			cout << "右区间: " << q + 1 << "  " << r << "  " << endl;	//测试输入区间
		}
		MERGE_SORT(A, q + 1, r);
		MERGE(A, p, q, r);	//排序
	}
}

void MERGE(int A[], int p, int q, int r){		//排序
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

//测试数据 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
//149 238 79 240 165 183 59 235 213 64 200 211 239 42 297 66 182 191 56 27 30 212 159 47 43 147 127 241 188 134 186 296 148 276 38 92 82 80 221 140 36 299 31 73 93 116 122 96 204 21 173 278 13 185 230 178 81 271 139 37 244 249 49 105 151 51 222 65 68 130 284 251 10 118 102 98 243 17 9 153 169 293 176 39 3 0 190 20 223 91 154 16 76 291 100 8 208 144 285 172 94 219 23 289 2 111 158 120 198 295 108 75 32 48 167 170 104 174 87 135 115 72 196 201 261 119 270 95 58 129 77 189 254 233 90 62 226 110 29 245 203 161 35 55 125 126 252 67 57 6 209 163 264 107 256 298 277 54 202 272 44 247 132 263 266 113 41 117 280 33 236 106 70 229 177 46 260 253 175 294 4 52 18 146 11 124 257 156 5 121 101 14 279 71 207 287 197 143 26 1 248 164 162 286 74 138 216 60 89 259 265 22 187 97 168 199 231 131 217 157 250 290 99 128 215 258 193 179 227 281 83 78 88 86 53 28 69 283 232 220 150 12 137 255 123 275 262 192 40 19 50 184 152 133 103 141 242 15 269 300 7 171 218 142 195 206 210 112 61 25 180 145 166 288 109 267 63 234 24 85 292 282 45 155 84 136 160 205 237 224 268 228 181 34 225 214 246 114 194 274-

#include<iostream>
#include<string>
using namespace std;

//哈夫曼树存储表示
typedef struct{
	int weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;
//哈夫曼编码表存储表示
typedef char **HuffmanCode;

void CreateHuffmanTree(HuffmanTree &, int);		//构造哈夫曼树
void Select(HuffmanTree &, int, int &, int &);	//寻找双亲域为0且权值最小的结点
void CreateHuffmanCode(HuffmanTree, HuffmanCode &, int);//从叶子到根逆向求每个字符的哈夫曼编码，存储在编码表HC中

int main(){
	//	cout << "================哈夫曼编码================" << endl;
	//	cout << "梁锐成 1463100043" << endl;
	HuffmanTree HT;
	HuffmanCode HC;
	int n;
	cout << "请输入叶子结点的个数：";
	cin >> n;
	CreateHuffmanTree(HT, n);
	CreateHuffmanCode(HT, HC, n);
	for (int i = 1; i <= n; i++){		//读取编码，注意HC[i]为字符串
		cout << i << "的编码为：" << HC[i] << " " << endl;
	}
	system("pause");
	return 0;
}

//构造哈夫曼树 HT:哈夫曼树，n:数据量
void CreateHuffmanTree(HuffmanTree &HT, int n){
	if (n <= 1)
		return;
	int m = 2 * n - 1;
	HT = new HTNode[m + 1];
	for (int i = 1; i <= m; ++i){		//初始化双亲，孩子下标，置为0
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	cout << "请输入叶子结点的权值：";
	for (int i = 1; i <= n; ++i){
		cin >> HT[i].weight;
	}
	//初始化工作完毕，开始创建哈夫曼树
	int s1, s2;			//记录最小和次小的权值的序号
	for (int i = n + 1; i <= m; ++i){
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;		//把s1,s2作为i的左右孩，并更新权值
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}
//寻找双亲域为0且权值最小的结点
void Select(HuffmanTree &HT, int n, int &s1, int &s2){
	int w = 999999;
	for (int i = 1; i <= n; ++i){
		if (HT[i].parent == 0 && HT[i].weight < w){
			w = HT[i].weight;			//每次比较保存较小的权值，并记录对应序号
			s1 = i;
		}
	}
	w = 999999;						//重置权值
	HT[s1].parent = 1;				//把已记录的最小权值父结点赋值，避免再次计算取值
	for (int i = 1; i <= n; ++i){
		if (HT[i].parent == 0 && HT[i].weight < w){
			w = HT[i].weight;
			s2 = i;
		}
	}
}
//从叶子到根逆向求每个字符的哈夫曼编码，存储在编码表HC中
void CreateHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n){
	char *cd; int start, c, f;
	HC = new char*[n + 1];				//分配n个字符编码空间（0号单元不用），HC为字符串
	cd = new char[n];					//临时存放编码动态数组
	cd[n - 1] = '\0';					//结束符
	for (int i = 1; i <= n; ++i){		//对逐个字符求解哈夫曼编码
		start = n - 1;				//start从结束符‘\0’开始往前记录（逆序记录）
		c = i;
		f = HT[i].parent;				//记录c的双亲结点
		while (f != 0){
			--start;					//先回朔一次start的位置
			if (HT[f].lchild == c)		//若c为左孩，生成字符‘0’，否则生成字符‘1’
				cd[start] = '0';
			else
				cd[start] = '1';
			c = f; f = HT[f].parent;	//向父结点回朔
		}
		HC[i] = new char[n - start];	//为第i个编码分配空间
		strcpy_s(HC[i], n - start, &cd[start]);//把临时空间cd的数据复制到HC当前行中，n-start为HC[i]的长度
	}
	delete cd;						//释放临时空间
}
//测试数据：5 29 7 8 14 23 3 11

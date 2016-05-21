#include<iostream>
#include<string>
using namespace std;

//���������洢��ʾ
typedef struct{
	int weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;
//�����������洢��ʾ
typedef char **HuffmanCode;

void CreateHuffmanTree(HuffmanTree &, int);		//�����������
void Select(HuffmanTree &, int, int &, int &);	//Ѱ��˫����Ϊ0��Ȩֵ��С�Ľ��
void CreateHuffmanCode(HuffmanTree, HuffmanCode &, int);//��Ҷ�ӵ���������ÿ���ַ��Ĺ��������룬�洢�ڱ����HC��

int main(){
	//	cout << "================����������================" << endl;
	//	cout << "����� 1463100043" << endl;
	HuffmanTree HT;
	HuffmanCode HC;
	int n;
	cout << "������Ҷ�ӽ��ĸ�����";
	cin >> n;
	CreateHuffmanTree(HT, n);
	CreateHuffmanCode(HT, HC, n);
	for (int i = 1; i <= n; i++){		//��ȡ���룬ע��HC[i]Ϊ�ַ���
		cout << i << "�ı���Ϊ��" << HC[i] << " " << endl;
	}
	system("pause");
	return 0;
}

//����������� HT:����������n:������
void CreateHuffmanTree(HuffmanTree &HT, int n){
	if (n <= 1)
		return;
	int m = 2 * n - 1;
	HT = new HTNode[m + 1];
	for (int i = 1; i <= m; ++i){		//��ʼ��˫�ף������±꣬��Ϊ0
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	cout << "������Ҷ�ӽ���Ȩֵ��";
	for (int i = 1; i <= n; ++i){
		cin >> HT[i].weight;
	}
	//��ʼ��������ϣ���ʼ������������
	int s1, s2;			//��¼��С�ʹ�С��Ȩֵ�����
	for (int i = n + 1; i <= m; ++i){
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;		//��s1,s2��Ϊi�����Һ���������Ȩֵ
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}
//Ѱ��˫����Ϊ0��Ȩֵ��С�Ľ��
void Select(HuffmanTree &HT, int n, int &s1, int &s2){
	int w = 999999;
	for (int i = 1; i <= n; ++i){
		if (HT[i].parent == 0 && HT[i].weight < w){
			w = HT[i].weight;			//ÿ�αȽϱ����С��Ȩֵ������¼��Ӧ���
			s1 = i;
		}
	}
	w = 999999;						//����Ȩֵ
	HT[s1].parent = 1;				//���Ѽ�¼����СȨֵ����㸳ֵ�������ٴμ���ȡֵ
	for (int i = 1; i <= n; ++i){
		if (HT[i].parent == 0 && HT[i].weight < w){
			w = HT[i].weight;
			s2 = i;
		}
	}
}
//��Ҷ�ӵ���������ÿ���ַ��Ĺ��������룬�洢�ڱ����HC��
void CreateHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n){
	char *cd; int start, c, f;
	HC = new char*[n + 1];				//����n���ַ�����ռ䣨0�ŵ�Ԫ���ã���HCΪ�ַ���
	cd = new char[n];					//��ʱ��ű��붯̬����
	cd[n - 1] = '\0';					//������
	for (int i = 1; i <= n; ++i){		//������ַ�������������
		start = n - 1;				//start�ӽ�������\0����ʼ��ǰ��¼�������¼��
		c = i;
		f = HT[i].parent;				//��¼c��˫�׽��
		while (f != 0){
			--start;					//�Ȼ�˷һ��start��λ��
			if (HT[f].lchild == c)		//��cΪ�󺢣������ַ���0�������������ַ���1��
				cd[start] = '0';
			else
				cd[start] = '1';
			c = f; f = HT[f].parent;	//�򸸽���˷
		}
		HC[i] = new char[n - start];	//Ϊ��i���������ռ�
		strcpy_s(HC[i], n - start, &cd[start]);//����ʱ�ռ�cd�����ݸ��Ƶ�HC��ǰ���У�n-startΪHC[i]�ĳ���
	}
	delete cd;						//�ͷ���ʱ�ռ�
}
//�������ݣ�5 29 7 8 14 23 3 11

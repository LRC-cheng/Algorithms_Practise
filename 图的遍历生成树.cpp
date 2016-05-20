#include<iostream>
#include<string>
using namespace std;

//ͼ���ڽӾ���洢��ʾ
#define MVNum 50 
typedef char VerTexType;		//��������
typedef int ArcType;			//��
typedef struct{
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];//�ڽӾ���
	int vexnum, arcnum;
}AMGraph;

int CreateUDN(AMGraph &);				//�����ڽӾ���
int LocateVex(AMGraph, VerTexType);		//���Ҷ��������±�
int FirstAdj(AMGraph, int);				//�ҵ����Ϊv�Ķ���ĵ�һ���ڽӶ�����
int NextAdj(AMGraph, int, int);			//��w��v���ڽӶ���, �ҵ�v������w�����һ���ڽӶ�����.
void DepthFirstSearch(AMGraph, int);		//����ͨͼ�Ӷ���v��ʼ����������ȷ���
void InitVisited();					//��ʼ�����ʱ�־����
bool visited[MVNum];					//���ʱ�־����

int main(){
	AMGraph G;
	CreateUDN(G);
	InitVisited();
	cout << "���ڽӾ���Ϊ��" << endl;
	for (int i = 0; i < G.vexnum; i++){		//�鿴�ڽӾ���ֵ���
		for (int j = 0; j < G.vexnum; j++){
			cout << G.arcs[i][j] << " ";
		}
		cout << endl;
	}
	int n;
	cout << "���ʴӵڼ����㿪ʼ������1~8����"; cin >> n;
	cout << "ͼ�ı�����" << endl;
	DepthFirstSearch(G, n);
	cout << endl;
	system("pause");
	return 0;
}

//�����ڽӾ���
int CreateUDN(AMGraph &G){
	VerTexType v1, v2;
	G.vexnum = 8; G.arcnum = 10;			//�趨Ϊ8�����㣬10���ߵ���ͨͼ
	cout << "���붥�����ƣ�" << endl;
	for (int i = 0; i < G.vexnum; ++i)
		cin>>G.vexs[i];
	for (int i = 0; i < G.vexnum; ++i)		//��ʼ���ڽӾ���
		for (int j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = 0;
	
	for (int k = 0; k < G.arcnum; ++k){
		cout << "���������֮��Ĺ�ϵ��v1,v2����" << endl;
		int i = 0, j = 0;
		cin >> v1 >> v2;
		i = LocateVex(G, v1); j = LocateVex(G, v2);
		G.arcs[i][j] = 1;
		G.arcs[j][i] = G.arcs[i][j];
	}
	return 0;
}

//���Ҷ��������±� G���ڽӾ���ṹ��V����������
int LocateVex(AMGraph G, VerTexType V){
	for (int i = 0; i < G.vexnum; i++){
		if (V == G.vexs[i]){
			return i;		//�ɹ����ң����ض�Ӧ�±�
		}
	}
	return -1;				//����ʧ�ܣ�����-1��
}

//�ҵ����Ϊv�Ķ���ĵ�һ���ڽӶ�����
int FirstAdj(AMGraph G, int v){
	for (int i = 0; i < G.vexnum; ++i){					//�ӵ�һ�п�ʼ����
		if (G.arcs[v][i] == 1 && visited[i] == false)	//��������δ���������򷵻ض�Ӧ�±�
			return i;
	}
	return -1;										//�ö���û���������ڽӶ��㣬����-1
}

//��w��v���ڽӶ���, �ҵ�v������w�����һ���ڽӶ�����
int NextAdj(AMGraph G, int v, int w){
	for (int i = w; i < G.vexnum; ++i){					//��w��ʼ��
		if (G.arcs[v][i] == 1 && visited[i] == false)	//�ҵ��������㣬��δ������
			return i;
	}
	return -1;										//����ʧ�ܷ���-1
}

//����ͨͼ�Ӷ�����v��ʼ����������ȷ���
void DepthFirstSearch(AMGraph G, int v){
	VerTexType m;				//�ѱ��vת��Ϊ��Ӧ������������Ѷ�Ӧ����������Ϊtrue
	m = G.vexs[v];
	cout << m << "->"; visited[v] = true;
	for (int w = FirstAdj(G, v); w >= 0; w = NextAdj(G, v, w)){ //���ҳ���õ������ĵ�һ����㣬δ����������б����������ҳ���һ���
		if (!visited[w])
			DepthFirstSearch(G, w);				//�ݹ����
	}
}

//��ʼ�����ʱ�־����
void InitVisited(){
	for (int i = 0; i < MVNum; i++){
		visited[i] = false;
	}
}
/*
�������ݣ�
1 2 3 4 5 6 7 8
1 2 1 3 2 4 2 5 3 6 3 7 4 8 5 8 6 8 7 8
*/
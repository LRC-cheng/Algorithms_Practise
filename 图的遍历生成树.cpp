#include<iostream>
#include<string>
using namespace std;

//图的邻接矩阵存储表示
#define MVNum 50 
typedef char VerTexType;		//顶点名称
typedef int ArcType;			//边
typedef struct{
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];//邻接矩阵
	int vexnum, arcnum;
}AMGraph;

int CreateUDN(AMGraph &);				//创建邻接矩阵
int LocateVex(AMGraph, VerTexType);		//查找顶点数组下标
int FirstAdj(AMGraph, int);				//找到编号为v的顶点的第一个邻接顶点编号
int NextAdj(AMGraph, int, int);			//设w是v的邻接顶点, 找到v的排在w后的下一个邻接顶点编号.
void DepthFirstSearch(AMGraph, int);		//对连通图从顶点v开始进行深度优先访问
void InitVisited();					//初始化访问标志数组
bool visited[MVNum];					//访问标志数组

int main(){
	AMGraph G;
	CreateUDN(G);
	InitVisited();
	cout << "该邻接矩阵为：" << endl;
	for (int i = 0; i < G.vexnum; i++){		//查看邻接矩阵赋值情况
		for (int j = 0; j < G.vexnum; j++){
			cout << G.arcs[i][j] << " ";
		}
		cout << endl;
	}
	int n;
	cout << "请问从第几个点开始遍历（1~8）："; cin >> n;
	cout << "图的遍历：" << endl;
	DepthFirstSearch(G, n);
	cout << endl;
	system("pause");
	return 0;
}

//创建邻接矩阵
int CreateUDN(AMGraph &G){
	VerTexType v1, v2;
	G.vexnum = 8; G.arcnum = 10;			//设定为8个顶点，10条边的连通图
	cout << "输入顶点名称：" << endl;
	for (int i = 0; i < G.vexnum; ++i)
		cin>>G.vexs[i];
	for (int i = 0; i < G.vexnum; ++i)		//初始化邻接矩阵
		for (int j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = 0;
	
	for (int k = 0; k < G.arcnum; ++k){
		cout << "输入各顶点之间的关系（v1,v2）：" << endl;
		int i = 0, j = 0;
		cin >> v1 >> v2;
		i = LocateVex(G, v1); j = LocateVex(G, v2);
		G.arcs[i][j] = 1;
		G.arcs[j][i] = G.arcs[i][j];
	}
	return 0;
}

//查找顶点数组下标 G：邻接矩阵结构，V：顶点名称
int LocateVex(AMGraph G, VerTexType V){
	for (int i = 0; i < G.vexnum; i++){
		if (V == G.vexs[i]){
			return i;		//成功查找，返回对应下标
		}
	}
	return -1;				//查找失败，返回-1；
}

//找到编号为v的顶点的第一个邻接顶点编号
int FirstAdj(AMGraph G, int v){
	for (int i = 0; i < G.vexnum; ++i){					//从第一列开始查找
		if (G.arcs[v][i] == 1 && visited[i] == false)	//若相连且未被遍历，则返回对应下标
			return i;
	}
	return -1;										//该顶点没有相连的邻接顶点，返回-1
}

//设w是v的邻接顶点, 找到v的排在w后的下一个邻接顶点编号
int NextAdj(AMGraph G, int v, int w){
	for (int i = w; i < G.vexnum; ++i){					//从w开始找
		if (G.arcs[v][i] == 1 && visited[i] == false)	//找到相连顶点，且未被遍历
			return i;
	}
	return -1;										//查找失败返回-1
}

//对连通图从顶点编号v开始进行深度优先访问
void DepthFirstSearch(AMGraph G, int v){
	VerTexType m;				//把编号v转换为对应名称输出，并把对应访问数组置为true
	m = G.vexs[v];
	cout << m << "->"; visited[v] = true;
	for (int w = FirstAdj(G, v); w >= 0; w = NextAdj(G, v, w)){ //先找出与该点相连的第一个结点，未被遍历则进行遍历，否则找出下一结点
		if (!visited[w])
			DepthFirstSearch(G, w);				//递归遍历
	}
}

//初始化访问标志数组
void InitVisited(){
	for (int i = 0; i < MVNum; i++){
		visited[i] = false;
	}
}
/*
测试数据：
1 2 3 4 5 6 7 8
1 2 1 3 2 4 2 5 3 6 3 7 4 8 5 8 6 8 7 8
*/
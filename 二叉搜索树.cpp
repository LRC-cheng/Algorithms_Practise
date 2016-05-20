#include<iostream>
#include<string>
using namespace std;

//二叉搜索树的三叉链表存储结构
typedef struct{
	string other;
	int key;
}TreeData;
typedef struct BSTNode{
	TreeData data;
	struct BSTNode *left, *right, *parent;
}BSTNode, *BSTree;

void InsertTree(BSTree &, TreeData);				//插入数据（允许数据重复）
void Transplant(BSTree &, BSTree, BSTree);		//移动子树
void Delete(BSTree &, BSTree);				//删除数据结点
BSTree Minimum(BSTree);			//找最小值
BSTree Maximum(BSTree);			//找最大值
BSTree Search(BSTree, int);			//搜索结点
BSTree Successor(BSTree);			//寻找后继
BSTree Predecessor(BSTree);			//寻找前驱
void CreatBSTree(BSTree &);			//先序遍历建立二叉搜索树，T:二叉搜索树
void InOrderTraverse(BSTree);		//中序遍历树（由小到大排列输出）
void PostOrderTraverse(BSTree);		//后序遍历

int main(){
	BSTree T, A, B;
	int n;
	cout << "创建二叉搜索树：";
	CreatBSTree(T);

	A = Maximum(T);
	cout << "最大最小值：" << "A.MAX = " << A->data.key;
	A = Minimum(T);
	cout << "A.MIN = " << A->data.key << endl;
	cout << "输入搜索数据：";
	cin >> n;
	cout << "搜索数据" << n << "并输出其父结点左右孩：" << endl;
	A = Search(T, n);
	cout << "A = " << A->data.key << endl;
	cout << "A->parent = ";
	if (A->parent)
		cout << A->parent->data.key << endl;
	else
		cout << "ERROR!,NULL";
	cout << "A->left = ";
	if (A->left)
		cout << A->left->data.key << endl;
	else
		cout << "ERROR!,NULL" << endl;
	cout << "A->right = ";
	if (A->right)
		cout << A->right->data.key << endl;
	else
		cout << "ERROR!,NULL" << endl;
	cout << "A的前驱后继：" << endl;
	B = Predecessor(A);
	if (B)
		cout << "A->predecessor = :" << B->data.key;
	else 
		cout << "ERROR!,NULL" << endl;
	B = Successor(A);
	if (B)
		cout << " ,A->successor = " << B->data.key << endl;
	else
		cout << "ERROR!,NULL" << endl;

	cout << "中序、后序遍历：" << endl;
	InOrderTraverse(T);
	cout << endl;
	PostOrderTraverse(T);
	cout << endl;
	B = A->parent;
	cout << "删除A点：";
	Delete(T, A);

	cout << "中序、后序遍历：" << endl;
	InOrderTraverse(T);
	cout << endl;
	PostOrderTraverse(T);
	cout << endl;

	system("pause");
	return 0;
}

//移动子树，把v移动到u处，u树将会分离出来
void Transplant(BSTree &T, BSTree u, BSTree v){
	if (!u->parent)				//u为根结点，直接把v替代根结点
		T = v;
	else if (u == u->parent->left)	//直接把v替代u的位置
		u->parent->left = v;
	else u->parent->right = v;
	if (v)						//若v不为空，更新其父结点
		v->parent = u->parent;
}
//删除数据结点（思路：删除前把z的后继代替z的位置）
void Delete(BSTree &T, BSTree z){
	BSTree y;
	if (!z->left)						//左子树为空，右子树接上，z分离出来
		Transplant(T, z, z->right);
	else if (!z->right)				//右子树为空，左子树接上，z分离出来
		Transplant(T, z, z->left);
	else{							//左右子树均不为空
		y = Minimum(z->right);			//z的后继--在右子树的最小值
		if (y->parent != z){			//若y不是z的孩子，就把z的右孩移到y的右孩处
			Transplant(T, y, y->right);//先把y的右孩移到y的位置，y单独游离了出来
			y->right = z->right;		//就把z的右孩移到y的右孩处
			y->right->parent = y;
		}
		Transplant(T, z, y);			//把y移到z处，z及其左子树从T分离了出来
		y->left = z->left;			//把z的左孩移到y的左孩，使z没孩子了
		y->left->parent = y;
	}
	delete z;						//把单独的z结点删除
}

//找最小值在最左边
BSTree Minimum(BSTree T){
	while (T->left)
		T = T->left;
	return T;
}
//找最大值在最右边
BSTree Maximum(BSTree T){
	while (T->right)
		T = T->right;
	return T;
}
//寻找后继
BSTree Successor(BSTree T){
	if (T->right)					//右树不为空，在右树最小值；右树为空，后继在父结点
		return Minimum(T->right);
	BSTree X = T->parent;
	while (X&&T == X->right){		//该结点属于右孩，即该父结点已经访问过，继续寻找
		T = X;
		X = X->parent;
	}
	return X;
}
//寻找前驱，与后继对称
BSTree Predecessor(BSTree T){
	if (T->left)
		return Maximum(T->left);
	BSTree X = T->parent;
	while (X&&T == X->left){
		T = X;
		X = X->parent;
	}
	return X;
}
//搜索结点
BSTree Search(BSTree T, int e){
	while (T&&e != T->data.key){	//树不为空则比较关键字
		if (e < T->data.key)
			T = T->left;
		else
			T = T->right;
	}
	return T;
}
//插入数据（允许数据重复）
void InsertTree(BSTree &T, TreeData e){
	if (!T){							//T为空，该处即为插入数据的地方
		BSTree S = new BSTNode;
		S->data = e;
		S->parent = S->left = S->right = NULL;
		T = S;
	}
	else if (e.key <= T->data.key){		//去掉不等号即为无重复数据插入
		InsertTree(T->left, e);
		T->left->parent = T;
	}
	else if (e.key > T->data.key){
		InsertTree(T->right, e);
		T->right->parent = T;
	}
}
//先序遍历建立二叉搜索树，T:二叉搜索树
void CreatBSTree(BSTree &T){
	TreeData e;
	T = NULL;
	for (;;){
		cin >> e.key >> e.other;
		if (cin.fail()){
			cin.clear();
			cin.sync();
			break;
		}
		InsertTree(T, e);
	}
}
//中序遍历树（由小到大排列输出）
void InOrderTraverse(BSTree T){
	if (T){
		InOrderTraverse(T->left);		//左树
		cout << T->data.key << "," << T->data.other << "->";	//根结点
		InOrderTraverse(T->right);		//右树
	}
}
//后序遍历
void PostOrderTraverse(BSTree T){
	if (T){
		PostOrderTraverse(T->left);		//左树
		PostOrderTraverse(T->right);	//右树
		cout << T->data.key <<","<<T->data.other<< "->";	//根结点
	}
}

//15 6 3 2 4 7 13 9 18 17 20 
//15 A 6 B 3 C 2 D 4 E 7 F 13 G 9 H 18 I 17 J 20 H
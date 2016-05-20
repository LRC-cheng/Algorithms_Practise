//Creat by LRC-cheng
#include<iostream>
#include<string>
using namespace std;
#define RED "Red"
#define BLACK "Black"
#define NIL 0
//红黑树的三叉链表存储结构
typedef short Other;
typedef struct{
	string Color;
	Other Info;
	int key;
}TreeData;
typedef struct RBTNode{
	TreeData data;
	struct RBTNode *left, *right, *parent;
}RBTNode, *RBTree;

void CreatBSTree(RBTree &);					//建立红黑树
void InsertTree(RBTree &, TreeData);			//插入数据（允许数据重复）
void RBInsertFixUp(RBTree &, RBTree);		//插入数据后维护工作
void Transplant(RBTree &, RBTree, RBTree);	//移动子树
void LeftRotate(RBTree &, RBTree);			//左旋
void RightRotate(RBTree &, RBTree);			//右旋
int Delete(RBTree &, int);					//删除数据结点 
void RBDeleteFixUp(RBTree &, RBTree);		//删除数据后维护工作
RBTree Minimum(RBTree);			//找最小值
RBTree Maximum(RBTree);			//找最大值
RBTree Search(RBTree, int);			//搜索结点
RBTree Successor(RBTree);			//寻找后继
RBTree Predecessor(RBTree);			//寻找前驱
void InOrderTraverse(RBTree);		//中序遍历树（由小到大排列输出）
void PostOrderTraverse(RBTree);		//后序遍历
void test(RBTree);					//测试功能

const RBTree Nil = new RBTNode;

int main(){
	Nil->left = Nil->right = Nil->parent = NULL;
	Nil->data.key = 0x3f3f3f3f;
	Nil->data.Color = BLACK;
	RBTree T ;
	T = Nil;
	T->parent = Nil;
/*------------初始化工作完毕-------------*/
	CreatBSTree(T);
	test(T);
	cout << endl;
	system("pause");
	return 0;
}

//建立红黑树
void CreatBSTree(RBTree &T){
	TreeData e;
	e.Color = RED;
	for (;;){
		cin >> e.key;
		if (cin.fail()){
			cin.clear();
			cin.sync();
			break;
		}
		InsertTree(T, e);
	}
}

//删除数据结点 
int Delete(RBTree &T, int e){
	RBTree z = new RBTNode;
	z = Search(T, e);
	if (z == Nil){
		return 0;
	}
	RBTree y = z, x;
	TreeData q;
	q.Color = y->data.Color;			//记录y的原色(这里其实记录的是z的颜色)
	if (z->left == Nil){				//左空，右树接上
		x = z->right;
		Transplant(T, z, z->right);
	}
	else if (z->right == Nil){			//右空，左树接上
		x = z->left;
		Transplant(T, z, z->left);
	}
	else{
		y = Minimum(z->right);			//z的后继
		q.Color = y->data.Color;		//记录y的原色
		x = y->right;
		if (y->parent == z)
			x->parent = y;			//防止移植后x的父结点指向z
		else{
			Transplant(T, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		Transplant(T, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->data.Color = z->data.Color;	//用y代替z的位置后把y置为z的颜色（z为红，则y被置为红）
	}
	delete z;


	cout << endl;
	cout << "删除后：（未维护）" << endl;
	cout << "中序遍历：";
	InOrderTraverse(T);
	cout << endl;
	cout << "后序遍历：";
	PostOrderTraverse(T);
	cout << endl;


	if (q.Color == BLACK)		//被删的z/y为黑色才要维护
		RBDeleteFixUp(T, x);	//x为指向y的原位置并更新删除后的位置

	return 1;
}
//删除数据后维护工作
void RBDeleteFixUp(RBTree &T, RBTree x){
	RBTree w = new RBTNode;
	while (x != T&&x->data.Color == BLACK){		//顶替结点x不为根结点，且x(y)为黑色时才要调整位置
		if (x == x->parent->left){
			w = x->parent->right;
			if (w->data.Color == RED){
				w->data.Color = BLACK;				//case 1
				x->parent->data.Color = RED;
				LeftRotate(T, x->parent);
				w = x->parent->right;
			}
			if (w->left->data.Color == BLACK&&w->right->data.Color == BLACK){
				w->data.Color = RED;				//case 2
				x = x->parent;
				if (x == T){
					break;
				}
			}
			else if (w->right->data.Color == BLACK){
				w->left->data.Color = BLACK;		//case 3
				w->data.Color = RED;
				RightRotate(T, w);
				w = x->parent->right;
			}
			w->data.Color = x->parent->data.Color;	//case 4
			x->parent->data.Color = BLACK;
			w->right->data.Color = BLACK;
			LeftRotate(T, x->parent);
			x = T;
		}
		else{
			w = x->parent->left;
			if (w->data.Color == RED){
				w->data.Color = BLACK;
				x->parent->data.Color = RED;
				RightRotate(T, x->parent);
				w = x->parent->left;
			}
			if (w->right->data.Color == BLACK&&w->right->data.Color == BLACK){
				w->data.Color = RED;
				x = x->parent;
				if (x == T){
					break;
				}
			}
			else if (w->left->data.Color == BLACK){
				w->right->data.Color = BLACK;
				w->data.Color = RED;
				LeftRotate(T, w);
				w = x->parent->left;
			}
			w->data.Color = x->parent->data.Color;
			x->parent->data.Color = BLACK;
			w->right->data.Color = BLACK;
			RightRotate(T, x->parent);
			x = T;
		}
	}
	x->data.Color = BLACK;
}
//移动子树
void Transplant(RBTree &T, RBTree u, RBTree v){
	if (u->parent == Nil)
		T = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else u->parent->right = v;
	v->parent = u->parent;
}
//插入数据（允许数据重复）
void InsertTree(RBTree &T, TreeData e){
	RBTree z = new RBTNode;
	z->data = e;
	RBTree y = Nil;
	RBTree x = T;
	while (x != Nil){
		y = x;					//记录父结点
		if (z->data.key <= x->data.key)
			x = x->left;
		else x = x->right;
	}
	z->parent = y;
	if (y == Nil)
		T = z;
	else if (z->data.key < y->data.key)
		y->left = z;
	else y->right = z;
	z->left = Nil;
	z->right = Nil;
	z->data.Color = RED;
	RBInsertFixUp(T, z);
}

//插入数据后维护工作
void RBInsertFixUp(RBTree &T, RBTree z){
	RBTree y = new RBTNode;
	while (z->parent->data.Color == RED){
		if (z->parent == z->parent->parent->left){
			y = z->parent->parent->right;			//y为z的叔结点
			if (y->data.Color == RED){
				z->parent->data.Color = BLACK;		//情况一 兄弟结点为红色，把兄弟结点变为黑色，使x处补充一个黑色
				y->data.Color = BLACK;
				z->parent->parent->data.Color = RED;
				z = z->parent->parent;
				if (z->parent == Nil){				//情况二 兄弟黑色，其孩子也是黑色，把兄弟变红色（减少旁边一个黑色结点数）
					break;
				}
			}
			else if (z == z->parent->right){		//情况三 兄弟左孩为红，先调整为情况四，再补充结点
				z = z->parent;
				LeftRotate(T, z);
			}
			z->parent->data.Color = BLACK;			//情况四，兄弟为黑，且右孩子为红，利用右树为左树补充一个黑结点
			z->parent->parent->data.Color = RED;
			if (z->parent->parent == Nil){
				break;
			}
			RightRotate(T, z->parent->parent);
		}
		else if (z->parent == z->parent->parent->right){
			y = z->parent->parent->left;			//y为z的叔结点
			if (y->data.Color == RED){
				z->parent->data.Color = BLACK;
				y->data.Color = BLACK;
				z->parent->parent->data.Color = RED;
				z = z->parent->parent;
				if (z->parent == Nil){
					break;
				}
			}
			else if (z == z->parent->left){
				z = z->parent;
				RightRotate(T, z);
			}
			z->parent->data.Color = BLACK;
			z->parent->parent->data.Color = RED;
			if (z->parent->parent == Nil){
				break;
			}
			LeftRotate(T, z->parent->parent);
		}
	}
	T->data.Color = BLACK;
}
//左旋
void LeftRotate(RBTree &T, RBTree x){
	RBTree y;
	y = x->right;
	x->right = y->left;
	if (y->left != Nil)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == Nil)
		T = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

//右旋
void RightRotate(RBTree &T, RBTree x){
	RBTree y;
	y = x->left;
	x->left = y->right;
	if (y->right != Nil)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == Nil)
		T = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->right = x;
	x->parent = y;
}

//找最小值
RBTree Minimum(RBTree T){
	while (T->left != Nil)
		T = T->left;
	return T;
}
//找最大值
RBTree Maximum(RBTree T){
	while (T->right != Nil)
		T = T->right;
	return T;
}
//寻找后继
RBTree Successor(RBTree T){
	if (T->right != Nil)
		return Minimum(T->right);
	RBTree X = T->parent;
	while (X != Nil&&T == X->right) {
		T = X;
		X = X->parent;
	}
	return X;
}
//寻找前驱
RBTree Predecessor(RBTree T){
	if (T->left != Nil)
		return Maximum(T->left);
	RBTree X = T->parent;
	while (X != Nil&&T == X->left){
		T = X;
		X = X->parent;
	}
	return X;
}
//搜索结点
RBTree Search(RBTree T, int e){
	while (T != Nil&&e != T->data.key){
		if (e < T->data.key)
			T = T->left;
		else
			T = T->right;
	}
	return T;
}
//中序遍历树（由小到大排列输出）
void InOrderTraverse(RBTree T){
	if (T != Nil){
		InOrderTraverse(T->left);		//左树
		cout << "(" << T->data.key << "," << T->data.Color << ")->";//根结点
		InOrderTraverse(T->right);		//右树
	}
}
//后序遍历
void PostOrderTraverse(RBTree T){
	if (T != Nil){
		PostOrderTraverse(T->left);		//左树
		PostOrderTraverse(T->right);	//右树
		cout << "(" << T->data.key << "," << T->data.Color << ")->";//根结点
	}
}

//测试功能
void test(RBTree T){
	RBTree A = new RBTNode;
	RBTree B = new RBTNode;
	int n;
	cout << "中序遍历：";
	InOrderTraverse(T);
	cout << endl;
	cout << "后序遍历：";
	PostOrderTraverse(T);
	cout << endl << endl;
	cout << "根结点为：" << T->data.key << "," << T->data.Color << endl;
	for (;;){
		cout << "输入搜索数据：";
		cin >> n;
		if (cin.fail()){
			cin.clear();
			cin.sync();
			break;
		}
		cout << "删除"<<n<<"点：";
		if (Delete(T, n))
			cout << "结点" << n << "已成功删除！" << endl;
		else
			cout << "ERROR!" << endl;

		cout << "根结点为：" << T->data.key << "," << T->data.Color;
		cout << endl;
		cout << "维护后：" << endl;
		cout << "中序遍历：";
		InOrderTraverse(T);
		cout << endl;
		cout << "后序遍历：";
		PostOrderTraverse(T);
		cout << endl;



		/*
		A = Maximum(T);
		cout << "最大最小值：" << "A.MAX = " << A->data.key;
		A = Minimum(T);
		cout << "，A.MIN = " << A->data.key << endl;
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
		cout << "A->predecessor = " << B->data.key;
		else
		cout << "ERROR!,NULL" << endl;
		B = Successor(A);
		if (B)
		cout << " ,A->successor = " << B->data.key << endl;
		else
		cout << "ERROR!,NULL" << endl;

		*/
	}
}
//11 2 7 1 5 4 8 14 15
//41 38 31 12 19 8
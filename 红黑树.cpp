//Creat by LRC-cheng
#include<iostream>
#include<string>
using namespace std;
#define RED "Red"
#define BLACK "Black"
#define NIL 0
//���������������洢�ṹ
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

void CreatBSTree(RBTree &);					//���������
void InsertTree(RBTree &, TreeData);			//�������ݣ����������ظ���
void RBInsertFixUp(RBTree &, RBTree);		//�������ݺ�ά������
void Transplant(RBTree &, RBTree, RBTree);	//�ƶ�����
void LeftRotate(RBTree &, RBTree);			//����
void RightRotate(RBTree &, RBTree);			//����
int Delete(RBTree &, int);					//ɾ�����ݽ�� 
void RBDeleteFixUp(RBTree &, RBTree);		//ɾ�����ݺ�ά������
RBTree Minimum(RBTree);			//����Сֵ
RBTree Maximum(RBTree);			//�����ֵ
RBTree Search(RBTree, int);			//�������
RBTree Successor(RBTree);			//Ѱ�Һ��
RBTree Predecessor(RBTree);			//Ѱ��ǰ��
void InOrderTraverse(RBTree);		//�������������С�������������
void PostOrderTraverse(RBTree);		//�������
void test(RBTree);					//���Թ���

const RBTree Nil = new RBTNode;

int main(){
	Nil->left = Nil->right = Nil->parent = NULL;
	Nil->data.key = 0x3f3f3f3f;
	Nil->data.Color = BLACK;
	RBTree T ;
	T = Nil;
	T->parent = Nil;
/*------------��ʼ���������-------------*/
	CreatBSTree(T);
	test(T);
	cout << endl;
	system("pause");
	return 0;
}

//���������
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

//ɾ�����ݽ�� 
int Delete(RBTree &T, int e){
	RBTree z = new RBTNode;
	z = Search(T, e);
	if (z == Nil){
		return 0;
	}
	RBTree y = z, x;
	TreeData q;
	q.Color = y->data.Color;			//��¼y��ԭɫ(������ʵ��¼����z����ɫ)
	if (z->left == Nil){				//��գ���������
		x = z->right;
		Transplant(T, z, z->right);
	}
	else if (z->right == Nil){			//�ҿգ���������
		x = z->left;
		Transplant(T, z, z->left);
	}
	else{
		y = Minimum(z->right);			//z�ĺ��
		q.Color = y->data.Color;		//��¼y��ԭɫ
		x = y->right;
		if (y->parent == z)
			x->parent = y;			//��ֹ��ֲ��x�ĸ����ָ��z
		else{
			Transplant(T, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		Transplant(T, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->data.Color = z->data.Color;	//��y����z��λ�ú��y��Ϊz����ɫ��zΪ�죬��y����Ϊ�죩
	}
	delete z;


	cout << endl;
	cout << "ɾ���󣺣�δά����" << endl;
	cout << "���������";
	InOrderTraverse(T);
	cout << endl;
	cout << "���������";
	PostOrderTraverse(T);
	cout << endl;


	if (q.Color == BLACK)		//��ɾ��z/yΪ��ɫ��Ҫά��
		RBDeleteFixUp(T, x);	//xΪָ��y��ԭλ�ò�����ɾ�����λ��

	return 1;
}
//ɾ�����ݺ�ά������
void RBDeleteFixUp(RBTree &T, RBTree x){
	RBTree w = new RBTNode;
	while (x != T&&x->data.Color == BLACK){		//������x��Ϊ����㣬��x(y)Ϊ��ɫʱ��Ҫ����λ��
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
//�ƶ�����
void Transplant(RBTree &T, RBTree u, RBTree v){
	if (u->parent == Nil)
		T = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else u->parent->right = v;
	v->parent = u->parent;
}
//�������ݣ����������ظ���
void InsertTree(RBTree &T, TreeData e){
	RBTree z = new RBTNode;
	z->data = e;
	RBTree y = Nil;
	RBTree x = T;
	while (x != Nil){
		y = x;					//��¼�����
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

//�������ݺ�ά������
void RBInsertFixUp(RBTree &T, RBTree z){
	RBTree y = new RBTNode;
	while (z->parent->data.Color == RED){
		if (z->parent == z->parent->parent->left){
			y = z->parent->parent->right;			//yΪz������
			if (y->data.Color == RED){
				z->parent->data.Color = BLACK;		//���һ �ֵܽ��Ϊ��ɫ�����ֵܽ���Ϊ��ɫ��ʹx������һ����ɫ
				y->data.Color = BLACK;
				z->parent->parent->data.Color = RED;
				z = z->parent->parent;
				if (z->parent == Nil){				//����� �ֵܺ�ɫ���亢��Ҳ�Ǻ�ɫ�����ֵܱ��ɫ�������Ա�һ����ɫ�������
					break;
				}
			}
			else if (z == z->parent->right){		//����� �ֵ���Ϊ�죬�ȵ���Ϊ����ģ��ٲ�����
				z = z->parent;
				LeftRotate(T, z);
			}
			z->parent->data.Color = BLACK;			//����ģ��ֵ�Ϊ�ڣ����Һ���Ϊ�죬��������Ϊ��������һ���ڽ��
			z->parent->parent->data.Color = RED;
			if (z->parent->parent == Nil){
				break;
			}
			RightRotate(T, z->parent->parent);
		}
		else if (z->parent == z->parent->parent->right){
			y = z->parent->parent->left;			//yΪz������
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
//����
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

//����
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

//����Сֵ
RBTree Minimum(RBTree T){
	while (T->left != Nil)
		T = T->left;
	return T;
}
//�����ֵ
RBTree Maximum(RBTree T){
	while (T->right != Nil)
		T = T->right;
	return T;
}
//Ѱ�Һ��
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
//Ѱ��ǰ��
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
//�������
RBTree Search(RBTree T, int e){
	while (T != Nil&&e != T->data.key){
		if (e < T->data.key)
			T = T->left;
		else
			T = T->right;
	}
	return T;
}
//�������������С�������������
void InOrderTraverse(RBTree T){
	if (T != Nil){
		InOrderTraverse(T->left);		//����
		cout << "(" << T->data.key << "," << T->data.Color << ")->";//�����
		InOrderTraverse(T->right);		//����
	}
}
//�������
void PostOrderTraverse(RBTree T){
	if (T != Nil){
		PostOrderTraverse(T->left);		//����
		PostOrderTraverse(T->right);	//����
		cout << "(" << T->data.key << "," << T->data.Color << ")->";//�����
	}
}

//���Թ���
void test(RBTree T){
	RBTree A = new RBTNode;
	RBTree B = new RBTNode;
	int n;
	cout << "���������";
	InOrderTraverse(T);
	cout << endl;
	cout << "���������";
	PostOrderTraverse(T);
	cout << endl << endl;
	cout << "�����Ϊ��" << T->data.key << "," << T->data.Color << endl;
	for (;;){
		cout << "�����������ݣ�";
		cin >> n;
		if (cin.fail()){
			cin.clear();
			cin.sync();
			break;
		}
		cout << "ɾ��"<<n<<"�㣺";
		if (Delete(T, n))
			cout << "���" << n << "�ѳɹ�ɾ����" << endl;
		else
			cout << "ERROR!" << endl;

		cout << "�����Ϊ��" << T->data.key << "," << T->data.Color;
		cout << endl;
		cout << "ά����" << endl;
		cout << "���������";
		InOrderTraverse(T);
		cout << endl;
		cout << "���������";
		PostOrderTraverse(T);
		cout << endl;



		/*
		A = Maximum(T);
		cout << "�����Сֵ��" << "A.MAX = " << A->data.key;
		A = Minimum(T);
		cout << "��A.MIN = " << A->data.key << endl;
		cout << "�����������ݣ�";
		cin >> n;
		cout << "��������" << n << "������丸������Һ���" << endl;
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
		cout << "A��ǰ����̣�" << endl;
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
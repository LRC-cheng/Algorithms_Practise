#include<iostream>
#include<string>
using namespace std;

//��������������������洢�ṹ
typedef struct{
	string other;
	int key;
}TreeData;
typedef struct BSTNode{
	TreeData data;
	struct BSTNode *left, *right, *parent;
}BSTNode, *BSTree;

void InsertTree(BSTree &, TreeData);				//�������ݣ����������ظ���
void Transplant(BSTree &, BSTree, BSTree);		//�ƶ�����
void Delete(BSTree &, BSTree);				//ɾ�����ݽ��
BSTree Minimum(BSTree);			//����Сֵ
BSTree Maximum(BSTree);			//�����ֵ
BSTree Search(BSTree, int);			//�������
BSTree Successor(BSTree);			//Ѱ�Һ��
BSTree Predecessor(BSTree);			//Ѱ��ǰ��
void CreatBSTree(BSTree &);			//�����������������������T:����������
void InOrderTraverse(BSTree);		//�������������С�������������
void PostOrderTraverse(BSTree);		//�������

int main(){
	BSTree T, A, B;
	int n;
	cout << "����������������";
	CreatBSTree(T);

	A = Maximum(T);
	cout << "�����Сֵ��" << "A.MAX = " << A->data.key;
	A = Minimum(T);
	cout << "A.MIN = " << A->data.key << endl;
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
		cout << "A->predecessor = :" << B->data.key;
	else 
		cout << "ERROR!,NULL" << endl;
	B = Successor(A);
	if (B)
		cout << " ,A->successor = " << B->data.key << endl;
	else
		cout << "ERROR!,NULL" << endl;

	cout << "���򡢺��������" << endl;
	InOrderTraverse(T);
	cout << endl;
	PostOrderTraverse(T);
	cout << endl;
	B = A->parent;
	cout << "ɾ��A�㣺";
	Delete(T, A);

	cout << "���򡢺��������" << endl;
	InOrderTraverse(T);
	cout << endl;
	PostOrderTraverse(T);
	cout << endl;

	system("pause");
	return 0;
}

//�ƶ���������v�ƶ���u����u������������
void Transplant(BSTree &T, BSTree u, BSTree v){
	if (!u->parent)				//uΪ����㣬ֱ�Ӱ�v��������
		T = v;
	else if (u == u->parent->left)	//ֱ�Ӱ�v���u��λ��
		u->parent->left = v;
	else u->parent->right = v;
	if (v)						//��v��Ϊ�գ������丸���
		v->parent = u->parent;
}
//ɾ�����ݽ�㣨˼·��ɾ��ǰ��z�ĺ�̴���z��λ�ã�
void Delete(BSTree &T, BSTree z){
	BSTree y;
	if (!z->left)						//������Ϊ�գ����������ϣ�z�������
		Transplant(T, z, z->right);
	else if (!z->right)				//������Ϊ�գ����������ϣ�z�������
		Transplant(T, z, z->left);
	else{							//������������Ϊ��
		y = Minimum(z->right);			//z�ĺ��--������������Сֵ
		if (y->parent != z){			//��y����z�ĺ��ӣ��Ͱ�z���Һ��Ƶ�y���Һ���
			Transplant(T, y, y->right);//�Ȱ�y���Һ��Ƶ�y��λ�ã�y���������˳���
			y->right = z->right;		//�Ͱ�z���Һ��Ƶ�y���Һ���
			y->right->parent = y;
		}
		Transplant(T, z, y);			//��y�Ƶ�z����z������������T�����˳���
		y->left = z->left;			//��z�����Ƶ�y���󺢣�ʹzû������
		y->left->parent = y;
	}
	delete z;						//�ѵ�����z���ɾ��
}

//����Сֵ�������
BSTree Minimum(BSTree T){
	while (T->left)
		T = T->left;
	return T;
}
//�����ֵ�����ұ�
BSTree Maximum(BSTree T){
	while (T->right)
		T = T->right;
	return T;
}
//Ѱ�Һ��
BSTree Successor(BSTree T){
	if (T->right)					//������Ϊ�գ���������Сֵ������Ϊ�գ�����ڸ����
		return Minimum(T->right);
	BSTree X = T->parent;
	while (X&&T == X->right){		//�ý�������Һ������ø�����Ѿ����ʹ�������Ѱ��
		T = X;
		X = X->parent;
	}
	return X;
}
//Ѱ��ǰ�������̶Գ�
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
//�������
BSTree Search(BSTree T, int e){
	while (T&&e != T->data.key){	//����Ϊ����ȽϹؼ���
		if (e < T->data.key)
			T = T->left;
		else
			T = T->right;
	}
	return T;
}
//�������ݣ����������ظ���
void InsertTree(BSTree &T, TreeData e){
	if (!T){							//TΪ�գ��ô���Ϊ�������ݵĵط�
		BSTree S = new BSTNode;
		S->data = e;
		S->parent = S->left = S->right = NULL;
		T = S;
	}
	else if (e.key <= T->data.key){		//ȥ�����Ⱥż�Ϊ���ظ����ݲ���
		InsertTree(T->left, e);
		T->left->parent = T;
	}
	else if (e.key > T->data.key){
		InsertTree(T->right, e);
		T->right->parent = T;
	}
}
//�����������������������T:����������
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
//�������������С�������������
void InOrderTraverse(BSTree T){
	if (T){
		InOrderTraverse(T->left);		//����
		cout << T->data.key << "," << T->data.other << "->";	//�����
		InOrderTraverse(T->right);		//����
	}
}
//�������
void PostOrderTraverse(BSTree T){
	if (T){
		PostOrderTraverse(T->left);		//����
		PostOrderTraverse(T->right);	//����
		cout << T->data.key <<","<<T->data.other<< "->";	//�����
	}
}

//15 6 3 2 4 7 13 9 18 17 20 
//15 A 6 B 3 C 2 D 4 E 7 F 13 G 9 H 18 I 17 J 20 H
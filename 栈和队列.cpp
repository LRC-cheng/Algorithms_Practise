#include<iostream>
#include<string>
#define MAXSIZE 10
using namespace std;

typedef struct{					//ջ�Ĵ洢�ṹ
	int *base;
	int *top;
	int stacksize;
}SqStack;

typedef struct {					//���еĴ洢�ṹ
	int *base;
	int front;
	int rear;
}SqQueue;

int InitStack(SqStack &);			//��ʼ��ջ
bool StackEmpty(SqStack &);			//�ж��Ƿ�Ϊ��ջ
bool Push(SqStack &, int);			//��ջ
bool Pop(SqStack &, int &);		//��ջ
int GetTop(SqStack &, int &);		//ȡջ��

int InitQueue(SqQueue &);			//��ʼ������
int EnQueue(SqQueue &, int);		//���
int QueueLength(SqQueue);			//��ӳ���
int DeQueue(SqQueue &, int &);		//����
int GetHead(SqQueue);				//ȡ��ͷ

void testqueue();
void teststack();

int main(){	
	teststack();
	testqueue();
	system("pause");
	return 0;
}

int InitStack(SqStack &S){			//��ʼ��ջ
	S.base = new int[MAXSIZE];
	if (!S.base)
		exit(OVERFLOW);			//�洢����ʧ��
	S.top = S.base ;
	S.stacksize = MAXSIZE;
	return 0;
}
bool StackEmpty(SqStack &S){		//�ж��Ƿ�Ϊ��ջ
	if (S.top == S.base)
		return true;
	else return false;
}

bool Push(SqStack &S, int e){		//��ջ
	if (S.top - S.base == S.stacksize) {
		cout << "��ջ����ջʧ�ܣ�"<<endl;
		return false;
	}
	*S.top ++= e;
	return true;
}

bool Pop(SqStack &S, int & e){		//��ջ
	if (StackEmpty(S)){
		cout << "ERROR" << endl;
		return false;
	}
	else{
		e = *--S.top;
		return true;
	}
}

int GetTop(SqStack &S, int &e){		//ȡջ��
	if (S.top != S.base)
		return *(S.top - 1);
}

void teststack(){
	cout << "-------------ջ-------------" << endl;
	SqStack S;
	int x;
	InitStack(S);

	for (int i = 0; i < 11; i++){
		Push(S, i);
	}
	cout << "ջ����" << GetTop(S, x) << endl;
	for (int i = 0; i < 5; i++){
		if (Pop(S, x))
			cout << "��ջԪ���ǣ�" << x << endl;
	}
	cout << "ջ����" << GetTop(S, x) << endl;
	if (StackEmpty(S))
		cout << "true" << endl;
	else
		cout << "false" << endl;
}

int InitQueue(SqQueue &Q){			//��ʼ������
	Q.base = new int[MAXSIZE];
	if (!Q.base)
		exit(OVERFLOW);
	Q.front = Q.rear = 0;
	return 0;
}

int QueueLength(SqQueue Q){			//��ӳ���
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

int EnQueue(SqQueue &Q, int e){		//���
	if ((Q.rear + 1) % MAXSIZE == Q.front){
		cout << "ERROR!";
		return 0;
	}
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXSIZE;
	return 0;
}

int DeQueue(SqQueue &Q, int &e){	//����
	if (Q.front == Q.rear){
		cout << "ERROR!" << endl;
		return 0;
	}
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXSIZE;
	return 1;
}
int GetHead(SqQueue Q){			//ȡ��ͷ
	if (Q.front != Q.rear)
		return Q.base[Q.front];
}

void testqueue(){
	cout << "------------����------------" << endl;
	SqQueue Q;
	int x;
	InitQueue(Q);
	for (int i = 0; i < 10; i++){
		EnQueue(Q, 2*i);
	}
	cout << "���г��ȣ�" << QueueLength(Q) << endl;
	cout << "��ͷԪ�أ�" << GetHead(Q) << endl;
	for (int i = 0; i < 10; i++){
		if (DeQueue(Q, x))
			cout << "����Ԫ�أ�" << x << endl;
	}

}
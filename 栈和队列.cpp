#include<iostream>
#include<string>
#define MAXSIZE 10
using namespace std;

typedef struct{					//栈的存储结构
	int *base;
	int *top;
	int stacksize;
}SqStack;

typedef struct {					//队列的存储结构
	int *base;
	int front;
	int rear;
}SqQueue;

int InitStack(SqStack &);			//初始化栈
bool StackEmpty(SqStack &);			//判断是否为空栈
bool Push(SqStack &, int);			//入栈
bool Pop(SqStack &, int &);		//出栈
int GetTop(SqStack &, int &);		//取栈顶

int InitQueue(SqQueue &);			//初始化队列
int EnQueue(SqQueue &, int);		//入队
int QueueLength(SqQueue);			//求队长度
int DeQueue(SqQueue &, int &);		//出队
int GetHead(SqQueue);				//取队头

void testqueue();
void teststack();

int main(){	
	teststack();
	testqueue();
	system("pause");
	return 0;
}

int InitStack(SqStack &S){			//初始化栈
	S.base = new int[MAXSIZE];
	if (!S.base)
		exit(OVERFLOW);			//存储分配失败
	S.top = S.base ;
	S.stacksize = MAXSIZE;
	return 0;
}
bool StackEmpty(SqStack &S){		//判断是否为空栈
	if (S.top == S.base)
		return true;
	else return false;
}

bool Push(SqStack &S, int e){		//入栈
	if (S.top - S.base == S.stacksize) {
		cout << "满栈，入栈失败！"<<endl;
		return false;
	}
	*S.top ++= e;
	return true;
}

bool Pop(SqStack &S, int & e){		//出栈
	if (StackEmpty(S)){
		cout << "ERROR" << endl;
		return false;
	}
	else{
		e = *--S.top;
		return true;
	}
}

int GetTop(SqStack &S, int &e){		//取栈顶
	if (S.top != S.base)
		return *(S.top - 1);
}

void teststack(){
	cout << "-------------栈-------------" << endl;
	SqStack S;
	int x;
	InitStack(S);

	for (int i = 0; i < 11; i++){
		Push(S, i);
	}
	cout << "栈顶：" << GetTop(S, x) << endl;
	for (int i = 0; i < 5; i++){
		if (Pop(S, x))
			cout << "出栈元素是：" << x << endl;
	}
	cout << "栈顶：" << GetTop(S, x) << endl;
	if (StackEmpty(S))
		cout << "true" << endl;
	else
		cout << "false" << endl;
}

int InitQueue(SqQueue &Q){			//初始化队列
	Q.base = new int[MAXSIZE];
	if (!Q.base)
		exit(OVERFLOW);
	Q.front = Q.rear = 0;
	return 0;
}

int QueueLength(SqQueue Q){			//求队长度
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

int EnQueue(SqQueue &Q, int e){		//入队
	if ((Q.rear + 1) % MAXSIZE == Q.front){
		cout << "ERROR!";
		return 0;
	}
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXSIZE;
	return 0;
}

int DeQueue(SqQueue &Q, int &e){	//出队
	if (Q.front == Q.rear){
		cout << "ERROR!" << endl;
		return 0;
	}
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXSIZE;
	return 1;
}
int GetHead(SqQueue Q){			//取队头
	if (Q.front != Q.rear)
		return Q.base[Q.front];
}

void testqueue(){
	cout << "------------队列------------" << endl;
	SqQueue Q;
	int x;
	InitQueue(Q);
	for (int i = 0; i < 10; i++){
		EnQueue(Q, 2*i);
	}
	cout << "队列长度：" << QueueLength(Q) << endl;
	cout << "队头元素：" << GetHead(Q) << endl;
	for (int i = 0; i < 10; i++){
		if (DeQueue(Q, x))
			cout << "出队元素：" << x << endl;
	}

}
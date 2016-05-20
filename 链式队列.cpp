/*created by LRC-cheng*/
#include<iostream>
#include<string>
using namespace std;

//链式队列存储结构
typedef struct QNode{
	char data;			//数据域
	struct QNode *next;	//指针域
}QNode, *QueuePtr;
typedef struct{
	QueuePtr front;		//队头指针
	QueuePtr rear;		//队尾指针
}LinkQueue;


int InitQueue(LinkQueue &);			//初始化
int EnQueue(LinkQueue &, char);		//队列入队
bool DeQueue(LinkQueue &, char &);	//出队
char GetHead(LinkQueue);			//取队头元素

int main(){
	cout << "-------------链式队列------------" << endl;
	cout << "说明：Ctrl+Z结束输入; '#'结束测试！" << endl;
	LinkQueue KeyBoard;
	InitQueue(KeyBoard);
	char x;
	int k;							//记录输入的数据量
	cout << "输入数据：";
	for (;;){
		k = 0;						//重置标志
		for (;;){
			cin >> x;
			if (cin.fail()){			//输入失败，退出输入循环
				break;
			}
			EnQueue(KeyBoard, x);		//输入成功，入队
			k++;
		}
		cin.clear();					//清空cin缓存
		for (int i = 0; i < k; i++){	//出队
			DeQueue(KeyBoard, x);
			cout << x << "    ";
		}
		cout << endl;
		if (x == '#'){
			break;
		}
	}
	system("pause");
	return 0;
}

//初始化 Q:队列
int InitQueue(LinkQueue &Q){			
	Q.front = Q.rear = new QNode;	//队头队尾均指向头结点
	Q.front->next = NULL;
	return 0;
}

//队列入队 Q:队列，e：入队元素
int EnQueue(LinkQueue &Q, char e){		
	QueuePtr p = new QNode;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;		//把新结点放到队尾
	Q.rear = p;
	return 0;
}

//出队 Q:队列，e：记录出队元素
bool DeQueue(LinkQueue &Q, char &e){
	if (Q.front == Q.rear){
		cout << "错误，队列为空！" << endl;
		return false;
	}
	QueuePtr p = new QNode;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)			//最后一个元素被删，队尾指针指向头结点
		Q.rear = Q.front;
	delete p;				//释放空间
	return true;
}

//取队头元素 Q:队列
char GetHead(LinkQueue Q){
	if (Q.front != Q.rear)			//队列非空
		return Q.front->next->data;
}

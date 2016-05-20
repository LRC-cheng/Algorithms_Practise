#include<iostream>
#include<string>
using namespace std;

//��ʽ���д洢�ṹ
typedef struct QNode{
	char data;			//������
	struct QNode *next;	//ָ����
}QNode, *QueuePtr;
typedef struct{
	QueuePtr front;		//��ͷָ��
	QueuePtr rear;		//��βָ��
}LinkQueue;


int InitQueue(LinkQueue &);			//��ʼ��
int EnQueue(LinkQueue &, char);		//�������
bool DeQueue(LinkQueue &, char &);	//����
char GetHead(LinkQueue);			//ȡ��ͷԪ��

int main(){
	cout << "-------------��ʽ����------------" << endl;
	cout << "���Է���ƥ�䡰'[',']','(',')','{','}'����˵����Ctrl+Z��������; '#'�������ԣ�" << endl;
	LinkQueue KeyBoard;
	InitQueue(KeyBoard);
	char x;
	int k;							//��¼�����������
	cout << "�������ݣ�";
	for (;;){
		k = 0;						//���ñ�־
		for (;;){
			cin >> x;
			if (cin.fail()){			//����ʧ�ܣ��˳�����ѭ��
				break;
			}
			EnQueue(KeyBoard, x);		//����ɹ������
			k++;
		}
		cin.clear();					//���cin����
		for (int i = 0; i < k; i++){	//����
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

//��ʼ�� Q:����
int InitQueue(LinkQueue &Q){			
	Q.front = Q.rear = new QNode;	//��ͷ��β��ָ��ͷ���
	Q.front->next = NULL;
	return 0;
}

//������� Q:���У�e�����Ԫ��
int EnQueue(LinkQueue &Q, char e){		
	QueuePtr p = new QNode;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;		//���½��ŵ���β
	Q.rear = p;
	return 0;
}

//���� Q:���У�e����¼����Ԫ��
bool DeQueue(LinkQueue &Q, char &e){
	if (Q.front == Q.rear){
		cout << "���󣬶���Ϊ�գ�" << endl;
		return false;
	}
	QueuePtr p = new QNode;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)			//���һ��Ԫ�ر�ɾ����βָ��ָ��ͷ���
		Q.rear = Q.front;
	delete p;				//�ͷſռ�
	return true;
}

//ȡ��ͷԪ�� Q:����
char GetHead(LinkQueue Q){
	if (Q.front != Q.rear)			//���зǿ�
		return Q.front->next->data;
}

#include <iostream>
using namespace std;

const int QUEUELEN=10;
class student{
public:
	int age;
	char *name;
};

class Queue{
public:
	student data[QUEUELEN];
	int head;
	int tail;
};

Queue *QuInit(){
	Queue *q;
	if (!(q=new Queue))
		return 0;
	q->head=0;
	q->tail=0;
	return q;
}

int IsEmpty(Queue *q){//If empty then return 1.
	int t;
	t=(q->head==q->tail);
	return 1;
}

int IsFull(Queue *q){
	int t;
	t=(q->tail==QUEUELEN);
	return t;
}

void QuClear(Queue *q){
	q->head=0;
	q->tail=0;
}

void QuFree(Queue *q){
	if (q)
		delete q;
}

int QuIn(Queue *q,student data){
	if (q->tail==QUEUELEN){
		cout<<"Error:Queue is Full!"<<endl;
		return 0;
	}
	q->data[q->tail++]=data;
	return 1;
}

student QuOut(Queue *q){
	if (q->head==q->tail){
		cout<<"Error:Queue is empty!"<<endl;
		exit(0);
	}
	else 
		return (q->data[q->head++]);
}

student QuRead(Queue *q){
	if (q->head==q->tail){
		cout<<"Error:Queue is empty!"<<endl;
		exit(0);
	}
	else 
		return (q->data[q->head]);
}

int QuLen(Queue *q){
	int t;
	t=q->tail-q->head;
	return t;
}

int main()
{
	system("pause");
	return 0;
}

#include <iostream>
using namespace std;

const int MAX=10;
class student{
public:
	int age;
	char name[20];
};

class Stack{
public:
	student data[MAX+1];
	int top;
};

Stack *StInit(){
	Stack *p;
	if (p=(new Stack)){
		p->top=0;
		return p;
	}
	return 0;
}

int IsEmpty(Stack *st){//If empty then return 1.
	int t;
	t=(st->top==0);
	return t;
}

int IsFull(Stack *st){//If full thrn return 1.
	int t;
	t=(st->top==MAX);
	return t;
}

void StClear(Stack *st){
	st->top=0;
}

void StFree(Stack *st){
	if (st){
		delete st;
	}
}

int StPush(Stack *st,student data){
	if (!IsFull(st))
	{
		cout<<"Error:Stack is full!"<<endl;
		return 0;
	}
	st->data[++st->top]=data;
	return 1;
}

student StPop(Stack *st){
	if (!IsEmpty(st)){
		cout<<"Error:Stack is empty!"<<endl;
		exit(0);
	}
	else
		return (st->data[st->top--]);
}

student StRead(Stack *st){
	if (!IsEmpty(st)){
		cout<<"Error:Stack is empty!"<<endl;
		exit(0);
	}
	else
		return (st->data[st->top]);
}

int main()
{
	system("pause");
	return 0;
}

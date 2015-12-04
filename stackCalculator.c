#include<stdio.h>
#include<assert.h>

/*
作者：yungkc
功能：利用栈，递归计算逆波兰表达式
说明：数字之间需要空格，不支持负数
*/

#define MAX 100 //表达式最大长度
int strLen(char *s){
	int i=0;
	while(s[i]!='\n' && s[i]!='\0') i++;
	return i;
}
int isNum(char c){
	return c>='0'&&c<='9'?1:0;
}

typedef union{
	double num;
	char op;
}Stack;
Stack stack[MAX];
int top=0;

void push(Stack data){//入栈
	if(top==MAX) return;
	stack[top++]=data;
}
Stack pop(){//出栈
	if(!top) return;
	return stack[--top];
}

double result(){//递归出栈，计算
	Stack s=pop();
	double a,b;
	switch(s.op){
		case '+':return result()+result();
		case '*':return result()*result();
		case '-':
			a=result(),b=result();
			return b-a;
		case '/':
			a=result(),b=result();
			assert(a!=0);
			return b/a;
		default:
			return s.num;
	}
}
void creat(char *c){//数字，运算符入栈
	double n=0;
	int i=0,k;
	Stack st;
	while(c[i]){
		k=1;
		n=0;
		if(isNum(c[i])){
			while(isNum(c[i]))
				n=n*10+(c[i++]-'0');
			if(c[i]=='.'){
				++i;
				while(isNum(c[i])){
					n+=((c[i++]-'0')/(10.0*k++));
				}
			}
			st.num=n;
			push(st);
			printf("%3d     :  %8.4lf\n",top,st.num);
		}
		if(c[i]==' ') ++i;
		else{
			st.op=c[i];
			push(st);
			printf("%3d     :  %5c\n",top,st.op);
			++i;
		}
	}
}

int main(){
	char s[MAX]="1.1 0.6+4.7*19.6-77.2+4.129 46.6 24.794-/33.4/-";//测试用，正常
	//fgets(s,MAX,stdin);
	s[strLen(s)]='\0';
	printf(" top    :  stack[top]\n");
	creat(s);
	printf("\nResult is : %lf\n",result());
	return 0;
}

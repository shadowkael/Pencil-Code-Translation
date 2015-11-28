#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

/*
作者：yungkc
功能：对正常的数学表达式求值，可包含以下运算符
运算符优先级
1: ( )
2: * / %
3: + -
*/
#define LEN 50
//functions
int isInt(double n){//判断是否是整数
	return n==(int)n?1:0;
}
double power(double n,double p){//返回n的p次方
	double m=1;
	while(p--) m*=n;
	return m;
}
int Bracket(char *s,int n){//跳过表达式s中的括号
	int i=0,m=1;
	while(m){
		if(s[--i]==')') ++m;
		if(s[i]=='(') --m;
	}
	return n+i;
}
int priority(char *s,int n,int p){//返回s中从右至左第一个优先级为p的运算符的位置，若无，返回0
	int i=n-1;
	if(p==3){
		while(i>0){
			if(s[i]=='+' || s[i]=='-') return i;
			else if(s[i]==')') i=Bracket(s+i,i);
			else --i;
		}
	}else if(p==2){
		while(i>0){
			if(s[i]=='*' || s[i]=='/' || s[i]=='%') return i;
			if(s[i]==')') i=Bracket(s+i,i);
			else --i;
		}
	}
	return 0;
}
double stod(char *s){//将s转换为double类型并返回
	double n=0;
	int m=1,i=0;
	if(s[0]=='-'){
		++i;
		while(s[i]!='.' && s[i]!='\0')
			n=(s[i++]-'0')+n*10;
		if(s[i]=='.'){
			while(s[++i]) n+=(s[i]-'0')/power(10,m++);
		}
		n*=-1;
	}else{
		while(s[i]!='.' && s[i])
			n=(s[i++]-'0')+n*10;
		if(s[i]=='.'){
			while(s[++i]) n+=(s[i]-'0')/power(10,m++);
		}
	}
	return n;
}
void strspl(char *s,char *s1,char *s2,int sign){//令s[sign]='\0'，从s[sign]处将s分为s1，s2两部分
	s[sign]='\0';
	int i=0,m=0;
	do{s1[i]=s[i];}while(s[i++]);
	do{s2[m++]=s[i];}while(s[i++]);
}
void Delbracket(char *s,int n){//删去表达式s的括号
	int i;
	for(i=0;i<n-1;i++)
		s[i]=s[i+1];
	s[n-3]='\0';
	printf("\n%s\n",s);
}

//Tree Node
typedef union{
	double num;
	char op;
}Data;
typedef struct CBT{
	Data data;
	struct CBT *left,*right;
}Tree;

//Tree functions
Tree *Createxp(char *s,int size){//递归分割表达式，创建树
	Tree *p=(Tree*)malloc(sizeof(Tree));
	int p3,p2;
	char s1[LEN],s2[LEN];
	p->left=NULL;
	p->right=NULL;
	if(!(p3=priority(s,size,3))){//查找优先级3
		if(!(p2=priority(s,size,2))){//查找优先级2
			if(s[0]=='('){
				Delbracket(s,size+1);
				Createxp(s,size-2);
			}else{
				p->data.num=stod(s);
				return p;
			}
		}else{
			p->data.op=s[p2];
			strspl(s,s1,s2,p2);
			printf("%c %s    %s\n",p->data.op,s1,s2);
			p->left=Createxp(s1,strlen(s1));
			p->right=Createxp(s2,strlen(s2));
			return p;
		}
	}else{
		p->data.op=s[p3];
		strspl(s,s1,s2,p3);
		printf("%c %s    %s\n",p->data.op,s1,s2);
		p->left=Createxp(s1,strlen(s1));
		p->right=Createxp(s2,strlen(s2));
		return p;
	}
}
double result(Tree *p){//递归求值
	if(!p->left) return p->data.num;
	Tree *pl=p->left,*pr=p->right;
	double n;
	switch(p->data.op){
	case '+':
		n=result(pl)+result(pr);break;
	case '-':
		n=result(pl)-result(pr);break;
	case '*':
		n=result(pl)*result(pr);break;
	case '/':
		assert(result(pr)!=0);
		n=result(pl)/result(pr);break;
	case '%':
		assert(result(pr)!=0);
		if(isInt(result(pl)) && isInt(result(pr)))
			n=(int)result(pl)%(int)result(pr);break;
	default:printf("Operation Error!\n");
	}
	return n;
}
void ShowTree(Tree *treeNode){//遍历树
	if(treeNode->left){
		printf("%c   ",treeNode->data.op);
		ShowTree(treeNode->left);
		ShowTree(treeNode->right);
	}else
		printf("%lf   ",treeNode->data.num);
}
void ClearTree(Tree *treeNode){//清空树
	if(treeNode){
		ClearTree(treeNode->left);
		ClearTree(treeNode->right);
		free(treeNode);
		treeNode=NULL;
	}
}

//main()
int main(){
	char s[LEN]="((7+(-8.2))*3.44-(-6))+2-5-4/(7.1+0.332)";
	printf("Input the expression: ");
	scanf("%s",s);
	putchar('\n');
	Tree *exp;
	exp=Createxp(s,strlen(s));
	putchar('\n');
	ShowTree(exp);
	putchar('\n');
	printf("\nResult is: %lf\n",result(exp));
	ClearTree(exp);
	return 0;
}

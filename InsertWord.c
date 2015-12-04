#include<stdio.h>

void strcatt(char *s,char *t){//连接
	while(*s) ++s;
	while(*s=*t) ++s,++t;
}
void strspl(char *s,char *tmp,int sign){//拆分
	int i=sign+1,m=0;
	do{tmp[++m]=s[i];}while(s[i++]);
	tmp[0]=' ';
	s[sign+1]='\0';
}
char s[50];
int main(){
	int i=0,n,m=0;
	char t,tmp[50],word[10];
	printf("Input string: ");
	while((t=getchar())!='\n') s[i++]=t;
	s[i]='\0';
	i=0;
	printf("Input n: ");
	scanf("%d",&n);
	while(s[i] && m!=n){
		if(s[i++]==' ') ++m;
	}
	strspl(s,tmp,i-1);
	printf("Input word: ");
	scanf("%s",word);
	strcatt(s,word);
	strcatt(s,tmp);
	printf("%s",s);
	return 0;
}

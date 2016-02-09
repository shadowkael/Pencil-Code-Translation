#include<stdio.h>

int main(){
	int a,b,n,i,sign;
	scanf("%d%d",&a,&b);
	if(a==b&&a==0) return;
	sign=0,n=0;
	for(i=0;a>0 && b>0;i++){
		sign=(a%10+b%10+sign>9)?1:0;
		n+=sign;
		a/=10,b/=10;
	}
	printf("%d",n);
	return 0;
}

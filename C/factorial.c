#include<stdio.h>
#define max 300000

int a[max];
int main(){
	a[0]=1;
	int n=100000,i,j,t,carry;
	//scanf("%d",&n);
	for(i=2;i<=n;i++){
		t=0;
		for(j=0;j<max;j++){
			carry=a[j]*i+t;
			a[j]=carry%10;
			t=carry/10;
		}
	}
	i=max;
	while(!a[--i]) ;
	printf("%d\n",i);
	for(j=i;j>=0;j--) printf("%d",a[j]);
	return 0;
}

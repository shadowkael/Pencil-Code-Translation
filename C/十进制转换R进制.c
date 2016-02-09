#include<stdio.h>
#include<stdlib.h>

int main(){
	int x,r,xx[10],i,j;
	for (i=0;i<10;i++){
		xx[i]=0;
	}
	printf("十进制转换为R进制....\n");
	printf("输入十进制数：");
	scanf("%d",&x);
	printf("输入R：");
	scanf("%d",&r);
	for(i=0;x!=0;i++){
		xx[i]=x%r;
		x/=r;
	}
	for (j=sizeof(xx)/sizeof(int)-1;j>=0;j--)
		if (xx[j]>=10)
			printf("%c",xx[j]+'A'-10);
		else
			printf("%d",xx[j]);
	system("pause");
	return 0;
}

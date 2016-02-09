#include <stdio.h>

void Select(int *a,int size){
	int t,i,j,k;
	for (i=0;i<size-1;i++)
	{
		printf("%d:",i+1);
		for (j=i+1;j<size;j++)
		{
			if (a[j]>a[i])
			{
				t=a[j];
				a[j]=a[i];
				a[i]=t;
			}
		}
		for (k=0;k<size;k++)
		{
			printf("%d ",a[k]);
		}
		putchar('\n');
	}
}

int main()
{
	int array[10],i;
	printf("输入要排序的数组(以空格隔开,仅限10个数)：\n");
	for (i=0;i<sizeof(array)/4;i++)
	{
		scanf("%d",&array[i]);
	}
	Select(array,sizeof(array)/4);
	return 0;
}


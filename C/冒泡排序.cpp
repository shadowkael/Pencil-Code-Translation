#include <iostream>
#include <time.h>
using namespace std;

void Bubble(int *n,int size){
	int t,x;
	for (int j=1;j<size;j++)
	{
		x=0;
		cout<<j<<":";
		for (int i=0;i<size-1;i++)
		{
			if (n[i]>n[i+1])
			{
				t=n[i];
				n[i]=n[i+1];
				n[i+1]=t;
				x++;
			}
			cout<<n[i]<<" ";
		}
		cout<<n[size-1]<<endl;
		if (x==0)
			break;
	}
	cout<<endl;
}

int main()
{
	int array[10],n;
	cout<<"输入要排序的数组(以空格隔开,仅限10个数)：";
	cout<<endl;
	for (int i=0;i<sizeof(array)/4;i++)
	{
		cin>>array[i];
	}
	Bubble(array,sizeof(array)/4);
	system("pause");
	return 0;
}

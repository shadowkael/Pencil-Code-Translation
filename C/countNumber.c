#include<stdio.h>

int main(){
    int i=0,j,k,max=0,x;
    int num[50]={0},a[50];
    while(scanf("%d",&a[i++])) ++num[i-1];
    for(j=1;j<i;j++){
        for(k=0;k<j;k++){
            if(a[j]==a[k]){
                ++num[k];break;
            }
        }
    }
    for(j=0;j<50;j++){
        if(num[j] && num[j]>max){max=num[j];x=a[j];}
    }
    printf("\n%d %d",max,x);
    return 0;
}


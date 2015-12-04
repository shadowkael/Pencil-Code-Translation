#include<stdio.h>
#include<ctype.h>//toupper(),isalpha()
#include<string.h>//strlen()

int main(){
    char s[100],p[100];
    int temp[100]={0};
    int i,j,n,m=0,max=0,start=0,end=0;
    fgets(s,sizeof(s),stdin);
    n=strlen(s);
    for(i=0;i<n;i++){
        if(isalpha(s[i])){
            p[m]=toupper(s[i]);
            temp[m++]=i;
        }
    }
    for(i=1;i<m;i++){
        for(j=1;j<=i;j++){
            if(p[i-j]!=p[i+j]) break;
            if(j*2+1>max){
                printf("%d %d %d %d\n",j,max=j*2+1,start=temp[i-j],end=temp[i+j]);
            }
        }
        for(j=1;j<=i;j++){
            if(p[i-j]!=p[i+j+1]) break;
            if(j*2+1>max){
                printf("%d %d %d %d\n",j,max=j*2+1,start=temp[i-j],end=temp[i+j+1]);
            }
        }
    }
    if(max){
        for(i=start;i<=end;i++) printf("%c",s[i]);
    }else
        printf("No string...\n");
    return 0;
}

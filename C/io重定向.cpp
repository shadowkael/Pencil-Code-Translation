//1
#include<iostream>
#include<cstdio>
using namespace std;

int main(){
    freopen("input.dat","r",stdin);
    freopen("output.dat","w",stdout);
    int n,max,min,s=0,count=0;
    cin>>n;
    max=min=n;
    for(;;){
        if(cin>>n==0) break;
        s+=n;count++;
        if(max<n) max=n;
        if(min>n) min=n;
    }
    float average=s/count;
    cout<<max<<" "<<min<<" "<<average<<endl;
}

//2
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

ifstream fin("input.dat");
ofstream fout("output.dat");
int main(){
    double i;
    cin>>i;
    fout<<fixed<<setprecision(4)<<i<<endl;
    return 0;
}

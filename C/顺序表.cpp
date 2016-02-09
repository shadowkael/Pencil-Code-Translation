#include <iostream>
using namespace std;

const int MAX=10;

class student{
public:
	int key;
	char name[20];
	int age;
};

class SLtype{
public:
	student List[MAX+1];
	int listlen;
};

void SLinit(SLtype *sl){sl->listlen=0;}

int SLlen(SLtype *sl){return sl->listlen;}

int SLinsert(SLtype *sl,student data,int n){
	if (sl->listlen>=MAX){
		cout<<"表已满！"<<endl;
		return 0;
	}
	if (n<1||n>100){
		cout<<"Insert Error!"<<endl;
		return 0;
	}
	for (int j=sl->listlen;j>=n;j--){
		sl->List[j+1]=sl->List[j];
	}
	sl->List[n]=data;
	sl->listlen++;
	return n;
}

int SLadd(SLtype *sl,student data){
	if (sl->listlen>=MAX){
		cout<<"表已满！"<<endl;
		return 0;
	}
	sl->List[++sl->listlen]=data;
	return sl->listlen;
}

int SLdelete(SLtype *sl,int n){
	if (n>sl->listlen||n<1){
		cout<<"Delete Error!"<<endl;
		return 0;
	}
	for (int i=n;i<=sl->listlen-1;i++){
		sl->List[n]=sl->List[n+1];
	}
	sl->listlen--;
	return n;
}

student *SLfind(SLtype *sl,int n){
	if (n>sl->listlen||n<1){
		cout<<"Find Error!"<<endl;
		return 0;
	}
	return &(sl->List[n]);
}

int SLall(SLtype *sl){
	for (int i=1;i<=sl->listlen;i++){
		cout<<sl->List[i].key<<endl
			<<sl->List[i].name<<endl
			<<sl->List[i].age<<endl;
	}
}
int main(){
	system("pause");
	return 0;
}

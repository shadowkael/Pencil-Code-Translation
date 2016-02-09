#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
using namespace std;

enum dir{sup,sdown,sleft,sright};
//围墙
class Fence
{
public:
	void lnitFence();
	void OutputF();
public:
	char game[20][20];
}f;
//画框框
void Fence::lnitFence()
{
	for(int i=0;i<20;i++)
		for(int j=0;j<20;j++)
		{
			if(i==0||i==19||j==0||j==19)
				game[i][j]=4;
			else game[i][j]=' ';
		}
}
//显示框框
void Fence::OutputF()
{
	for (int i=0;i<20;i++)
	{
		for (int j=0;j<20;j++)
			cout<<game[i][j]<<' ';
		cout<<endl;
	}
}
//蛇结点
class SnakeNobe
{
public:
	void add_head(int x,int y);
	int get_x();
	int get_y();
	void delete_tail();
private:
	int x,y;
	SnakeNobe *prior,*next;
}*head=NULL,*tail=NULL;
//插入头结点
void SnakeNobe::add_head(int x,int y)
{
	SnakeNobe *q=new SnakeNobe;
	q->x=x;q->y=y;
	q->next=head;
	q->prior=NULL;
	if(head) head->prior=q;
	head=q;
	if(!tail) tail=head;
	f.game[x][y]=1;
}
int SnakeNobe::get_x()
{
	return x;
}
int SnakeNobe::get_y()
{
	return y;
}
//删除尾结点
void SnakeNobe::delete_tail()
{
	SnakeNobe *p=tail;
	f.game[tail->get_x()][tail->get_y()]=' ';
	if(tail==head)
		tail=head=NULL;
	else
	{
		tail=tail->prior;
		tail->next=NULL;
	}
	delete p;
}
//移动
class smove
{
public:
	dir point;//控制方向
	int food_x;
	int food_y;
public:
	void moving();
	void change_point(char);//改变方向
	void get_food();
};
void smove::moving()
{
	int a,b;
	a=head->get_x();//头结点横左标
	b=head->get_y();//头结点纵坐标
	switch(point)
	{
	case sup:--a;break;
	case sdown:++a;break;
	case sleft:--b;break;
	case sright:++b;break;
	}
	if(a==19||b==19||a==0||b==0)
	{
		//判断是否撞墙
		cout<<"Game over!"<<endl;
		exit(0);
	}
	if(a==food_x && b==food_y)
	{
		//吃food
		head->add_head(a,b);
		get_food();
	}
	else
	{
		head->add_head(a,b);//插入头结点
		head->delete_tail();//删除尾结点
	}
}
void smove::change_point(char keydown)
{
	switch(keydown)
	{
	case 'w':point=sup;break;
	case 's':point=sdown;break;
	case 'a':point=sleft;break;
	case 'd':point=sright;break;
	}
}
void smove::get_food()
{
	srand((unsigned int) time(NULL));//程序运行时间
	food_x=rand()%18+1;
	food_y=rand()%18+1;
	f.game[food_x][food_y]=2;
}
//主函数
int main()
{
	cout<<"Using 'w,s,a,d' to move snake!\n\n\n";
	//画框框和蛇
	smove m;
	f.lnitFence();
	head->add_head(4,3);
	head->add_head(4,4);
	head->add_head(4,5);
	m.get_food();
	f.OutputF();
	while (true)
	{
		char keydown=getch();
		m.change_point(keydown);
		while (!kbhit())
		{//判断有无按键落下
			//system("cls");//清屏幕
			m.moving();
			f.OutputF();
			Sleep(150);
		}
	}
	return 0;
}

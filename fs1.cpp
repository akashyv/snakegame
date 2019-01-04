#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
using namespace std;
struct fruit{
	int x,y;
	char value;
}f;
struct snake{
	int x,y;
	char value;
	struct snake *next;
}s;
struct snake *start=NULL,*tail=NULL;
void snakes(int i, int j)
{
	struct snake *n;
	n=new snake;
    n->x=i;
    n->y=j;
    if(start==NULL)
    {

        n->value='X';
        n->next=NULL;
        start=n;
        tail=n;
    }
    else
    {
        n->value='#';
        n->next=NULL;
        tail->next=n;
		tail=n;
    }	
}
void savegame()
{
 FILE *fp,*fp1;
    fp=fopen("snake.txt","w");
    fp1=fopen("food.txt","w");

    struct snake *ptr=start;
    while(ptr!=NULL)
    {
        putc(ptr->x+'0',fp);
        putc(ptr->y+'0',fp);
	    putc('\n',fp);
        ptr=ptr->next;
    }
    putc(f.x+'0',fp1);
    putc(f.y+'0',fp1);
	fclose(fp);
	fclose(fp1);
}
void resumegame()
{
    FILE *fp,*fp1;
	fp=fopen("snake.txt","r");
	fp1=fopen("food.txt","r");
	char ch;
	int a,b;
	ch=getc(fp);
	while(ch!=EOF)
    {
        if(ch!='\n')
        {
    	a=ch-'0';
   		ch=getc(fp);
   		b=ch-'0';
    	snakes(a,b);
        }
        ch=getc(fp);
    }
    char ch1;
	ch1=getc(fp1);
	while(ch1!=EOF)
	{
		f.x=ch1-'0';
   		ch1=getc(fp1);
   		f.y=ch1-'0';
   		ch1=getc(fp1);
}
tail->value='Y';
fclose(fp);
fclose(fp1);
}
void screate(){
	int r=5,c=5,z=3;
	while(z--)
	{
		snakes(r,c);
		r++;
	}
	tail->value='I';
}
void change(){
	struct snake *ptr,*nptr;
	int a,b,c,d;
	ptr=start;
	nptr=start->next;
	while(nptr!=NULL)
	{
		if(ptr==start)
		{
			a=nptr->x;
			b=nptr->y;
			nptr->x=ptr->x;
			nptr->y=ptr->y;
			nptr=nptr->next;
			ptr=ptr->next;
		}
		else{
			c=nptr->x;
			d=nptr->y;
			nptr->x=a;
			nptr->y=b;
			a=c;
			b=d;
			nptr=nptr->next;
		}
		
	}
}
int food(char a[][10]){
    static int fx=12,fy=13;
	struct snake *ptr;
	static int score=0;
    ptr=start;
    f.x=fx;
    f.y=fy;
    if(start->x==f.x && start->y==f.y){
    	tail->value='#';
		int sx,sy;
		sx=tail->x;
		sy=tail->y;
		snakes(sx,sy);
		tail->value='I';
		f.x=rand()%(10-3)+1;
		f.y=rand()%(10-3)+1;
		fx=f.x;
		fy=f.y;
		++score;
	}
	if(f.x>8 || f.x<1){
		f.x=rand()%(10-3)+1;
		fx=f.x;
	}
	if(f.y>8 || f.y<1){
		f.y=rand()%(10-3)+1;
		fy=f.y;
	}
	while(ptr!=NULL)
	{
		if(ptr->x==f.x && ptr->y==f.y)
		{	
			f.x=rand()%(10-3)+1;
			f.y=rand()%(10-3)+1;
			fx=f.x;
			fy=f.y;
			ptr=start;
		}
		ptr=ptr->next;		
	}
	a[f.x][f.y]='O';
	return score;
}
int field(char  a[][10])
{
	struct snake *ptr,*ptr1;
	ptr=start;
	int score;
	for(int i=0;i<10;i++)
	for(int j=0;j<10;j++)
	a[i][j]=' ';
	score=food(a);
	for(int i=0;i<10;i++)
	{
		a[0][i]='*';
		a[i][0]='*';
		a[9][i]='*';
		a[i][9]='*';
	}
	while(ptr!=NULL)
	{
		a[ptr->x][ptr->y]=ptr->value;
		ptr=ptr->next;
	}	
	return score;
}
int check(){
	struct snake *ptr,*ptr1;
	int flag=0;
	ptr=start->next;
	while(ptr!=NULL){
	if(start->x==ptr->x && start->y==ptr->y)
	{
		flag=1;
		break;
	}
	ptr=ptr->next;
	}
	if(flag==1)
		return 1;
	else
		return 0;	
}
void print(char a[][10]){
	system("CLS");
	for(int i=0;i<10;i++)
   	{
    	for(int j=0;j<10;j++)
       	{
       		cout<<a[i][j];
           	cout<<' ';
       	}
       	cout<<endl;
   	}
}
int move(char c, char a[][10])
{
	int flag=0,score;
	if(c=='w'){
		if(start->x==1){
			change();
			start->x=8;
			score=field(a);
		}
		else{
			change();
			start->x=start->x-1;
			score=field(a);	
		}
	}
	else if(c=='s'){
		if(start->x==8)
		{
			change();
			start->x=1;
			score==field(a);
		}
		else{
			change();
			start->x=start->x+1;
			score=field(a);
		}
	}
	else if(c=='d'){
		if(start->y==8){
			change();
			start->y=1;
			score=field(a);
		}
		else{
			change();
			start->y=start->y+1;
			score=field(a);	
		}
	}
	else if(c=='a'){
		if(start->y==1){
			change();
			start->y=8;
			score=field(a);
		}
		else{
			change();
			start->y=start->y-1;
			score=field(a);
		}
	}
	flag=check();
	if(flag==1){
		cout<<"\nSCORE : "<<score<<"\nGAME OVER\n";
		return 1;
	}
	print(a);
	return 0;
}
int main() {
	char a[10][10]={' '},c;
	int flag=0,res;
	cout<<"Do you want to resume your game?\n";
	cin>>res;
	if(res==1)
	{
		resumegame();
	}
	else{
		screate();
		food(a);
	}
	field(a);
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			cout<<a[i][j];
			cout<<" ";
		}
		cout<<endl;
	}
	cout<<"ENTER Q TO STOP OR W,A,S or D TO MOVE \n";
	cin>>c;
	do{
		flag=move(c,a);
		if(flag==1)
			break;
		cin>>c;
		if(c=='q')
		{	
			cout<<"Do you want to save your progress??\n";
			cin>>res;
			if(res==1)
				savegame();
			else{
				
			}
		}
	}while(c!='q');
	cout<<"****OVER****";
	return 0;

}

/*				 SNAKES

NOTES:
1. Spamming of keys causes lag in output
2. Place the SCORE.dat file attached in the BIN folder of the TC directory

										*/
#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <fstream.h>
#include <string.h>
int gd= DETECT, gm;
int i,j;
struct score
{
 int rank;
 char name[20];
 int pts;
 }a;
class snake
{
 int l,ft;
 int s[100][2];int d[100];
 int board[50][50];
 int st,fst,pt,diff;
 public:
 snake();
 void disp();
 void move();
 void gen();
 void clean();
};
void snake::clean()
{
 setcolor(0);
 setfillstyle(0,0);
 for(i=0;i<l;++i)
 {
  fillellipse((s[i][1]*20),(s[i][0]*20),15,15);
  }
 setcolor(3);
 rectangle(98,getmaxy()-40,200,getmaxy());
 rectangle(332,getmaxy()-40,380,getmaxy());
 setcolor(0);
 setfillstyle(0,0);
 floodfill(99,getmaxy()-38,3);
 floodfill(333,getmaxy()-38,3);
 setcolor(0);
 rectangle(98,getmaxy()-40,200,getmaxy());
 rectangle(332,getmaxy()-40,380,getmaxy());
}
snake::snake()
{
  l=3; fst=1;st=1; pt=0; diff=200;
  for(i=0;i<20;++i)
  {
   if(i<l)
   {
    d[i]=3;
    s[i][0]=10;s[i][1]=10-i;
    }
   for(j=0;j<30;++j)
	   {
    if(i==0||j==0||j==29||i==19)
    {
     board[i][j]=1;
     }
   else
    board[i][j]=2;
    }
   }
  }

void snake::disp()
{
 int h1=0,h2=0; char P[10];
 int c=0,f=1,top=0,count=0;
 setcolor(GREEN);
 settextstyle(1,0,5);
 outtextxy(240,390,"SNAKE");
 setcolor(YELLOW);
 settextstyle(1,0,3);
 outtextxy(10,440,"POINTS:");
 itoa(pt,P,10);
 setcolor(WHITE);
 outtextxy(100,440,P);
 itoa(l,P,10);
 outtextxy(335,440,P);
 setcolor(YELLOW);
 settextstyle(1,0,3);
 outtextxy(240,440,"LENGTH:");
 outtextxy(400,440,"EXIT(X)  PAUSE(P)");
 for(i=0;i<20;++i)
  {
   for(j=0;j<30;++j)
   {
    if(c<l)
    {
     for(int x=0;x<l;++x)
     {
      if(i==s[x][0]&&j==s[x][1])
      {
       if(x==0)
	board[i][j]-=1;
       else if(s[x][0]==s[0][0]&&s[x][1]==s[0][1])
       {
	board[i][j]=1;
	st=0;
       }
       else
	board[i][j]=1;
       c++;
      }
     }
    }
    if(board[i][j]==3)
    {
      if(ft==0)
      {
       setcolor(RED);
       setfillstyle(9,RED);
       fillellipse(j*20,i*20,10,10);
       setfillstyle(9,GREEN);
       setcolor(RED);
       fillellipse(j*20,i*20-10,2,5);
     }
     else
     {
      setcolor(YELLOW);
      setfillstyle(9,YELLOW);
      fillellipse(j*20,i*20,10,12);
      setfillstyle(9,GREEN);
      setcolor(YELLOW);
      fillellipse(j*20,i*20-10,2,5);
     }
     f=0;
    }
    else if(board[i][j]==1)
    {
     if(i==0||i==19||j==0||j==29)
     {
      setcolor(1);
      rectangle(j*20,top,(j*20)+20,top+20);
      rectangle(j*20+2,top+2,(j*20)+18,top+18);
     }
     else
     {
      if(i==s[0][0]&&j==s[0][1])
      {
       if(d[0]<3)
	h2=5;
       else
	h1=5;
      }
      if(count%2==0)
      {
       setfillstyle(9,GREEN);
       setcolor(GREEN);
      }
      else
      {
       setfillstyle(9,10);
       setcolor(GREEN);
      }
      fillellipse((j*20),(i*20),10+h1,10+h2);
      if(i==s[0][0]&&j==s[0][1])
      {
       setcolor(RED);
       setfillstyle(1,RED);
       fillellipse((j*20)+3,(i*20)-2,2,2);
      }
      count++;
      h1=0;
      h2=0;
     }
    }
    else if(board[i][j]==0)
    {
     setcolor(RED);
     rectangle(j*20,top,(j*20)+20,top+20);
     rectangle(j*20+2,top+2,(j*20)+18,top+18);
     st=0;
    }
    }
    top+=20;
  }
  if(f==1)
  {
   fst=0;
  }
 }
void high_score(score a)
{
 cleardevice();
 setcolor(BLUE);
 setfillstyle(5,1);
 bar3d(0, 10, getmaxx()-20, 30, 10, 1);
 bar3d(0,10,20,getmaxy()-20,10,1);
 bar3d(0,getmaxy()-40,getmaxx()-20,getmaxy()-20,10,1);
 bar3d(getmaxx()-40,10,getmaxx()-20,getmaxy()-20,10,1);
 settextstyle(1,0,7);
 setcolor(YELLOW);
 outtextxy(120,50,"HIGH SCORE");
 settextstyle(1,0,3);
 outtextxy(50,200,"ENTER NAME:");
 char str[20];
 setcolor(WHITE);
 for(int i=0;i<19;++i)
 {

  str[i]=getch();
  str[i+1]='\0';
  outtextxy(210,200,str);
  if(str[i]=='\r')
  {
   str[i]='\0';
   break;
  }
 }
 strcpy(a.name,str);
 fstream f("SCORE.dat",ios::binary|ios::in|ios::out|ios::nocreate);
 fstream f1("TEMP.dat",ios::binary|ios::in|ios::out);
 score s;int change=0;
 while(f.read((char*) &s, sizeof(s)))
 {
  if(change==1)
   s.rank++;
  if(a.pts>s.pts&&change==0)
  {
   a.rank=s.rank;
   change=1;
   s.rank++;
   f1.write((char*) &a, sizeof(a));
  }
  if(s.rank<=10)
   f1.write((char*) &s, sizeof(s));
 }
  f.close();
 f1.close();
 remove("SCORE.dat");
 rename("TEMP.dat","SCORE.dat");
}

void snake::move()
{
  cleardevice();
  int max;

  while(st)
  {
   delay(diff);
   pause:
   clean();
   char c='l';
   for(i=l-1;i>0;--i)
   {
    d[i]=d[i-1];
   }
   if (fst==0)
   {
    gen();
    fst=1;
    l++;
    pt+=((l/3*diff)/100);
    d[l-1]=d[l-2];
    if(l%5==0&&diff>100)
     diff-=10;
    }
   if(kbhit())
    c=getch();
   switch(c)
   {
    case'w': if(d[1]!=2)
	      d[0]=1;
	     break;
    case's': if(d[1]!=1)
	      d[0]=2;
	     break;
    case'd':if(d[1]!=4)
	     d[0]=3;
	    break;
    case'a':if(d[1]!=3)
	     d[0]=4;
	    break;
    case'p':settextstyle(1,0,7);
	    setcolor(WHITE);
	    outtextxy(getmaxx()/2-130,getmaxy()/2-120,"PAUSED");
	    settextstyle(1,0,3);
	    outtextxy(getmaxx()/2-170,getmaxy()/2-50,"Press any key to continue");
	    getch();
	    cleardevice();
	    goto pause;
    case'x':setcolor(WHITE);
	    settextstyle(1,0,3);
	    outtextxy(getmaxx()/2-200,getmaxy()/2-90,"Confirm Exit by pressing a key");
	    getch();
	    cleardevice();
	    closegraph();
	    exit(0);
   }
   board[s[l-1][0]][s[l-1][1]]=2;

   for(i=l-1;i>0;--i)
   {
    s[i][0]=s[i-1][0];
    s[i][1]=s[i-1][1];
    }
   if(d[0]==1)
    --s[0][0];
   else if(d[0]==2)
    ++s[0][0];
   else if(d[0]==3)
    ++s[0][1];
   else if(d[0]==4)
    --s[0][1];

   disp();
  }
  cout<<"\n";
  if(st==0)
  {
   int high=0;
   settextstyle(1,0,7);
   setcolor(GREEN);
   outtextxy(getmaxx()/2-190,getmaxy()/2-90,"GAME OVER");
   settextstyle(1,0,3);
   outtextxy(getmaxx()/2-170,getmaxy()/2+20,"Press any key to continue");
   ifstream f("SCORE.dat",ios::binary);
   f.seekg(4*sizeof(a));
   f.read((char*)&a,sizeof(a));
   if(a.pts<pt)
   {
    a.pts=pt;
    outtextxy(getmaxx()/2-120,getmaxy()/2-20,"NEW HIGH SCORE");
    high=1;
   }
    getch();
    if(high==1)
     high_score(a);
    f.close();
  }
}
void snake::gen()
{
 srand(time(NULL));
 re:
 i=random(19)+1;
 j=random(29)+1;
 ft=random(2);
 if(board[i][j]==1)
  goto re;
 else
  board[i][j]=3;
}
void front()
{
 setcolor(10);
 settextstyle(1,0,10);
 outtextxy(100,50,"SNAKES");
 setcolor(1);
 setfillstyle(5,1);
 bar3d(0, 10, getmaxx()-20, 30, 10, 1);
 bar3d(0,10,20,getmaxy()-20,10,1);
 bar3d(0,getmaxy()-40,getmaxx()-20,getmaxy()-20,10,1);
 bar3d(getmaxx()-40,10,getmaxx()-20,getmaxy()-20,10,1);
 setcolor(YELLOW);
 settextstyle(1,0,4);
 outtextxy(getmaxx()/2-65,getmaxy()/2,"START");
 outtextxy(getmaxx()/2-60,getmaxy()/2+50,"HELP");
 outtextxy(getmaxx()/2-120,getmaxy()/2+100,"HIGH SCORES");
 outtextxy(getmaxx()/2-60,getmaxy()/2+150,"EXIT");
 setcolor(WHITE);
}
void help()
{
 settextstyle(1,0,7);
 setcolor(1);
 setfillstyle(5,1);
 bar3d(0, 10, getmaxx()-20, 30, 10, 1);
 bar3d(0,10,20,getmaxy()-20,10,1);
 bar3d(0,getmaxy()-40,getmaxx()-20,getmaxy()-20,10,1);
 bar3d(getmaxx()-40,10,getmaxx()-20,getmaxy()-20,10,1);
 setcolor(10);
 outtextxy(230,50,"HELP");
 setcolor(WHITE);
 settextstyle(1,0,2);
 outtextxy(100,150,"Use the keys W,A,S,D to move the snake");
 rectangle(280,190,310,220);
 rectangle(245,225,275,255);
 rectangle(280,225,310,255);
 rectangle(315,225,345,255);
 outtextxy(275,192," W");
 outtextxy(245,225," A  S  D");
 outtextxy(100,280,"Eat the orbs to gain length and increase");
 outtextxy(100,300,"your points");
 outtextxy(100,320,"Hitting walls or eating yourself will end");
 outtextxy(100,340,"the game. The difficulty scales with your");
 outtextxy(100,360,"length.");
 setcolor(YELLOW);
 outtextxy(120,390,"Press any key to return to menu.");
}
void high_print()
{
 cleardevice();
 char s[20];int top=0;
 setcolor(BLUE);
 bar3d(0, 10, getmaxx()-20, 30, 10, 1);
 bar3d(0,10,20,getmaxy()-20,10,1);
 bar3d(0,getmaxy()-40,getmaxx()-20,getmaxy()-20,10,1);
 bar3d(getmaxx()-40,10,getmaxx()-20,getmaxy()-20,10,1);
 settextstyle(1,0,7);
 setcolor(10);
 outtextxy(120,50,"HIGH SCORES");
 ifstream f("SCORE.dat",ios::binary);
 setcolor(YELLOW);
 settextstyle(1,0,2);
 outtextxy(50,120,"RANK        NAME                 PTS");
 setcolor(WHITE);
 while(f.read((char*)&a,sizeof(a)))
 {
  if(a.rank<6)
  {
   itoa(a.rank,s,10);
   outtextxy(50,150+top,s);
   itoa(a.pts,s,10);
   outtextxy(140,150+top,a.name);
   outtextxy(400,150+top,s);
   top+=20;
  }
 }
 setcolor(YELLOW);
 outtextxy(120,getmaxy()-150,"Enter any key to return to menu");
 f.close();
}
void menuchoose()
{
 int flag=1,top=230,bot=285;char c;
 while(flag)
 {
  setcolor(WHITE);
  front();
  rectangle(190,top,410,bot);
  rectangle(192,top+2,408,bot-2);
  if(kbhit())
  {
   c=getch();
   setcolor(BLACK);
   rectangle(190,top,410,bot);
   rectangle(192,top+2,408,bot-2);
   }
  switch(c)
  {
   case 'w': if(top>=270)
	     {
	      top-=50;
	      bot-=50;
	      }
	     c='\0';
	     break;
   case 's':if(top<=350)
	     {
	      top+=50;
	      bot+=50;
	     }
	     c='\0';
	     break;
   case '\r':cleardevice();
	     switch(top)
	     {
	      case 230:clrscr();
		       snake s;
		       s.gen();
		       s.disp();
		       getch();
		       s.move();
		       break;
	      case 280:help();
		       getch();
		       break;
	      case 330:high_print();
		       getch();
		       break;
	      case 380:delay(300);
		       exit(0);break;
	      }
	     cleardevice();
	     c='\0';
	     break;
   }
   }
}

void main()
{

 accept:
 clrscr();
 initgraph(&gd,&gm,"C:\\TC\\BIN");
 cleardevice();
 menuchoose();
 getch();
 goto accept;
}


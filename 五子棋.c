#include<stdio.h>
#include<windows.h>
#define up 'w'
#define left 'a'
#define down 's'
#define right 'd'
#define locate 'p'
#define cls 'q'

struct stu
{
        int x;
        int y;
}location;

int player = 1;
int Q[20][20]={0};

void gotoxy(int x, int y)//系统函数，获取位置 //建立坐标函数
{
    COORD c;
    c.X=2*x;
    c.Y=y;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c); //修改当前光标的位置
}

void draw()
{
        int i,j;
        system("cls");
        for(i=0;i<20;i++)
        {
            for(j=0;j<20;j++)
            {
                    Q[i][j]=0;
                    printf("十");
            }
            printf("\n");
        }
        location.x=0;
        location.y=0;
        gotoxy(0,0);
}

void record()//谁落子
{
      Q[location.x][location.y]=player+1;
      if(player)
       {
        player=0;  //玩家变换
        return;
       }
      player=1;
}

void droppiece()
{
        if(Q[location.x][location.y]==0)
        {
              if(player)
        {
            record();
            printf("●");
        }
        else
        {
            record();
            printf("○");
        }
        gotoxy(location.x,location.y);
        }
}

int check_if_win()
{
        int p;
    int r,c,rr,cc,count=0;
    p=player==0?2:1;
    for(c=0;c<20;c++)
    {
        for(r=0;r<20;r++)
        {
            if(Q[r][c]!=p)
                continue;
                        //检查列
            rr=r;cc=c;
            while(--cc>=0 &&Q[rr][cc]==p)count++;  cc=c;
            while(++cc<20 &&Q[rr][cc]==p)count++;  cc=c;
            if(count+1>=5)
                return p;
                        //检查行
            count=0;
            while(--rr>=0 &&Q[rr][cc]==p)count++;  rr=r;
            while(++rr<20 &&Q[rr][cc]==p)count++;  rr=r;
            if(count+1>=5)
                return p;
                        //检查反斜边
            count=0;
            cc--;rr--;
            while((cc>=0||rr>=0) &&Q[rr][cc]==p){count++;cc--;rr--;}  rr=r;cc=c;
            cc++;rr++;
            while((cc<20||rr<20) &&Q[rr][cc]==p){count++;cc++;rr++;}  rr=r;cc=c;
            if(count+1>=5)
                return p;
            count=0;
                        //检查正斜边
            count=0;
            cc++;rr--;
            while((cc<20||rr>=0) &&Q[rr][cc]==p){count++;cc++;rr--;}  rr=r;cc=c;
            cc--;rr++;
            while((cc>=0||rr<20) &&Q[rr][cc]==p){count++;cc--;rr++;}  rr=r;cc=c;
            if(count+1>=5)
                return p;
            count=0;
        }
    }
    return 0;
}

void Keypress(char n) //光标位置移动
{
    switch(n)
    {
    case up:
            if(location.y<=0)
                location.y=19;
            else location.y--;
            gotoxy(location.x,location.y);
            break;
        //向上移动光标
    case left:
            if(location.x<=0)
                location.x=19;
            else
                location.x--;
            gotoxy(location.x,location.y);
            break;
        //向左移动光标
    case right:
            if(location.x>=19)
                location.x=0;
            else location.x++;
            gotoxy(location.x,location.y);
            break;
        //向右移动光标
    case down:
            if(location.y>=19)
                location.y=0;
            else location.y++;
            gotoxy(location.x,location.y);
            break;
        //向下移动光标
    case locate:
            droppiece();
            break;
        //开始落子操作
    case cls:
            draw();
            break;
        //重新开始
    }
}

main()
{
    char press;
    int winer=0;
    system("color 3f");
l:  draw();
    press=getch();
    while(1)
    {
        Keypress(press);
        if(press=='p')
        winer=check_if_win();
        if(winer!=0)
            gotoxy(0,20);
        if(winer==2)
            printf("the side of ● wins\n");
        else if(winer==1)
            printf("the side of ○ wins\n");
        else
        {
            press=getch();
            continue;
        }
        printf("do you want to play again?(y/n):");
p:      press=getch();
        if(press=='n')
            break;
        else if(press=='y')
        {
            winer=0;
            goto l;
        }
        else
            goto p;
    }
}

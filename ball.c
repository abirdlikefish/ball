
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>

typedef struct node
{
    int x;
    int y;
}Node;


//修改了gotoxy函数,使其按照Node ball修改光标
void gotoxy(Node ball)
{
 COORD coord = {ball.x, ball.y}; 
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//另一种gotoxy函数实现
/*
void gotoxy(Node ball)
{
    //从(1,1)开始,坐标要+1
    printf("\033[%d;%dH",ball.y+1,ball.x+1);
}
*/


int main()
{
    //设置命令行大小
    system("mode con cols=60 lines=60");

    //清空屏幕
    system("cls");

    //隐藏光标
    fputs("\33[?25l",stdout);

    //更改终端颜色
    fputs("\033[30;103m",stdout);




    
    //输出地图
    for(int i=0;i<=50;i++)
    {
        for(int j=0;j<=50;j++)
        {
            if(i==0||j==0||i==50||j==50)
                fputs("#",stdout);
            else
                fputs(" ",stdout);
        }
        puts("");
    }


    //初始化小球
    Node ball={10,10};
    gotoxy(ball);
    fputs("O",stdout);


    //循环
    while(1)
    {
        if(_kbhit())
        {

            //擦除原先小球图案
            gotoxy(ball);
            fputs(" ",stdout);



            // 读取第一个输入并将输入缓存里的其他输入清空
            char op=_getch();
            while(_kbhit())
                _getch();
            

            //判断运动方向
            switch (op)
            {
            case 'w':
                if(ball.y-1>0) ball.y--;
                break;
            
            case 's':
                if(ball.y+1<50) ball.y++;
                break;
            
            case 'a':
                if(ball.x-1>0) ball.x--;
                break;
            
            case 'd':
                if(ball.x+1<50) ball.x++;
                break;


            
            default:
                break;
            }


            //打印小球新位置
            gotoxy(ball);
            fputs("O",stdout);
        }


        //睡一会防止小球运动过快
        //未清空输入缓存且睡太久的话小球会有"惯性"
        Sleep(10);
    }

    return 0;
}

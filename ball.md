# **自由移动的小球** (c语言版)

## 前置知识

1. gotoxy(int x,int y)
2. system(char*command)
3. int _kbhit(void)
4. char _getch(void)
5. char _getche(void)
6. ANSI
7. fflush()


### gotoxy(int x,int y)
包含在``conio.h``头文件中  
控制光标的函数,将光标移动到(x,y)处  

0--------------->x  
|  
|  
|  
|  
\\/  
y  

不过现在大部分集成开发环境都不包括这个函数,所以一般要自己重新写一个  

```c
//gotoxy 源代码
//需要 windows.h 头文件
//x,y从0开始
void  gotoxy( int  x,  int  y)  
{
COORD pos;
pos.X = x ;
pos.Y = y ;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
```


    system("mode con cols=200 lines=60");

### system(char*command)
包含在``stdlib.h``头文件中  
将一个字符串(指令)传入控制台中  
本程序所用命令:
- cls  
清空控制台
- mode con cols=x lines=y
控制控制台的行列数
- color xy
由两个16进制数改变控制台颜色
>0 = 黑色   8 = 灰色
1 = 蓝色   9 = 淡蓝色
2 = 绿色   A = 淡绿色
3 = 浅绿色 B = 淡浅绿色
4 = 红色    C = 淡红色
5 = 紫色    D = 淡紫色
6 = 黄色    E = 淡黄色
7 = 白色    F = 亮白色

### int _kbhit(void)
包含在``conio.h``头文件中  
检测缓冲区中是否有数据，如果有的话就返回非 0 值，没有的话就返回 0  
_kbhit() 不会读取数据，数据仍然留在缓冲区  

### char getch(void)
包含在``conio.h``头文件中  
不回显函数,输入不显示在控制台  
getch()函数用于从stdio流中读字符，即从控制台读取一个字符；语法为：“int getch(void)”，返回读取的字符。

### char getch(void)
是回显函数  
其他与与getch()相似  

### ANSI
转义字符

- puts("\033[0m")
恢复默认

- puts("\033[ x ; y ; z m")
更改命令行字体/背景颜色
>x  
0 终端默认设置（黑底白字）
1 高亮显示
4 使用下划线
5 闪烁
7 反白显示
8 不可见

>字色(y)           背景(z)          颜色
30                40              黑
31                41              红
32                42              绿
33                43              黄
34                44              蓝
35                45              紫
36                46              青蓝
37                47              白
x+60/y+60 -> 颜色变亮

- 光标控制
>\33[nA 光标上移n行 
\33[nB 光标下移n行 
\33[nC 光标右移n行 
\33[nD 光标左移n行 
\33[y;xH设置光标位置(从(1,1)开始)
\33[2J 清屏 
\33[K 清除从光标到行尾的内容 
\33[s 保存光标位置 
\33[u 恢复光标位置 
\33[?25l 隐藏光标 
\33[?25h 显示光标

### int fflush(FILE *stream)
包含在``stdio.h``头文件中
本来是想用``fflush(stdin)``清空输入缓存区的,但好像用不了


## 常见问题

- 小球有惯性/松开按键后小球继续运动
sleep()后未清空缓存区
- 小球越界
光标的零点(0,0)未取到命令行界面的左上点
更改命令行界面大小,重新启动命令行,单独运行该程序


## 代码
``` c

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

```
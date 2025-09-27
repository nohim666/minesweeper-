#include <stdio.h>
#include <windows.h>
#include <time.h>


#define ez_row 7
#define ez_line 7
#define med_row 12
#define med_line 12




//开地图
int developer[med_row][med_line];
int player[med_row][med_line];


//声明
void game_rule(void);
void loading(void);
void reset_mine (int row,int line);
void summon_player (int row,int line);
void set_mine (int count);
void set_med_mine(int count);
int count_mine (int x,int y);
void sweep_mine(int x,int y);
void show_mine (int row,int line);
int count_last(int row,int line);
void safe_mine (int row,int line);
void show_develop(int row,int line);
void auto_open(int x,int y);






void game_rule(void)     //选模式
{
    printf("--------welcome to the mineweeper--------\n");
    printf("1   easy \n");
    printf("2   medium\n");
    printf("please enter number to choose difficult\n");
    //printf("3   hard\n");
}

void loading(void)  //虚伪的加载动画
{
    printf("loading.\n");
    Sleep(1000);
    printf("loading..\n");
    Sleep(1000);
    printf("loading...\n");
    Sleep(1000);
    printf("loading....\n");
    Sleep(1000);
    printf("loading.....\n");
    Sleep(1000);

}

void reset_mine (int row,int line)    //重置雷区和玩家视角
{
    for(int i=0;i<=row;i++)
    {
        for(int j=0;j<=line;j++)
        {

            developer[i][j]= '0';
        }
    }
    for(int i=1;i<=row-2;i++)
    {
        for(int j=1;j<=line-2;j++)
        {
            player[i][j]= '*';
        }
    }

}

void summon_player (int row,int line) //这是玩家初始
{
    int i,j;

    printf(" 0 ");
    for(i=1;i<row-1;i++)    //横行0-10打印
    {
        printf("%d ",i);

    }
    printf("\n");
        for(j=1;j<row-1;j++)
        {
            printf("---");
        }
    printf("\n");
    for(j=1;j<line-1;j++)   //竖行1-10打印
    {
        printf("%2.d|",j);
        for(i=1;i<row-1;i++)
        {
            printf("%c ",player[i][j]);  //填充玩家视角
        }
        printf("\n");

    }
}


void set_mine (int count)    //放置雷
{
    int x = 0,y = 0;
    int COUNT = count;
    srand(time(NULL));
    while(COUNT)
    {

        x=rand()%5+1;
        y=rand()%5+1;
        if(developer[x][y]=='0')
        {
            developer[x][y]='1';
            COUNT--;
        }
    }

}
void set_med_mine (int count)    //放置雷
{
    int x = 0,y = 0;
    int COUNT = count;
    srand(time(NULL));
    while(COUNT)
    {

        x=rand()%10+1;
        y=rand()%10+1;
        if(developer[x][y]=='0')
        {
            developer[x][y]='1';
            COUNT--;
        }
    }

}



int count_mine (int x,int y)   //点击处四周雷的个数
{
    int count = 0;
    if(developer[x+1][y+1]=='1') //右下
    {
        count++;
    }
    if(developer[x][y+1]=='1') //下
    {
        count++;
    }
    if(developer[x-1][y+1]=='1') //左下
    {
        count++;
    }
    if(developer[x+1][y]=='1') //右
    {
        count++;
    }
    if(developer[x-1][y]=='1') //左
    {
        count++;
    }
    if(developer[x+1][y-1]=='1') //右上
    {
        count++;
    }
    if(developer[x][y-1]=='1') //上
    {
        count++;
    }
    if(developer[x-1][y-1]=='1')//左上
    {
        count++;
    }
    // int i,j,count;
    // for (i = x-1;i <= x+1;i++)
    // {
    //     for (j = y-1;j <= y+1;j++)
    //     {
    //         if (developer[i][j]== '1' )
    //         {
    //             count++;
    //         }
    //
    //     }
    // }

    return count;
}

void sweep_mine(int x,int y)
{
    if(developer[x+1][y+1]=='0' && count_mine(x+1,y+1) != 0)//右下
    {
        player[x+1][y+1]=count_mine(x+1,y+1) - 208;
    }
    else if(developer[x+1][y+1]=='0' && count_mine(x+1,y+1) == 0)
    {
        player[x+1][y+1]= '0';//此处无雷
       // sweep_mine((x+1),(y+1));
        auto_open((x+1),(y+1));
    }
    else
    {
        player[x+1][y+1]='*';//此处是雷
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(developer[x][y+1]=='0' && count_mine(x,y+1) != 0)//下
    {
        player[x][y+1]=count_mine(x,y+1) - 208;
    }
    else if(developer[x][y+1]=='0' && count_mine(x,y+1) == 0)
    {
        player[x][y+1]='0';//此处无雷
        //sweep_mine((x),(y+1));
        auto_open((x),(y+1));
    }
    else
    {
        player[x][y+1]= '*';//此处是雷

    }
//////////////////////////////////////////////////////////////////////////////////////////////////////
    if (developer[x-1][y+1]=='0' && count_mine(x-1,y+1) != 0)//左下
    {
        player[x-1][y+1]=count_mine(x-1,y+1) - 208;
    }
    else if(developer[x-1][y+1] == '0' && count_mine(x-1,y+1) == 0 )
    {
        player[x-1][y+1]='0';//此处无雷
        //sweep_mine((x-1),(y+1));
        auto_open((x-1),(y+1));
    }
    else
    {
        player[x-1][y+1]='*';//此处是雷

    }
////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (developer[x+1][y]=='0' && count_mine(x+1,y) != 0)//右
    {
        player[x+1][y]=count_mine(x+1,y) - 208;
    }
    else if(developer[x+1][y]=='0' && count_mine(x+1,y) == 0)
    {
        player[x+1][y]='0';//此处无雷
        //sweep_mine((x+1),(y));
        auto_open((x+1),(y));
    }
    else
    {
        player[x+1][y]='*';//此处是雷

    }
////////////////////////////////////////////////////////////////////////////////////////////////////////
   if(developer[x-1][y]=='0' && count_mine(x-1,y) != 0)//左
   {
       player[x-1][y]=count_mine(x-1,y) - 208;
   }
    else if(developer[x-1][y]=='0' && count_mine(x-1,y) == 0)
    {
        player[x-1][y]='0';//此处无雷
        //sweep_mine((x-1),(y));
        auto_open((x-1),(y));
    }
    else
    {
        player[x-1][y]='*';//此处是雷

    }
////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (developer[x+1][y-1]=='0' && count_mine(x+1,y-1) != 0)//右上
    {
        player[x+1][y-1]=count_mine(x+1,y-1) - 208;
    }
    else if(developer[x+1][y-1] == '0' && count_mine(x+1,y-1) == 0)
    {
        player[x+1][y-1]='0';//此处无雷
        //sweep_mine((x+1),(y-1));
        auto_open((x+1),(y-1));
    }
    else
    {
        player[x+1][y-1]='*';//此处是雷

    }
////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (developer[x][y-1]=='0' && count_mine(x,y-1) != 0)//上
    {
        player[x][y-1]=count_mine(x,y-1) - 208;
    }
    else if(developer[x][y-1]=='0' && count_mine(x,y-1) == 0)
    {
        player[x][y-1]='0';//此处无雷
        //sweep_mine((x),(y-1));
        auto_open((x),(y-1));
    }
    else
    {
        player[x][y-1]='*';//此处是雷

    }
////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (developer[x-1][y-1]=='0' && count_mine(x-1,y-1) != 0)//左上
    {
        player[x-1][y-1]=count_mine(x-1,y-1) - 208;
    }
    else if(developer[x-1][y-1]=='0' && count_mine(x-1,y-1) == 0)
    {
        player[x-1][y-1]='0';//此处无雷
        //sweep_mine((x-1),(y-1));
        auto_open((x-1),(y-1));
    }
    else
    {
        player[x-1][y-1]='*';//此处是雷

    }

}

void show_mine (int row,int line)
{
    int i,j;
    printf(" 0 ");
    for(i=1;i<row-1;i++)    //横行0-10打印
    {
        printf("%d ",i);

    }
    printf("\n");
        for(j=1;j<row-1;j++)
        {
            printf("---");
        }
    printf("\n");
    for(j=1;j<line-1;j++)   //竖行1-10打印
    {
        printf("%2.d|",j);
        for(i=1;i<row-1;i++)
        {
            printf("%c ",player[i][j]);  //填充玩家视角
        }
        printf("\n");
    }
}
void show_develop (int row,int line)
{
    int i,j;
    printf(" 0 ");
    for(i=1;i<row-1;i++)    //横行0-10打印
    {
        printf("%d ",i);
    }
    printf("\n");
    for(j=1;j<line-1;j++)   //竖行1-10打印
    {
        printf("%2.d ",j);
        for(i=1;i<row-1;i++)
        {
            printf("%c ",developer[i][j]);  //填充玩家视角
        }
        printf("\n");
    }
}

int count_last(int row,int line)
{
    int count = 0;
    for(int j=1;j<line;j++)
    {
        for(int i=1;i<row;i++)
        {
              if(player[i][j]=='*')
              {
                  count++;
              }
        }
    }
    return count;
}

void safe_mine (int row,int line)  //第一次不暴毙
{
    int x = 0,y = 0;
    int ret = 1;
    printf("please enter position:");
    while (1)
    {

        printf("\n");
        printf("x=");
        scanf("%d",&x);
        printf("y=");
        scanf("%d",&y);
        if(x >= 1 && x <= row-2 && y >= 1 && y <= line-2)//判断输入是否符合要求
        {
            if(developer[x][y]=='1')//第一次就踩雷
            {
                developer[x][y]='0';
                player[x][y] = count_mine(x,y) - 208;
                sweep_mine (x,y);
                while(ret)
                {
                    int x = rand()%10+1;
                    int y = rand()%10+1;
                    if(developer[x][y] == '0')
                    {
                        developer[x][y]='1';
                        ret = 0;
                        break;
                    }
                }
                summon_player(row,line);

                break;
            }
            if(developer[x][y]=='0')
            {
                player[x][y]=count_mine(x,y) - 208; //ascii码转化成数字的ascii   3-51   ╚-200
                sweep_mine(x,y);
               // auto_open(x,y);
                summon_player(row,line);
                break;
            }
        }
        else
        {
            printf("please enter position again:");
        }

    }

}

void auto_open(int x,int y)
{
    //player[x][y]=' ';
    int i,j,count;
    for (i = x-1;i <= x+1;i++)
    {
        for (j = y-1;j <= y+1;j++)
        {
            if(player[i][j]=='*' && developer[i][j]=='0')
            {
                count = count_mine( i, j);
                player[i][j] = count - 208;
                if (player[i][j]== '0' )
                {

                    auto_open((i),(j));
                }
            }

        }
    }


}

void game(int row,int line)
{
    int n = 1;
    while(n)
    {
        int x = 0,y = 0;
        printf("please enter position:");
        printf("\n");
        printf("x=");
        scanf("%d",&x);
        printf("y=");
        scanf("%d",&y);
        if(developer[x][y]=='1')
        {
            printf("you lose \n");
            printf("ansewer \n");
            show_mine(row,line);
            n=0;
        }
        else
        {
            //printf("count=%d\n",count_mine(x,y));
            player[x][y]=count_mine(x,y) - 208; //ascii码转化成数字的ascii   3-51   ╚-200
            sweep_mine(x,y);
            summon_player(row,line);
            n=1;
        }

        if(count_last(row,line) == 6) //简单模式6个胜利
        {
            printf("----------------------------------------------------\n\n");
            printf("you win\n");
            printf("----------------------------------------------------\n\n");
            break;
        }
    }
}



int main(void)
{
    int mode = 1;//初始化变量
    int n = 1;

    game_rule();                           //见面问候


    scanf("%d",&mode);               //模式选择
    if (mode == 1)
    {
        reset_mine(ez_row,ez_line);
        //loading();
        printf("    begin   \n");

        set_mine(6);
        show_mine(ez_row,ez_line);
                                            //扫雷部分
        safe_mine(ez_row,ez_line);

        printf("    developer   \n");            //测试语句用于看本次游戏的答案
        show_develop(ez_row,ez_line);
        printf("    test end \n");

        game(ez_row,ez_line);




    }
    else
    {
        reset_mine(med_row,med_line);
        //loading();
        printf("    begin   \n");
        summon_player(med_row,med_line);            //打印初始键盘
        set_med_mine(12);                           //下雷

        safe_mine(med_row,med_line);            //第一次不gg

        printf("    developer   \n");               //测试语句用于看本次游戏的答案
        show_develop(med_row,med_line);
        printf("    test end \n");
        game(med_row,med_line);
    }


    return 0;
}
/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            佛祖保佑       永无BUG
*/




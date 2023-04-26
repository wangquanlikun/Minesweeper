#include<stdio.h>
#define CONTINUE 1
#define BOOM 2
#define WIN 3

void getspace();//读入雷区与预处理数据模块
int opertion(int process, int xspace, int yspace);//处理对雷区操作模块
int output(int status, int steps, int remains);//输出操作结果模块
void gameover(int status);//游戏结束游戏输出处理模块
int adjustwin(int remains);//判断点开所有非雷格子胜利的模块

char space[24 + 1][30 + 1] = {'\0'}; //记录原始雷区数据
char numspace[24 + 1][30 + 1] = {'\0'}; //直接记录个位置雷与数字
char outputspace[24 + 1][30 + 1] = {'\0'};//记录输出的游戏数据
int N_space = 0, M_space = 0, C_space = 0; //行数 N，列数 M 和雷数 C

int main()
{
    int gamelevel;//初级、中级、高级、自定义
    
    scanf("%d", &gamelevel);
    if(gamelevel==4)
        scanf("%d%d%d", &N_space, &M_space, &C_space);
    //雷区大小不能超过 24 × 30
    if(N_space>24)
        N_space = 24;
    if(M_space>30)
        M_space = 30;
    getchar();//读取换行符'\n'

    //生成不同难度级别的游戏区域
    if(gamelevel==1){
        N_space = 9;
        M_space = 9;
        C_space = 10;}
    else if(gamelevel==2){
        N_space = 16;
        M_space = 16;
        C_space = 40;}
    else if(gamelevel==3){
        N_space = 16;
        M_space = 30;
        C_space = 99;}

    getspace();

    int process, xspace, yspace;//操作类型以及坐标xy
    scanf("%d%d%d", &process, &xspace, &yspace);
    int steps = 0, remains = C_space;//已经进行的操作次数，剩余地雷数量
    int operation_return;
    int status;
    while(1)
    {
        operation_return = opertion(process, xspace, yspace);
        steps += 1;
        if(operation_return>=-1)
        {
            remains -= operation_return;
            status = output(CONTINUE, steps, remains);
            if(status==3)
                break;
        }
        else if(operation_return==-2)//-2表示触雷
        {
            output(BOOM, steps, remains);
            break;
        }
        else if(operation_return==-3)//-3表示胜利
        {
            output(WIN, steps, remains);
            break;
        }
        if(feof(stdin))
            break;
        scanf("%d%d%d", &process, &xspace, &yspace);
    }
    return 0;
}

int output(int status, int steps, int remains)//status状态：1继续，2触雷，3胜利
{
    //如果玩家点开了所有没有雷的格子也判断胜利
    if(status==CONTINUE)
    {
        int c = adjustwin(remains);
        if(c==WIN)
            status = WIN;
    }

    if(status==CONTINUE)
        printf("Game in progress\n");
    else if(status==BOOM)
        printf("Hit mine, you lose\n");
    else if(status==WIN)
        printf("Game over, you win\n");

    printf("%d %d\n", steps, remains);

    gameover(status);

    int i1, i2;
    for (i1 = 1; i1 <= N_space;i1++)
    {
        for (i2 = 1; i2 <= M_space;i2++)
            printf("%c", outputspace[i1][i2]);
        printf("\n");
    }

    return status;
}

int adjustwin(int remains)//3 = win  //如果玩家点开了所有没有雷的格子也判断胜利
{
    int k1, k2;
    int not_open = 0;
    for (k1 = 1; k1 <= N_space;k1++)
    {
        for (k2 = 1; k2 <= M_space;k2++)
        {
            if(outputspace[k1][k2]=='.')
                not_open++;
        }
    }
    if(not_open==remains)
        return WIN;
    else
        return 0;
}

void gameover(int status)//胜利或失败之后需要在输出棋盘时，所有地雷所在位置输出"*"，其余位置输出当前操作后的棋盘状态
{
    int k1, k2;
    if(status==CONTINUE)
        return;
    else if(status==BOOM)
    {
        for (k1 = 1; k1 <= N_space;k1++)
        {
            for (k2 = 1; k2 <= M_space;k2++)
            {
                if(outputspace[k1][k2] == '.' && space[k1][k2] == '*')
                    outputspace[k1][k2] = '*';
                else if (outputspace[k1][k2] == '!' && space[k1][k2] == '*')
                    outputspace[k1][k2] = '*';
                else if(outputspace[k1][k2]=='!'&&space[k1][k2]!='*')
                    ;
            }
        }
        return;
    }
    else if(status==WIN)
    {
        for (k1 = 1; k1 <= N_space;k1++)
        {
            for (k2 = 1; k2 <= M_space;k2++)
            {
                if(outputspace[k1][k2]=='!')
                    outputspace[k1][k2] = '*';
                else if(outputspace[k1][k2]=='.'&&space[k1][k2]=='*')
                    outputspace[k1][k2] = '*';
            }
        }
        return;
    }
}

int opertion(int process, int xspace, int yspace)//函数返回值是减少的雷数量；-2表示触雷，-3表示胜利
{
    if(process==1)
    {
        if(xspace<0||yspace<0||xspace>24||yspace>30||space[xspace][yspace]=='\0')
            return 0;
        if(outputspace[xspace][yspace]!='.')
            return 0;

        if(numspace[xspace][yspace]=='0')
        {
            outputspace[xspace][yspace] = '0';
            int k1, k2;
            for (k1 = -1; k1 <= 1;k1++)
            {
                for (k2 = -1; k2 <= 1;k2++)
                {
                    if(k1!=0||k2!=0)
                        opertion(1, xspace + k1, yspace + k2);//递归打开方格
                }
            }
            return 0;
        }
        else if(numspace[xspace][yspace]=='*')
        {
            //所有地雷所在位置输出"*"
            int k1, k2;
            for (k1 = 1; k1 <= xspace;k1++)
            {
                for (k2 = 1; k2 <= yspace;k2++)
                {
                    if(space[k1][k2]=='*'&&outputspace[k1][k2]=='.')
                        outputspace[k1][k2] = '*';
                }
            }
            return -2;
        }
        else
        {
            outputspace[xspace][yspace] = numspace[xspace][yspace];
            return 0;
        }
    }
    else if(process==2)
    {
        if(outputspace[xspace][yspace]=='.'||outputspace[xspace][yspace]=='?')
            outputspace[xspace][yspace] = '!';
        return 1;
    }
    else if(process==3)
    {
        if(outputspace[xspace][yspace]=='!')
        {
            outputspace[xspace][yspace] = '?';
            return -1;
        }
        else if(outputspace[xspace][yspace]=='.')
        {
            outputspace[xspace][yspace] = '?';
            return 0;
        }
    }
    else if(process==4)
    {
        if(outputspace[xspace][yspace]=='!')
        {
            outputspace[xspace][yspace] = '.';
            return -1;
        }
        else if(outputspace[xspace][yspace]=='?')
        {
            outputspace[xspace][yspace] = '.';
            return 0;
        }
    }
    else if(process==9)
    {
        int minenow;
        int k1, k2;
        if(outputspace[xspace][yspace]!='!'&&outputspace[xspace][yspace]!='?')
        {
            for (k1 = -1; k1 <= 1;k1++)
            {
                for (k2 = -1; k2 <= 1;k2++)
                if(outputspace[xspace+k1][yspace+k2]=='!')
                        minenow += 1;
            }
        }//统计周围标记雷的数量

        if(minenow+'0'==numspace[xspace][yspace])
        {
            for (k1 = -1; k1 <= 1;k1++)
            {
                for (k2 = -1; k2 <= 1;k2++)
                {
                    if(outputspace[xspace+k1][yspace+k2]=='.'&&space[xspace+k1][yspace+k2]=='*')
                        return -2;
                }
            }
            for (k1 = -1; k1 <= 1;k1++)
            {
                for (k2 = -1; k2 <= 1;k2++)
                {
                    if(outputspace[xspace+k1][yspace+k2]=='.')
                        opertion(1, xspace + k1, yspace + k2);
                }
            }
            return 0;
        }
        else if(minenow+'0'!=numspace[xspace][yspace])
            return 0;
    }
}

void getspace()//读取扫雷区域，生成输出区域，同时生成含数量的区域
{
    int i1, i2;
    for (i1 = 1; i1 <= N_space;i1++)
    {
        for (i2 = 1; i2 <= M_space;i2++)
            scanf("%c", &space[i1][i2]);
        getchar();
    }

    int k1, k2;
    int minenum;
    for (i1 = 1; i1 <= N_space;i1++)
    {
        for (i2 = 1; i2 <= M_space;i2++)
        {
            if(space[i1][i2]=='*')
            {
                outputspace[i1][i2] = '.';
                numspace[i1][i2] = '*';
                //C_space += 1;
            }
            else if(space[i1][i2]=='.')
            {
                minenum = 0;
                for (k1 = -1; k1 <= 1;k1++)
                {
                    for (k2 = -1; k2 <= 1;k2++)
                    {
                        if((k1!=0||k2!=0)&&space[i1+k1][i2+k2]=='*')
                            minenum += 1;
                    }
                }
                numspace[i1][i2] = minenum + '0';
                outputspace[i1][i2] = '.';
            }
        }
    }
    return;
}
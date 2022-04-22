/*
スタックを用いたプログラム。
char 型の要素を持つ2 次元配列canvas[N][N] があるとする(N は1 以上の奇数)。canvas の中央の位置(
canvas[N/2][N/2] ) からはじめ、その上下左右にある空白文字を全て文字@ (アットマーク) に置き換える
プログラムを作成。また、作成するプログラムにおいては、N はマクロで定義され、11 であるものとし、
中央canvas[N/2][N/2] には空白があると仮定。

入力例
--------------------------------------------------------------------------------------------------------
+---------+
|         |
|         |
+----     |
|         |
|         |
|         |
|     ----+
|         |
|         |
+---------+
--------------------------------------------------------------------------------------------------------
出力例
+---------+
|@@@@@@@@@|
|@@@@@@@@@|
+----@@@@@|
|@@@@@@@@@|
|@@@@@@@@@|
|@@@@@@@@@|
|@@@@@----+
|@@@@@@@@@|
|@@@@@@@@@|
+---------+
--------------------------------------------------------------------------------------------------------

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 11
#define MAXSTACK N * N /* スタックの要素数の最大値*/
struct zahyo
{
    int x, y;
};
typedef struct zahyo elementtype;

char buf[N + 2];
char canvas[N][N];

struct stack
{
    int top;                        /* 最後に入れた要素の位置(添字)、スタックが空なら-1　*/
    elementtype contents[MAXSTACK + 1]; /* 要素を含む配列。0番目からtop 番目までがスタックの要素　*/
};



void initstack(struct stack *p);
int stackempty(struct stack *p);
elementtype pop(struct stack *p);
void push(struct stack *p, elementtype e);
//void printstack(struct stack *s); //要素の出力

elementtype move(elementtype a,elementtype b)//2が与えられたとき、その和を出力
{
    elementtype q = {.x = a.x + b.x, .y = a.y + b.y};
    return q;
}
elementtype possible_moves [ 4 ] = 
/*四方向の候補を求めるときに使う*/
{
  { .x =  0, .y = -1 },
  { .x =  0, .y = +1 },
  { .x = -1, .y =  0 },
  { .x = +1, .y =  0 } };

int main()
{
    int i, j;
    i = 0;

    /* 入力を1行ずつ読み込んでheya へ格納*/
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        for (j = 0; j < N; ++j)
            canvas[i][j] = buf[j];
        ++i;
    }

    /* ここを埋めればよい*/

    struct stack s;
    elementtype ichi,ni;
    elementtype candidate [ 4 ]; // left, right, up, down;
    ichi.x = N / 2;
    ichi.y = N / 2;
    initstack(&s);
    push(&s,ichi); //中心の座標(N/2; N/2) をプッシュ
    //ni = pop(&s);
    //printf("%d,%d\n",ni.x,ni.y);

    while(!stackempty(&s)){
        //printf("whileに入ったよ\n");
        ni = pop(&s);
        for(int i = 0; i < 4; i++){
            candidate[i] = move(ni, possible_moves[i]);
            if(canvas[candidate[i].x][candidate[i].y] == ' '){
                push(&s,candidate[i]);
                //printf("push candidate[%d]\n",i);
                canvas[candidate[i].x][candidate[i].y] = '@';
            }
            else if(canvas[ni.x][ni.y] == ' '){
                canvas[ni.x][ni.y] = '@';
            }
        }

    }



    /* canvas の出力*/
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
    return 0;
}

void initstack(struct stack *p)
{
    p->top = -1;
}

int stackempty(struct stack *p)
{
    return p->top < 0;
}

/*
void printstack(struct stack *p)
{
    for (int i = 0; i <= p->top; i++)
    {
        printf("[%c]", p->contents[i]);
    }
    printf("\n");
}
*/

void push(struct stack *p, elementtype x)
{
    //printf("push %d\n",x);
    p->top += 1;
    if (p->top >= MAXSTACK)
    {
        printf("Overflow\n");
        exit(1);
    }
    else
    {
        p->contents[p->top] = x;
    }
    return;
}

elementtype pop(struct stack *p)
{
    //printf("pop\n");
    elementtype x;
    if (p->top < 0)
    {
        printf("Underflow\n");
        exit(1);
    }
    else
    {
        x = p->contents[p->top];
        p->top -= 1;
        return x;
    }
}
/*
キューを用いたプログラム。
左上の座標を(0,0)、右下の座標を(9,9) とする部屋(下向きがx 軸、右向きがy 軸) があり、
* は通ることのできない壁であるとし、S はスタート地点、G はゴール地点とする。
このような部屋において、上下左右にしか移動できないコマが指定したスタートS からゴールG までの最短距離を計算するプログラムを作成。
ここで、S からG までの最短距離とは、S からG に移動するまでに通るコマ( S 自身は除く) の数の最小値である。
標準入力は、10 × 10 の部屋のレイアウトで、周囲は全て壁であり、S とG は必ず1 つずつ存在し、
S からG までたどり着ける道があるものと仮定。
入力例
--------------------------------------------------------------------------------------------------------
**********
*        *
*S *     *
*****    *
*        *
*    *****
*    *  G*
*    *   *
*        *
**********
--------------------------------------------------------------------------------------------------------
出力例
19
--------------------------------------------------------------------------------------------------------

*/


#include <stdio.h>
#include <stdlib.h>
#define N 10
#define MAXQUEUE N * N * 4

struct zahyo
{
  int x;
  int y;
};

typedef struct zahyo elementtype;

char buf[N + 2];
char heya[N][N];

struct queue
{
  int front;
  int rear;
  elementtype contents[MAXQUEUE];
};



void initqueue(struct queue *p);
int queueempty(struct queue *p);
void printqueue(struct queue *p);
void putq(struct queue *p, elementtype e);
void putqstruct(struct queue *p, elementtype e);
elementtype getq(struct queue *p);

elementtype move(elementtype a,elementtype b)//2要素が与えられたとき、その和を出力
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

elementtype ini(elementtype *a){ //zahyoの初期化
    a->x = 0;
    a->y = 0;
    return *a;
}

int main(void)
{
  int i, j;
  elementtype ni;
  elementtype start, goal;
  ini(&start);
  ini(&goal);
  //printf("start.x = %d\n",start.x);
  elementtype candidate [ 4 ]; // left, right, up, down;
  int kyori[N][N];
  for (i = 0; i < N; i++){
    for (j = 0; j < N; j++){
      kyori[i][j] = -1;
    }
  }
  /* 入力を1行ずつ読み込んでheya へ格納*/
  i = 0;

  while (fgets(buf, sizeof(buf), stdin) != NULL)
  {
    for (j = 0; j < N; ++j)
    {
      if (buf[j] == 'S') /* 文字がS のときstart に記録*/
      {
        start.x = i;
        start.y = j;
      }
      else if (buf[j] == 'G')/* 文字がG のときgoal に記録*/
      {
        goal.x = i;
        goal.y = j;
      }
      heya[i][j] = buf[j];
    }
    i++;
  }
  kyori[start.x][start.y] = 0; //kyori[sx][sy] に0 を入れる
  struct queue q;
  initqueue(&q);
  
  putq(&q, start);
  /*
  ヒントをそのままc言語に翻訳しただけ。
  */
  while (!queueempty(&q))
  {
    ni = getq(&q);
    for(int i = 0; i < 4; i++){
            candidate[i] = move(ni, possible_moves[i]);
            if(kyori[candidate[i].x][candidate[i].y] == -1 && heya[candidate[i].x][candidate[i].y] != '*'){
                putq(&q,candidate[i]);
                //printf("push candidate[%d]\n",i);
                kyori[candidate[i].x][candidate[i].y] = kyori[ni.x][ni.y] + 1;
            }
        }
  }
  printf("%d\n", kyori[goal.x][goal.y]);
  return 0;
}

void initqueue(struct queue *p)
{
    p->front = 0;
    p->rear = 0;
}

int queueempty(struct queue *p)
{
    return p->rear == p->front ? 1 : 0;
}

/*
void printqueue(struct queue *p)
{

    for (int i = p->front; i < p->rear; i++)
    {
        printf("[%d]", p->contents[i]);
    }
    printf("\n");
}

*/

void putq(struct queue *p, elementtype e)
{
    if (p->rear == MAXQUEUE)
  {
    printf("Sorry.\n");
    exit(1);
  }
  p->rear++;
  p->contents[p->rear - 1] = e;
}

elementtype getq(struct queue *p)
{
    p->front++;
  return p->contents[p->front - 1];
}
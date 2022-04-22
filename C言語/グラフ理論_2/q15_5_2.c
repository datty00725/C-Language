#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define ROSENZU "rosenzu.txt" /* 路線図データファイル */
#define SETMAX 10600          /* 集合の要素数の最大値 (駅の数) */
char buf[256];                /* 入力された文字列を格納するグローバル変数 */
int dist[SETMAX];             /* 指定された駅から各駅までの最短距離を格納するグローバル変数 */
int prev[SETMAX];             /* 各駅までの最短距離における1つ前の駅を格納するグローバル変数 */
int hop[SETMAX];              /* 各駅までの最短距離における駅の数を格納するグローバル変数 */

struct node
{
  int eki, rosen, kyori;
  struct node *next;
};
struct set
{
  int elements[SETMAX];
  int size;
};

void init_set(struct set *p, int n, int e)
{
  /* ※ここは問題 1 と同じ */
  int i = 0, j = 0;
  while (i < n)
  {
    if (i == e)
      ;
    else
    {
      p->elements[j] = i;
      j++;
    }
    i++;
  }
  p->size = i - 1;
}

int delete_min(struct set *p)
{
  /* ※ここは問題 3 から変更する必要あり */
  if (p->size == 0)
    return -1;
  else
  {
    int i = p->elements[0], j = 0, k, min = dist[p->elements[0]];
    for (k = 0; k < p->size; k++)
    {
      if (dist[p->elements[k]] < min)
      {
        min = dist[p->elements[k]];
        i = p->elements[k];
        j = k;
      }
      else if (dist[p->elements[k]] == min)
      {
        if (hop[i] > hop[p->elements[k]])
        {
          min = dist[p->elements[k]];
          i = p->elements[k];
          j = k;
        }
        else if (hop[i] == hop[p->elements[k]])
        {
          if (prev[i] > prev[p->elements[k]])
          {
            min = dist[p->elements[k]];
            i = p->elements[k];
            j = k;
          }
        }
      }
    }
    p->elements[j] = p->elements[p->size - 1];
    p->size -= 1;
    return i;
  }
}

void add_edge(struct node *adjlist[], int eki1, int eki2, int rosen, int kyori)
{
  /* ここは問題 4 と同じ */
  struct node *p, *q;
  p = (struct node *)malloc(sizeof(struct node));
  p->eki = eki1;
  p->rosen = rosen;
  p->kyori = kyori;
  p->next = adjlist[eki2];
  adjlist[eki2] = p;
  q = (struct node *)malloc(sizeof(struct node));
  q->eki = eki2;
  q->rosen = rosen;
  q->kyori = kyori;
  q->next = adjlist[eki1];
  adjlist[eki1] = q;
}

int dijkstra_path(struct node *adjlist[], int eki1, int eki2, int ekisu)
{
  /* ※ここを適切なプログラムで埋める */
  /* 問題 4 の関数 dijkstra を適切にする */
  int i, cur;
  struct node *p;
  struct set unknown;

  for (i = 0; i < ekisu; i++)
  {
    dist[i] = INT_MAX;
    hop[i] = INT_MAX;
  }
  dist[eki1] = 0;
  hop[eki1] = 0;
  cur = eki1;
  init_set(&unknown, ekisu, eki1);
  while (&unknown != NULL && cur != eki2)
  {
    p = adjlist[cur];
    while (p != NULL)
    {
      if (dist[cur] + p->kyori < dist[p->eki])
      {
        dist[p->eki] = dist[cur] + p->kyori;
        hop[p->eki] = hop[cur] + 1;
        prev[p->eki] = cur;
      }
      else if (dist[cur] + p->kyori == dist[p->eki])
      {
        if (hop[p->eki] > hop[cur] + 1)
        {
          dist[p->eki] = dist[cur] + p->kyori;
          hop[p->eki] = hop[cur] + 1;
          prev[p->eki] = cur;
        }
        else if (hop[p->eki] == hop[cur] + 1)
        {
          if (prev[p->eki] > cur)
          {
            dist[p->eki] = dist[cur] + p->kyori;
            hop[p->eki] = hop[cur] + 1;
            prev[p->eki] = cur;
          }
        }
      }
      p = p->next;
    }
    cur = delete_min(&unknown);
  }
  return dist[eki2];
}

int main()
{
  int eki, eki1, eki2, rosen, ekisu, i, kyori;
  FILE *fp = fopen(ROSENZU, "r"); /* 路線図ファイルの読取り開始 */
  fscanf(fp, "%d ", &ekisu);      /* 1行目の駅数を読取り */
  struct node *adjlist[ekisu];
  /* 隣接リスト表現を初期化、すべての頂点に対する隣接リストを空にする */
  for (i = 0; i < ekisu; ++i)
    adjlist[i] = NULL;
  while (fgets(buf, sizeof(buf), fp) != NULL)
  {
    /* 隣り合う駅の情報を読取り */
    sscanf(buf, "%d:%d:%d:%d ", &eki1, &eki2, &rosen, &kyori);
    /* そのデータを隣接リスト表現のグラフに追加 */
    add_edge(adjlist, eki1, eki2, rosen, kyori);
  }
  fclose(fp); /* 路線図ファイルの読取り終了 */
  scanf("%d %d ", &eki1, &eki2);
  kyori = dijkstra_path(adjlist, eki1, eki2, ekisu);
  /* 最短距離を出力*/
  printf("%d:", kyori);
  eki = eki2;
  /* hop[eki]の数だけ前に戻って出力 */
  for (i = 0; i < hop[eki2]; ++i)
  {
    printf(" %d <-", eki); /* 1つ手前の駅へ */
    eki = prev[eki];       /* さらに1つ手前の駅へ */
  }
  /* プログラムが正しければ、ここで eki が開始駅 eki1 になっているはず (違っていたら異常終了) \
*/
  if (eki != eki1)
  {
    fprintf(stderr, "hop or prev is invalid.\n");
    exit(1);
  }
  printf(" %d\n", eki); /* 開始駅を出力 */
  return 0;
}

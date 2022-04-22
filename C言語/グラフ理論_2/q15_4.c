#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define ROSENZU "rosenzu.txt" /* 路線図データファイル */
#define SETMAX 10600          /* 集合の要素数の最大値 (駅の数) */
char buf[256];                /* 入力された文字列を格納するグローバル関数 */
int dist[SETMAX];             /* 指定された駅から各駅までの最短距離を格納するグローバル関数 */

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

typedef struct set *Pset;

typedef int elementtype;
typedef int kyoritype;
typedef struct node *list;

list makelist();                                                //後々dataについてもmallocが必要になるかも。
list cons(elementtype e1, elementtype e2, kyoritype k, list l); // eを要素とするノードをlの頭に付ける
list cons_node(list e, list l);
void insert(elementtype e, elementtype e2, kyoritype k, list l); // eを要素とするnodeをlの次に挿入する
void insert_node(list e, list l);
list serch_tail(); // lのお尻を探す
list nod(list t);
// Pset makelist_set();

void init_set(struct set *p, int n, int e)
{
    /* ※ここを適切なプログラムで埋める */
    int i = 0, j = 0;
    while (i < n)
    {
        if (i != e)
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
    /* ※ここを適切なプログラムで埋める */
    if (p->size == 0)
    {
        return -1;
    }
    else
    {
        int i = p->elements[0], j = 0, min = dist[p->elements[0]];
        for (int k = 0; k < p->size; k++)
        {
            if (dist[p->elements[k]] < min)
            {
                min = dist[p->elements[k]];
                i = p->elements[k];
                j = k;
            }
        }
        p->elements[j] = p->elements[p->size - 1];
        p->size -= 1;
        return i;
    }
}

void add_edge(struct node *adjlist[], int eki1, int eki2, int rosen, kyoritype kyori)
{
    struct node *a, *b;
    a = makelist();
    b = makelist();
    a->eki = eki1;
    a->rosen = rosen;
    a->kyori = kyori;
    b->eki = eki2;
    b->rosen = rosen;
    b->kyori = kyori;
    if (adjlist[eki1] == NULL) // eki1から順にみていく
    {
        adjlist[eki1] = b;
    }
    else
    {
        adjlist[eki1] = cons_node(b, adjlist[eki1]);
    }
    if (adjlist[eki2] == NULL)
    {
        adjlist[eki2] = a;
        // adjlist[eki2] = adjlist[eki2]->next;
    }
    else
    {
        adjlist[eki2] = cons_node(a, adjlist[eki2]);
    }
}

int dijkstra(struct node *adjlist[], int eki1, int eki2, int ekisu)
{
    /* ※ここを適切なプログラムで埋める */
    struct set unknown;
    // Pset unknown;  //にするとエラーが起きてしまう。。。

    for (int i = 0; i < ekisu; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[eki1] = 0; //配列dist のeki1 番目の要素を0 とし、それ以外の要素をINT_MAX にしておく
    int cur = eki1;
    init_set(&unknown, ekisu, eki1);
    while (unknown.size == 0 || cur != eki2)
    {
        list p = adjlist[cur];
        while (p)
        {
            if (dist[cur] + p->kyori < dist[p->eki])
            {
                dist[p->eki] = dist[cur] + p->kyori;
            }
            p = p->next;
        }
        cur = delete_min(&unknown);
    }
    return dist[eki2];
}

int main()
{
    int eki1, eki2, rosen, ekisu, i, kyori;
    FILE *fp = fopen(ROSENZU, "r"); /* 路線図ファイルを読む準備 */
    fscanf(fp, "%d ", &ekisu);      /* 1行目の駅数を読みとり */
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
    fclose(fp);
    scanf("%d %d ", &eki1, &eki2);
    printf("%d\n", dijkstra(adjlist, eki1, eki2, ekisu));
    // for (i = 0; i < ekisu; ++i)
        // if (dist[i] < INT_MAX)
            // printf("%d: %d\n", i, dist[i]);
    return 0;
}

list makelist()
{
    list l;
    // elementtype *s = (elementtype *)malloc(sizeof(elementtype));
    l = (list)malloc(sizeof(struct node));
    // l->data = *s;
    l->next = NULL;
    return l;
}

list cons(elementtype e1, elementtype e2, kyoritype k, list l)
{
    list q;
    q = makelist();
    q->eki = e1;
    q->rosen = e2;
    q->kyori = k;
    q->next = l;
    return q;
}

void insert(elementtype e1, elementtype e2, kyoritype k, list l)
{
    l->next = cons(e1, e2, k, l->next);
}

list serch_tail(list l)
{
    list p = l;

    while (p->next != NULL)
    {
        p = p->next;
    }

    return p;
}

list cons_node(list e, list l)
{

    e->next = l;
    return e;
}

void insert_node(list e, list l)
{
    l->next = cons_node(e, l->next);
}

list nod(list t)
{
    // if (t)
    //{
    //     printf("node is %s,%d\n", t->data.name, t->data.id);
    // }
    return t;
}

//　2 駅離れた駅のうち最も遠い駅までの距離を計算する関数two_hop_kyori を定義
#include <stdio.h>
#include <stdlib.h>
char buf[256];

struct node
{
    int eki, rosen;
    float kyori;
    struct node *next;
};
typedef int elementtype;
typedef float kyoritype;
typedef struct node *list;

list makelist();                                                //後々dataについてもmallocが必要になるかも。
list cons(elementtype e1, elementtype e2, kyoritype k, list l); // eを要素とするノードをlの頭に付ける
list cons_node(list e, list l);
void insert(elementtype e, elementtype e2, kyoritype k, list l); // eを要素とするnodeをlの次に挿入する
void insert_node(list e, list l);
list serch_tail(); // lのお尻を探す

void add_edge(struct node *adjlist[], int eki1, int eki2, int rosen, float kyori)
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

/* 頂点数 n の隣接リスト表現を表示する関数 */
void print_adjlist(struct node *adjlist[], int n)
{
    int i;
    struct node *p;
    for (i = 0; i < n; ++i)
    {
        printf("%d:", i);
        p = adjlist[i];
        while (p != NULL)
        {
            printf(" (%d,%d,%.3f)", p->eki, p->rosen, p->kyori);
            p = p->next;
        }
        printf("\n");
    }
    return;
}

float two_hop_kyori(struct node *adjlist[], int eki)
{
    kyoritype rem = 0, tem, mem = 0;
    list a, b;
    a = adjlist[eki];
    while (a)
    {
        b = adjlist[a->eki];
        while (b)
        {
            if (b->eki != eki)
            {
                tem = a->kyori + b->kyori;
                if (rem < tem)
                {
                    rem = tem;
                }
            }
            b = b->next;
        }
        if (mem < rem)
        {
            mem = rem;
        }
        a = a->next;
    }
    return mem;
}

int main()
{
    int eki1, eki2, rosen, ekisu, i;
    float kyori;
    scanf("%d ", &ekisu);
    struct node *adjlist[ekisu];
    /* 隣接リスト表現を初期化.すべての頂点に対する隣接リストを空にする */
    for (i = 0; i < ekisu; ++i)
        adjlist[i] = NULL;
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        /* 隣り合う駅の情報を読取り */
        sscanf(buf, "%d:%d:%d:%f ", &eki1, &eki2, &rosen, &kyori);
        /* そのデータを隣接リスト表現のグラフに追加 */
        add_edge(adjlist, eki1, eki2, rosen, kyori);
    }
    for (i = 0; i < ekisu; ++i)
        printf("%d: %.3f\n", i, two_hop_kyori(adjlist, i));
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
//隣接行列表現で与えられたグラフに対し、そのグラフの推移的閉包の隣接行列表現を求めるプログラムを作成
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

void warshall(int n, int adjmat[n][n], int result[n][n])
{
    /* ※ここを適切なプログラムで埋める */
    int reach[n + 1][n][n], i, j, k;
    for (k = 0; k <= n; k++) // 初期化
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; ++j)
            {
                reach[k][i][j] = 0;
            }
        }
    }

    for (i = 0; i < n; ++i) // when 0
    {
        for (j = 0; j < n; ++j)
        {
            if (adjmat[i][j] == 1 || i == j)
                reach[0][i][j] = 1;
        }
    }

    for (k = 1; k <= n; ++k) // when over 0
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                if ((reach[k - 1][i][j] == 1 || reach[k - 1][i][k - 1]) && (reach[k - 1][i][j] == 1 || reach[k - 1][k - 1][j]))
                {
                    reach[k][i][j] = 1;
                }
            }
        }
    }

    for (i = 0; i < n; i++) // copy
    {
        for (j = 0; j < n; j++)
        {
            result[i][j] = reach[n][i][j];
        }
    }
    return;
}

int main()
{
    int ekisu;
    scanf("%d ", &ekisu);
    int adjmat[ekisu][ekisu], result[ekisu][ekisu];
    int eki1, eki2, rosen, i, j;
    float kyori;
    for (i = 0; i < ekisu; ++i)
    {
        for (j = 0; j < ekisu; ++j)
        {
            adjmat[i][j] = 0;
        }
    }
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        sscanf(buf, "%d:%d:%d:%f ", &eki1, &eki2, &rosen, &kyori);
        adjmat[eki1][eki2] = 1;
        adjmat[eki2][eki1] = 1;
    }
    warshall(ekisu, adjmat, result);
    for (i = 0; i < ekisu; ++i)
    {
        for (j = 0; j < ekisu; ++j)
        {
            printf("%d", result[i][j]);
        }
        printf("\n");
    }
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
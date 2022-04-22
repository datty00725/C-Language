//リスト構造のマージソート
#include <stdio.h>
#include <stdlib.h>

int count = 0;
char kijun;

struct point
{
    int x, y;
};
typedef struct point elementtype;

struct node
{
    elementtype element;
    struct node *next;
};
typedef struct node *list;

int compare_by(struct point p1, struct point p2);
void swap(list q, list p);
void print_arr(list q);
list makelist();
list cons(elementtype e, list l);
void insert(list l, elementtype e);
list serch_tail();
int compare(struct point p1, struct point p2)
{
    /* ※ここは適切なプログラムで埋める */
    ++count;
    // printf("compare\n");
    return compare_by(p1, p2);
}

void split(list l1, list l2)
{
    /* ※ここは適切なプログラムで埋める */
    // printf("aa\n");
    list p1, p2;
    p1 = l1;
    p2 = l1;
    while (p2 != NULL && p2->next != NULL)
    {
        p2 = p2->next;
        p2 = p2->next;
        p1 = p1->next;
        // printf("aaaa\n");
    }
    l2->next = p1->next;
    p1->next = NULL;
    // printf("aaa\n");
}
void merge(list l1, list l2)
{
    /* ※ここも適切なプログラムで埋める */
    int judge;
    list fix;
    fix = l1;
    //printf("count = %d\n\n", count);

    //printf("now in merge\n");
    //print_arr(l1);
    //printf("\n");
    //print_arr(l2);
    //printf("\n");

    while (l2->next && l1->next) //短い方が終わればマージ終わり
    {
        // printf("good\n");
        judge = compare(l1->next->element, l2->next->element);
        // printf("count = %d\n", count);
        if (judge == 1) // l2 min
        {
            //printf("good2\n");
            insert(l1, l2->next->element);

            l1 = l1->next;
            l2 = l2->next;
        }
        else // l1 min and l1 = l2
        {
            //printf("good3\n");
            l1 = l1->next;
        }
    }
    if (l2->next)
    {
        serch_tail(fix)->next = l2->next;
    }

    l1 = fix;
    //printf("mergeした結果\n");
    //print_arr(l1);
    //printf("\n");
}

void merge_sort(list l)
{
    /* ※ここも適切なプログラムで埋める */
    if (!l->next->next)
    {
        return;
    }
    list l2;
    l2 = makelist();

    // printf("1\n");
    // print_arr(l);

    split(l, l2);

    //printf("lを表示するぞい\n");
    //print_arr(l);
    //printf("\n");

    //printf("l2を表示するぞい\n");
    //print_arr(l2);
    //printf("\n");
    //   printf("2\n");
    merge_sort(l);
    //  printf("3\n");
    merge_sort(l2);
    //  printf("4\n");
    merge(l, l2);
}

int main()
{
    char buf[128];
    struct point p;
    list l, last;
    scanf("%c ", &kijun);

    last = l = (list)malloc(sizeof(struct node));
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        sscanf(buf, "%d %d", &p.x, &p.y);
        last = last->next = (list)malloc(sizeof(struct node));
        last->element = p;
    }
    last->next = NULL;

    merge_sort(l);

    printf("%d\n", count);
    while ((l = l->next) != NULL)
    {
        p = l->element;
        printf("%d %d\n", p.x, p.y);
    }
    return 0;
}

int compare_by(struct point p1, struct point p2)
/*
X,Y,Dについて題意を満たすように構築。
Dについて距離が等しいときには題意よりXを用いて比較をする。
*/
{
    /* ※ここは適切なプログラムで埋める */

    if (kijun == 'X')
    {
        if (p1.x > p2.x)
        {
            return 1;
        }
        else if (p1.x < p2.x)
        {
            return -1;
        }
        else
        {
            if (p1.y > p2.y)
            {
                return 1;
            }
            else if (p1.y < p2.y)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }
    }
    else if (kijun == 'Y')
    {
        if (p1.y > p2.y)
        {
            return 1;
        }
        else if (p1.y < p2.y)
        {
            return -1;
        }
        else
        {
            if (p1.x > p2.x)
            {
                return 1;
            }
            else if (p1.x < p2.x)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }
    }
    else if (kijun == 'D')
    {
        int len_1 = p1.x * p1.x + p1.y * p1.y, len_2 = p2.x * p2.x + p2.y * p2.y;
        if (len_1 > len_2)
        {
            return 1;
        }
        else if (len_1 < len_2)
        {
            return -1;
        }
        else
        {
            if (p1.x > p2.x)
            {
                return 1;
            }
            else if (p1.x < p2.x)
            {
                return -1;
            }
            else
            {
                if (p1.y > p2.y)
                {
                    return 1;
                }
                else if (p1.y == p2.y)
                {
                    return 0;
                }
                else
                {
                    return -1;
                }
            }
        }
    }
    return 0;
}

list makelist()
{
    list l;
    l = (list)malloc(sizeof(struct node));
    l->next = NULL;
    return l;
}

list cons(elementtype e, list l)
{
    list q;
    q = makelist();
    q->element = e;
    q->next = l;
    return q;
}

void insert(list l, elementtype e)
{
    l->next = cons(e, l->next);
}

void print_arr(list q)
{
    q = q->next;
    for (; q;)
    {
        printf("%d %d\n", q->element.x, q->element.y);
        q = q->next;
    }
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
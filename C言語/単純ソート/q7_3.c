//選択ソート
#include <stdio.h>
#include <stdlib.h>
int count = 0; /* ←比較回数を数えるグローバル変数 */

struct point
{
    int x, y;
};

int compare_by(struct point p1, struct point p2, char c)
/*
Dの時、距離が等しいときXを用いて比較をしている。
カウントがここで一つ余計に増えてしまうため、一つ減らすように調整。
*/
{
    ++count; /* ←ここで比較回数を1回分カウント */
    if (c == 'X')
    {
        if (p1.x > p2.x)
        {
            return 1;
        }
        else if (p1.x == p2.x)
        {
            return p1.y > p2.y ? 1 : 0;
        }
        else
        {
            return 0;
        }
    }
    else if (c == 'Y')
    {
        if (p1.y > p2.y)
        {
            return 1;
        }
        else if (p1.y == p2.y)
        {
            return p1.x > p2.x ? 1 : 0;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        int len_1 = p1.x * p1.x + p1.y * p1.y, len_2 = p2.x * p2.x + p2.y * p2.y;
        if (len_1 > len_2)
        {
            return 1;
        }
        if (len_1 == len_2)
        {
            count--;
            return compare_by(p1, p2, 'X');
        }
        else
        {
            return 0;
        }
    }
}

int max_index_by(struct point a[], int n, char c)
{
    /* ※compare_by を利用して適切に埋める */
    struct point x = a[0];
    int where = 0;
    for (int k = 0; k < n - 1; k++)
    {
        if (!compare_by(x, a[k + 1], c))
        {
            x = a[k + 1];
            where = k + 1;
        }
    }
    //printf("一ちゃん大きいのは1 a[%d] : x = %d : y = %d\n",where,a[where].x,a[where].y);
    return where;
}

void swap(struct point *p, struct point *q)
{
    struct point *temp;
    temp = (struct point*)malloc(sizeof(struct point));
    temp->x = p->x;
    temp->y = p->y;

    p->x = q->x;
    p->y = q->y;

    q->x = temp->x;
    q->y = temp->y; 
}

void selection_sort(struct point a[], int n, char c)
{
    /* ※ ここはアルゴリズムに従って適切に埋める */
    /*
    printf("before\n");
    for (int i = 0; i < n; ++i)
        printf("%d %d\n", a[i].x, a[i].y);
        printf("index = %d\n",max_index_by(a, n, c));
        */
    for (int k = n; k > 1; k--)
    {
        //printf("k = %d\n",k);
        //printf("index = %d\n",max_index_by(a, k, c));
        
        //printf("swap a[%d],a[%d]\n",max_index_by(a, k, c),k);
        swap(&a[max_index_by(a, k, c)],&a[k-1]);
    }
}

int main()
{
    char c, buf[128];
    struct point p, arr[128];
    int i = 0, n;
    scanf("%c ", &c);
    while (fgets(buf, sizeof(buf), stdin) != NULL && i < 128)
    {
        sscanf(buf, "%d %d", &p.x, &p.y);
        arr[i] = p;
        ++i;
    }
    n = i;
    //printf("%d %d\n", arr[0].x, arr[0].y);
    //printf("max_index = %d\n",max_index_by(arr,n,c));
    //swap(&arr[0],&arr[1]);
    selection_sort(arr, n, c);

    printf("%d\n", count);
    for (i = 0; i < n; ++i)
        printf("%d %d\n", arr[i].x, arr[i].y);
    return 0;
}
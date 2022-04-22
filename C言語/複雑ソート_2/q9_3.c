//ヒープソート
#include <stdio.h>

int count = 0;
char kijun;
int size;
struct point
{
    int x, y;
};

void swap(struct point *q, struct point *p);
int compare_by(struct point p1, struct point p2);
void print_arr(struct point *q);
int compare(struct point p1, struct point p2)
{
    ++count;
    /* ※ここは前回と同じ*/
    return compare_by(p1, p2);
}

void pushdown(struct point a[], int m, int n)
{
    /* ※ここを適切なプログラムで埋める*/
    // print_arr(a);
    int i;
    if (2 * m + 2 <= n)
    {
        // printf("a\n");
        if (compare(a[2 * m + 1], a[2 * m + 2]) == 1)
        {
            // printf("aa\n");
            // printf("what is m : m = %d\n", m);
            // print_arr(a);
            i = 2 * m + 1;
        }
        else
        {
            // printf("aaa\n");
            // printf("what is m : m = %d\n", m);
            i = 2 * m + 2;
        }
        if (compare(a[i], a[m]) == 1)
        {
            // printf("aaaa\n");
            // printf("what is m : m = %d\n", m);
            // printf("before swap\na[%d] : (%d,%d)\na[%d] : (%d,%d)\n",i,a[i].x,a[i].y,m,a[m].x,a[m].y);
            swap(&a[i], &a[m]);
            // printf("after swap\na[%d] : (%d,%d)\na[%d] : (%d,%d)\n",i,a[i].x,a[i].y,m,a[m].x,a[m].y);

            pushdown(a, i, n);
        }
        else
        {
            // printf("123123\n");

            return;
        }
    }
    else if (2 * m + 1 == n)
    {
        if (compare(a[2 * m + 1], a[m]) == 1)
        {
            // printf("aaaaa\n");
            // printf("what is m : m = %d\n", m);
            // printf("before swap\na[%d] : (%d,%d)\na[%d] : (%d,%d)\n",2 * m + 1,a[2 * m + 1].x,a[2 * m + 1].y,m,a[m].x,a[m].y);
            swap(&a[2 * m + 1], &a[m]);
            // printf("after swap\na[%d] : (%d,%d)\na[%d] : (%d,%d)\n",2 * m + 1,a[2 * m + 1].x,a[2 * m + 1].y,m,a[m].x,a[m].y);
            return;
        }
        else
        {
            // printf("aaaaaa\n");
            return;
        }
    }
    else if (2 * m + 1 > n)
    {
        // printf("aaaaaa\n");
        return;
    }
}

void heap_sort(struct point a[], int n)
{
    for (int k = n / 2 - 1; k >= 0; k--)
    {
        pushdown(a, k, n - 1);
    }
    for (int k = n - 1; k > 0; k--)
    {
        swap(&a[0], &a[k]);
        pushdown(a, 0, k - 1);
    }
}

int main()
{
    char buf[128];
    struct point p, arr[128];
    int i = 0, n;
    scanf("%c ", &kijun);
    while (fgets(buf, sizeof(buf), stdin) != NULL && i < 128)
    {
        sscanf(buf, "%d %d", &p.x, &p.y);
        arr[i] = p;
        ++i;
    }
    n = i;
    size = i;
    heap_sort(arr, n);
    printf("%d\n", count);
    for (i = 0; i < n; ++i)
        printf("%d %d\n", arr[i].x, arr[i].y);
    return 0;
}

int compare_by(struct point p1, struct point p2)
/*
an_i,Y,Dについて題意を満たすように構築。
Dについて距離が等しいときには題意よりan_iを用いて比較をする。
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

void swap(struct point *q, struct point *p)
{
    struct point temp;

    temp = *q;
    *q = *p;
    *p = temp;
}
void print_arr(struct point *q)
{
    for (int i = 0; i < size; ++i)
        printf("%d %d\n", q[i].x, q[i].y);
}
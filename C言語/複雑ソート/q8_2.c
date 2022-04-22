//クイックソート
#include <stdio.h>

int count = 0;
char kijun;
int size;

struct point
{
    int x, y;
};

int compare_by(struct point p1, struct point p2);
void swap(struct point *q, struct point *p);
void print_arr(struct point *q);
int compare(struct point p1, struct point p2)
{
    /* ※ここは適切なプログラムで埋める */
    ++count;
    // printf("compare\n");
    return compare_by(p1, p2);
}

int partition(struct point a[], int m, int n)
{
    /* ※ここも適切なプログラムで埋める */
    struct point pivot = a[m];
    int l = m + 1, r = n;
    while (1)
    {
        for (; l < n && compare(pivot, a[l]) == 1; l++)
            ;
        // printf("a\n");
        for (; r > m && compare(a[r], pivot) == 1; r--)
            ;
        // printf("b\n") ;
        if (l < r)
        {
            // printf("before\n");
            // print_arr(a);
            swap(&a[l], &a[r]);
            // printf("after\n");
            // print_arr(a);
        }
        else
        {
            break;
        }
        l++;
        r--;
    }
    // printf("r = %d\n\n",r);
    swap(&a[r], &a[m]);
    return r;
}

void quicksort(struct point a[], int m, int n)
{
    /* ※ここを適切なプログラムで埋める */
    int p;
    if (m < n)
    {
        p = partition(a, m, n);
        //print_arr(a);
        //printf("\n");
        quicksort(a, m, p - 1);

        quicksort(a, p + 1, n);
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
    size = n;
    quicksort(arr, 0, n - 1);
    printf("%d\n", count);
    for (i = 0; i < n; ++i)
        printf("%d %d\n", arr[i].x, arr[i].y);
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
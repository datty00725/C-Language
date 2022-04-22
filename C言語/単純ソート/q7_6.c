//バブルソート
#include <stdio.h>
#include <stdlib.h>

int count = 0;
//int ko = 0;

struct point
{
    int x, y;
};

int compare_by(struct point p1, struct point p2, char c)
{
    ++count;
    // printf("in compare count = %d\n", count);
    /* ※ ここは問題2 と同じ*/
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
            //ko++;
            count--;
            return compare_by(p1, p2, 'X');
        }
        else
        {
            return 0;
        }
    }
}

void swap(struct point *p, struct point *q)
{
    struct point *temp;
    temp = (struct point *)malloc(sizeof(struct point));
    temp->x = p->x;
    temp->y = p->y;

    p->x = q->x;
    p->y = q->y;

    q->x = temp->x;
    q->y = temp->y;
}

void bubble_sort(struct point a[], int n, char c)
/*
題意通りに翻訳しただけ
*/
{
    for (int k = n - 2; k > -1; k--)
    {
        for (int l = 0; l <= k; l++)
        {
            if (compare_by(a[l], a[l + 1], c))
            {
                swap(&a[l], &a[l + 1]);
            }
        }
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
    bubble_sort(arr, n, c);
    printf("%d\n", count);
    //printf("%d\n", ko);
    for (i = 0; i < n; ++i)
        printf("%d %d\n", arr[i].x, arr[i].y);
    return 0;
}
//マージソート
#include <stdio.h>

int count = 0;
char kijun;
int size; //デバッグで使用

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

void merge(struct point a[], int m, int n, int h)
{
    printf("in merge\n");
    printf("m = %d\nn = %d\n",m,n);
    struct point another[n - m + 1]; //別の配列
    int l = m, r = h + 1, an_i = m, judge;

    for (int i = m; i < n; i++)
    {
        printf("in for\n");
        if (l == h + 1)
        { //前ブロックの最後まで
            printf("11111\n");
            break;
        }
        if (r == n + 1)
        { //後ブロックの最後まで
        printf("22222\n");
            break;
        }
        printf("33333\n");
        judge = compare(a[l], a[r]);
        if (judge == 1)
        { //題意より小さい方を別配列へ
        printf("judge = 1\n");
        printf("another[%d] = a[%d].x = %d, a[%d].y = %d\n",an_i,r,a[r].x,r,a[r].y);
            another[an_i++] = a[r++];
        }
        if (judge == -1)
        {
            printf("judge = -1\n");
            printf("another[%d] = a[%d].x = %d, a[%d].y = %d\n",an_i,l,a[l].x,l,a[l].y);
            another[an_i++] = a[l++]; //題意より小さい方を別配列へ
        }
        if (judge == 0)
        { //題意より同じなら前半のものを先に
        printf("judge = 0\n");
        printf("another[%d] = a[%d].x = %d, a[%d].y = %d\n",an_i,l,a[l].x,l,a[l].y);

            another[an_i++] = a[l++];
        }
    }
    if (l == h + 1)
    { //なくなったら残りを全部入れる
        while (r < n + 1)
        {
            printf("\n");

            another[an_i++] = a[r++];
        }
    }
    if (r == n + 1)
    { //なくなったら残りを全部入れる
        while (l < h + 1)
        {
            printf("\n");
            another[an_i++] = a[l++];
        }
    }
    while (m != n + 1)
    { // aに入れ直し
        a[m] = another[m];
        m++;
    }
    printf("n = %d\nm = %d\n",n,m);
}

void merge_sort(struct point a[], int m, int n)
{
    int h;
    if (m < n)
    {
        h = (m + n) / 2;
        printf("1\n");
        printf("1 before h = (%d + %d) = %d\n",m,n,h);
        print_arr(a);
        printf("\n");
        printf("in merge_sort(a, %d, %d)\n",m,h);
        merge_sort(a, m, h);
        printf("1 after h = (%d + %d) = %d\n",m,n,h);

        printf("2\n");
        printf("2 before h = (%d + %d) = %d\n",m,n,h);
        print_arr(a);
        printf("\n");
        printf("in merge_sort(a, %d, %d)\n",h+1,n);
        merge_sort(a, h + 1, n);
        printf("2 after h = (%d + %d) = %d\n",m,n,h);
        merge(a, m, n, h);
        printf("fin\n");
    }
    else printf("m >= n なんだよ\n\n");
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
    merge_sort(arr, 0, n - 1);
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
            if (p1.x> p2.x)
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
        int len_1 = p1.x * p1.x + p1.y * p1.y, len_2 = p2.x* p2.x + p2.y * p2.y;
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
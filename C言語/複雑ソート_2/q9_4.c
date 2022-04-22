//バケツソート
#include <stdio.h>

struct point
{
    int x, y;
};

void bucket_sort(struct point a[], int n)
{
    /* ※ここを適切なプログラムで埋める*/
    int c[100] = {};
    struct point b[n];
    // printf("c[23] = %d\n",c[23]);
    for (int i = 0; i < n; i++)
    {
        ++c[a[i].x];
        b[i] = a[i];
    }
    for (int i = 1; i < 100; i++)
    {
        c[i] += c[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        --c[b[i].x];
        a[c[b[i].x]] = b[i];
    }
}

int main()
{
    char buf[128];
    struct point p, arr[128];
    int i = 0, n;
    while (fgets(buf, sizeof(buf), stdin) != NULL && i < 128)
    {
        sscanf(buf, "%d %d", &p.x, &p.y);
        arr[i] = p;
        ++i;
    }
    n = i;
    bucket_sort(arr, n);
    for (i = 0; i < n; ++i)
        printf("%d %d\n", arr[i].x, arr[i].y);
    return 0;
}
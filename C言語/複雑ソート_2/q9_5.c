//基数ソート
#include <stdio.h>

struct point
{
    int x, y;
};

int kajo(int r, int i);
void print_arr(struct point *q, int n);
void radix_sort(struct point a[], int n, int r, int dmax)
{
    // int c[kajo(2, r)];
    //printf("kajo(2,3) = %d\n",kajo(2,3));
    

    // printf("rad[4] = %d\n",rad[4]);
    // printf("a\n\n");
    for (int i = 0; i < dmax; i++)
    {
        struct point b[128];
        // printf("aa\n\n");
        int c[1025] = {};
        // aのコピー
        // printf("c[4] = %d\n", c[4]);
        for (int j = 0; j < n; j++)
        {
            c[(a[j].x >> (i * r)) & ((1 << r) - 1)]++;
            
            b[j] = a[j];
        }
        for (int j = 1; j <= kajo(2, r); j++)
        {
            // printf("aaaaa\n\n");
            c[j] += c[j - 1];
            //printf("c[%d] = %d\n", j, c[j]);
        }
        for (int j = n - 1; j >= 0; j--)
        {
            // printf("aaaaaa\n\n");
            int l = (b[j].x >> (i * r)) & ((1 << r) - 1);
            --c[l];
            a[c[l]] = b[j];
        }
        for (int j = 0; j < n; j++)
        {
            printf("%d %d\n", a[j].x, a[j].y);
        }
        printf("--\n");
    }
}

int main()
{
    char buf[128];
    struct point p, arr[128];
    int i = 0, n, r, dmax;
    scanf("%d %d ", &r, &dmax);

    while (fgets(buf, sizeof(buf), stdin) != NULL && i < 128)
    {
        sscanf(buf, "%d %d", &p.x, &p.y);
        arr[i] = p;
        // printf("arr[%d] = %d %d\n", i, arr[i].x, arr[i].y);
        ++i;
    }
    n = i;
    // print_arr(arr, n);
    // printf("arr[0] = %d %d\n", arr[0].x, arr[0].y);
    radix_sort(arr, n, r, dmax);
    return 0;
}

int kajo(int r, int i)
{
    int ans = 1;
    for (int j = 1; j <= i; j++)
    {
        ans *= r;
    }
    return ans;
}

void print_arr(struct point *q, int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d %d\n", q[i].x, q[i].y);
}
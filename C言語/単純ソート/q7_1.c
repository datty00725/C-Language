//最大値探索
#include <stdio.h>

int max_index(int a[], int n)
{
    int max = a[0], elem = 0;
    /* ※ここを適切なプログラムで埋める*/
    for (int i = 0; i < n; i++)//最大要素を求める
    {
        if(max <= a[i]){
            max = a[i];
        }
    }
    //printf("max = %d\n",max);
    for(int j = 0; j < n; j++){//同じ最大値を持つ要素が来たとき、末尾に近い方を保存できるようにした。
        if(max == a[j]){
            elem = j;
        }
    }
    return elem;
}

int main()
{
    char buf[128];
    int arr[128], i = 0;
    while (fgets(buf, sizeof(buf), stdin) != NULL && i < 128)
        sscanf(buf, "%d", &arr[i++]);
    printf("%d\n", max_index(arr, i));
    return 0;
}
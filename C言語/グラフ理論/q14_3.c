//、辺の集合(羅列) として与えられたグラフに対する隣接行列表現を求める
#include <stdio.h>
#include <stdlib.h>
char buf[256];

int main()
{
    int ekisu;
    scanf("%d ", &ekisu);
    int adjmat[ekisu][ekisu]; /* ← 隣接行列を表す 2次元配列 */
    /* ※ここを適切なプログラムで埋める */
    int a, b, i = 0, j = 0;
    for (i = 0; i < ekisu; i++)//初期化
    {
        for (j = 0; j < ekisu; j++)
        {
            adjmat[i][j] = 0;
        }
    }
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        sscanf(buf, "%d:%d", &a, &b);
        adjmat[a][b] = 1;
        adjmat[b][a] = 1;
    }
    for (i = 0; i < ekisu; i++)
    {
        for (j = 0; j < ekisu; j++)
        {
            printf("%d", adjmat[i][j]);
        }
        printf("\n");
    }
    return 0;
}
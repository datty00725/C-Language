#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SETMAX 10600
char buf[256];

struct station
{
    int eki;
    char name[64], rosen[64];
};

int main()
{
    struct station *ekidata[SETMAX], *st;
    int i = 0, ekisize, l, r, m;

    char ekiname[64];
    FILE *fp = fopen("./ekisen.txt", "r");
    while (fgets(buf, sizeof(buf), fp) != NULL && i < SETMAX)
    {
        st = (struct station *)malloc(sizeof(struct station));
        sscanf(buf, "%[^:]:%d:%[^\n]*c", st->name, &st->eki, st->rosen);
        ekidata[i] = st;
        ++i;
    }
    fclose(fp);
    ekisize = i;
    scanf("%[^\n]%*c", ekiname);
    l = 0;
    r = ekisize - 1;
    /* ここから二分探索木 */
    while (l <= r)
    {
        /* ※ここを適切なプログラムで埋める */
        m = (l + r) / 2;

        if (strcmp(ekiname, ekidata[m]->name) == 0)
        {
            break;
        }
        else if (strcmp(ekiname, ekidata[m]->name) < 0)
        {
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }
    if (r < l)
    { /* 駅名がない場合 */
        fprintf(stderr, "%s: 駅名がありません\n", ekiname);
        exit(1);
    }
    else
    { /* 駅名がある場合 */
        /* ※ここも適切なプログラムで埋める */
        while (strcmp(ekiname, ekidata[m]->name) == 0)
        {
            m--;
        }
        m++;
        while (strcmp(ekiname, ekidata[m]->name) == 0)
        {
            printf("%d:%s\n", ekidata[m]->eki, ekidata[m]->rosen);
            m++;
        }
    }
    return 0;
}

//表から最小値を削除する関数を作成
#include <stdio.h>
#define SETMAX 10600 /* 集合の要素数の最大値 (駅の数) */
char buf[256];       /* 入力された文字列を格納するグローバル変数 */

struct set
{
    int elements[SETMAX];
    int size;
};

typedef struct set *Pset;

int delete_min_int(struct set *p)
{
    /* ※ここを適切なプログラムで埋める */
    if (p->size == 0)
    {
        return -1;
    }
    else
    {
        int i = 0, min = p->elements[0];
        for (int j = 0; j < p->size; j++)
        {
            if (p->elements[j] < min)
            {
                min = p->elements[j];
                i = j;
            }
        }
        p->elements[i] = p->elements[p->size - 1];
        p->size -= 1;
        return min;
    }
}

void print_set(struct set *p)
{
    /* ※ここは問題 1 と同じ */
    int i;
    printf("{");
    for (i = 0; i < p->size; ++i)
        printf(" %d", p->elements[i]);
    printf(" }\n");
}

int main()
{
    struct set s; /* 入力される整数値を格納する集合 */
    int i, m;
    i = 0; /* 添字 0 から格納していく */
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        sscanf(buf, "%d ", &s.elements[i]); /* 入力された整数値を集合 s に格納 */
        ++i;                                /* 添字を 1 つ増やす */
    }
    s.size = i; /* ← この時点で i に要素の数が格納されているはず */
    while (1)
    {
        m = delete_min_int(&s);
        if (m < 0)
            break; /* m が負なら集合が空なので終了 */
        printf("%d : ", m);
        print_set(&s); /* 最小値と集合を出力 */
    }
    return 0;
}

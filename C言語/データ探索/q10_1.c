/*
与えられた数値と同じ得点をもつ学生のうち、学籍番号が最も若い(小さい) 学生の学籍番号と名前を出力
するプログラムを作成.

(1) n 番目に得点がS であるような構造体student (番兵(sentinel) という) を入れる。
(2) 配列のi 番目の学生の得点がS と異なる間、i に1 を足し続ける。
(3) (2) が終わった時点で、i がn であれば得点がS である学生が見つからなかったことになり、i < n で
あれば学生の得点がS である最初の学生がi 番目であることを表す。
*/

#include <stdio.h>

struct student
{
    int id;
    char name[32];
    int score;
};

int main()
{
    int i = 0, n, v;
    char buf[128], c;
    struct student st[1024];
    while (fgets(buf, sizeof(buf), stdin) != NULL && i < 1024)
    {
        sscanf(buf, "%d%c", &v, &c);
        if (c == ',')
        {
            st[i].id = v;
            sscanf(buf, "%*d,%[^,],%d", st[i].name, &st[i].score);
            ++i;
        }
    }
    n = i;
    /* この時点でv に探索すべき得点が入っていて、n が読み込んだ要素の数である*/
    /* ※ここを適切なプログラムで埋める*/
    /* for 文やwhile 文においてi<n のような添字による終了判定をしないこと*/
    int k = 0;
    st[n].score = v;
    while (st[k].score != v)
    {
        k++;
    }
    if (k == n)
    { 
        printf("Not found.\n");
    }
    else if (k < n)
    {
        printf("%d,%s", st[k].id, st[k].name);
    }
    return 0;
}
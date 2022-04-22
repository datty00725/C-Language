//学生の名前と得点のデータから学生の合計点を出力するプログラムを作成。

#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 関数strcmp を使うために必要*/
#define SIZE 101

struct student
{
    char name[32];
    int score;
};

struct node
{
    struct student data;
    struct node *next;
};

typedef struct student elementtype;
typedef struct node *list;

list makelist();                    //後々dataについてもmallocが必要になるかも。
list cons(elementtype e, list l);   // eを要素とするノードをlの頭に付ける
void insert(elementtype e, list l); // eを要素とするnodeをlの次に挿入する
list serch_tail();                  // lのお尻を探す
void print_table(list table[]);

int hash(char *s)
{
    /* ※ここは問題3 と同じ*/
    int sum = 0, i = 0;
    while (s[i] != '\0')
    {
        sum = (sum * 128 + (int)s[i++]) % SIZE;
    }
    return sum;
}

void set_data(struct node *table[], struct student st)
{
    /* ※ここを適切なプログラムで埋める*/
    int where = hash(st.name);
    // printf("what is where = %d\n", where);
    if (!table[where]) // table[where]そのものがNULLであることに注意
    {
        table[where] = makelist();
        table[where]->data = st;
    }
    else
    {
        insert(st, serch_tail(table[where])); //新しい要素を一番後ろに付ける必要がある。
    }
}

void renewal(list table[], elementtype st)
{
    // printf("st.name = %s\n", st.name);
    int where = hash(st.name);
    // printf("a\n");

    if (!table[where]) //要素がなかったらかまわずset_data
    {
        // printf("aa\n");
        set_data(table, st);
    }
    else //要素があったらちょっと考える
    {
        // printf("aaa\n");
        int flag = 0; //同一生徒がいたかを記憶
        list q;
        q = table[where];
        while (table[where])
        {

            if (!strcmp(st.name, table[where]->data.name))
            {
                // printf("aaaaa\n");
                table[where]->data.score += st.score;
                flag = 1;
            }
            // printf("aaaa\n");
            table[where] = table[where]->next;
        }
        table[where] = q;
        if (flag == 0) // table[where]が空ではないが同一生徒がいなかった場合。
        {
            // printf("b\n");
            set_data(table, st);
        }
    }
}

int main()
{
    int i;
    char buf[128];
    struct student st;
    struct node *table[SIZE];

    for (i = 0; i < SIZE; ++i)
        table[i] = NULL;
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        // printf("a\n");
        sscanf(buf, "%[^,],%d", st.name, &st.score);
        // printf("%s\n", st.name);
        // printf("%d\n", hash(st.name));
        renewal(table, st);
    }

    // print_table(table);

    for (i = 0; i < SIZE; ++i)
    {
        list p = table[i];
        while (p != NULL)
        {
            st = p->data;
            printf("%s,%d\n", st.name, st.score);
            p = p->next;
        }
    }
    return 0;
}

list makelist()
{
    list l;
    // elementtype *s = (elementtype *)malloc(sizeof(elementtype));
    l = (list)malloc(sizeof(struct node));
    // l->data = *s;
    l->next = NULL;
    return l;
}

list cons(elementtype e, list l)
{
    list q;
    q = makelist();
    q->data = e;
    q->next = l;
    return q;
}

void insert(elementtype e, list l)
{
    l->next = cons(e, l->next);
}

list serch_tail(list l)
{
    list p = l;

    while (p->next != NULL)
    {
        p = p->next;
    }

    return p;
}

void print_table(list table[])
{

    for (int j = 0; j < SIZE; j++)
    {
        list p = table[j];
        if (!p)
        {
            printf("table[%d] is NULL.\n", j);
        }
        else
        {
            printf("table[%d]", j);

            while (p)
            {
                printf(" - %s ", p->data.name);
                p = p->next;
            }
            printf("\n");
        }
    }
}
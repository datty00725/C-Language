//ハッシュ表を用いて特定の名前の学生の情報を見つけ出す。
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 関数strcmp を使うために必要*/
#define SIZE 101

struct student
{
    int id;
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

list makelist();//後々dataについてもmallocが必要になるかも。
list cons(elementtype e, list l);

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
    //printf("what is where = %d\n", where);
    if (!table[where])//table[where]そのものがNULLであることに注意
    {
        table[where] = makelist();
        table[where]->data = st;
    }
    else
    {
        table[where] = cons(st, table[where]);
    }
}

int find_score(struct node *table[], char *s)
{
    /* ※ここを適切なプログラムで埋める*/
    int where = hash(s);
    if(!table[where]){
        return -1;
    }
    while(table[where]){
        if(!strcmp(s,table[where]->data.name)){
            return table[where]->data.score;
        }
        table[where] = table[where]->next;
    }
    return -1;
}

int main()
{
    int i, v;
    char buf[128], name[32];
    struct student st;
    struct node *table[SIZE];

    for (i = 0; i < SIZE; ++i)
        table[i] = NULL;
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        sscanf(buf, "%d,", &v);
        /* 各行の最初の数値によって分岐*/
        if (v > 0)
        {
            sscanf(buf, "%d,%[^,],%d", &st.id, st.name, &st.score);
            set_data(table, st);
        }
        else
            sscanf(buf, "0,%[^,\n]", name);
    }
    v = find_score(table, name);
    if (v < 0)
        printf("Not found.\n"); /* Not found */
    else
        printf("%d\n", v);
    return 0;
}

list makelist()
{
    list l;
    //elementtype *s = (elementtype *)malloc(sizeof(elementtype));
    l = (list)malloc(sizeof(struct node));
    //l->data = *s;
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
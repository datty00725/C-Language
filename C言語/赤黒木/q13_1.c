//赤黒木の回転を行う2 つの関数rotate_right、rotate_left を定義
#include <stdio.h>
#include <stdlib.h>
char buf[128];

struct student
{
    int id;
    char name[32];
    int score;
};
typedef struct student datatype; /* ← 格納するデータは構造体student */
struct rb_node
{
    datatype data;
    struct rb_node *left, *right;
    int black;
};
typedef struct rb_node *Prb_node;

Prb_node nod(Prb_node t);

struct rb_node *get_rbtree()
{
    /* ※ここは問題1 と同じ*/
    struct rb_node *t;
    char c;
    /* ドットだけなら葉(NULL) を返す*/
    if (fgets(buf, sizeof(buf), stdin) == NULL || buf[0] == '.')
        return NULL;
    else
    {
        /* ドットでなければ節点を表す構造体のアドレスt を用意*/
        t = (struct rb_node *)malloc(sizeof(struct rb_node));
        /* 色を表す文字をc に、学籍番号、名前、得点をt->data に格納*/
        sscanf(buf, "[%c]%d,%[^,],%d", &c, &t->data.id, t->data.name, &t->data.score);
        /* 色の文字がb なら1、r なら0 */
        t->black = (c == 'b');
        /* 左の子をt->left に、右の子をt->right に格納*/
        t->left = get_rbtree();
        t->right = get_rbtree();
        /* t を返す*/
        return t;
    }
}

struct rb_node *rotate_right(struct rb_node *t)
{

    if (!t || !t->left)
    {
        return t;
    }
    else
    {
        Prb_node tem;
        tem = t->left;
        t->left = tem->right;
        tem->right = t;
        return tem;
    }
}

struct rb_node *rotate_left(struct rb_node *t)
{

    if (!t || !t->right)
    {
        return t;
    }
    else
    {
        Prb_node tem;
        tem = t->right;
        t->right = tem->left;
        tem->left = t;
        return tem;
    }
}

int is_red(struct rb_node *t)
{
    return (t != NULL && !t->black);
}

void print_rbtree(struct rb_node *t)
{
    if (t == NULL)
        printf(".\n");
    else
    {
        printf("[%c]%d,%s,%d\n", t->black ? 'b' : 'r', t->data.id, t->data.name, t->data.score);
        print_rbtree(t->left);
        print_rbtree(t->right);
    }
}

int main()
{
    char c;
    struct rb_node *t;
    scanf("%c ", &c);
    t = get_rbtree();
    if (c == 'R')
        t = rotate_right(t); /* R なら右回転*/
    else if (c == 'L')
        t = rotate_left(t); /* L なら左回転*/
    print_rbtree(t);
    return 0;
}

Prb_node nod(Prb_node t)
{
    // if (t)
    //{
    //     printf("node is %s,%d\n", t->data.name, t->data.id);
    // }
    return t;
}

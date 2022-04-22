//各学生の総得点を計算するために赤黒木のデータを更新する関数rb_update を定義
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

int rb_by_turns(Prb_node t);

Prb_node makelist();

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

struct rb_node *resolve_red_pair(struct rb_node *t)
{
    /* ※ここを適切なプログラムで埋める */
    if (is_red(t->left) && is_red(t->left->left)) // case1
    {
        // printf("1.1\n");
        if (is_red(t->right)) // case1.1
        {
            t->black = 0;
            t->left->black = t->right->black = 1;
        }
        else // case1.2
        {
            // printf("1.2\n");
            t = rotate_right(t);
            t->black = 1;
            t->right->black = 0;
        }
    }
    else if (is_red(t->left) && is_red(t->left->right)) // case2
    {
        if (is_red(t->right)) // case2.1
        {
            // printf("2.1\n");
            t->black = 0;
            t->left->black = t->right->black = 1;
        }
        else // case2.2
        {
            // printf("2.2\n");
            t->left = rotate_left(nod(t->left));
            t = rotate_right(nod(t));
            t->black = 1;
            t->right->black = 0;
        }
    }
    else if (is_red(t->right) && is_red(t->right->left)) // case3
    {
        if (is_red(t->left))
        {
            // printf("3.1\n");
            t->black = 0;
            t->right->black = t->left->black = 1;
        }
        else
        {
            // printf("3.2\n");
            t->right = rotate_right(t->right);
            t = rotate_left(t);
            t->black = 1;
            t->left->black = 0;
        }
    }
    else if (is_red(t->right) && is_red(t->right->right)) // case4
    {
        if (is_red(t->left))
        {
            // printf("4.1\n");
            t->black = 0;
            t->right->black = t->left->black = 1;
        }
        else
        {
            // printf("4.2\n");
            t = rotate_left(t);
            t->black = 1;
            t->left->black = 0;
        }
    }
    return t;
}

struct rb_node *rb_insert_rec(struct rb_node *t, struct student d)
{
    /* ※ここを適切なプログラムで埋める */
    if (!t)
    {
        t = makelist(); // notice black member is 0.
        t->data = d;
    }
    else
    {
        if (d.id < t->data.id)
        {
            t->left = rb_insert_rec(nod(t->left), d);
        }
        else
        {
            t->right = rb_insert_rec(nod(t->right), d);
        }
        t = resolve_red_pair(nod(t));
    }
    return t;
}

struct rb_node *rb_insert(struct rb_node *t, struct student d)
{
    t = rb_insert_rec(t, d);
    t->black = 1;
    return t;
}

Prb_node mitsukeru(Prb_node t, struct student d) {
    if (!t)
    {
        t = rb_insert_rec(nod(t), d);
    }
    else
    {
        if (d.id < t->data.id)
        {
            t->left = mitsukeru(nod(t->left), d);
        }
        else if (d.id > t->data.id)
        {
            t->right = mitsukeru(nod(t->right), d);
        }
        else
        {
            t->data.score += d.score;
        }
        t = resolve_red_pair(nod(t));
    }
    return t;
}

struct rb_node* rb_update(struct rb_node *t, struct student d) {
    t = mitsukeru(nod(t), d);
    t->black = 1;
    return t;
}
int main()
{
    struct rb_node *t = NULL; /* 葉のみの赤黒木を用意*/
    struct student d;
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        sscanf(buf, "%d,%[^,],%d", &d.id, d.name, &d.score); /* 学生の番号を読取り*/
        t = rb_update(t, d);                                 /* そのデータで赤黒木を更新*/
    }
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

Prb_node makelist()
{
    Prb_node l;
    l = (Prb_node)malloc(sizeof(struct rb_node));
    l->left = NULL;
    l->right = NULL;
    l->black = 0;
    return l;
}

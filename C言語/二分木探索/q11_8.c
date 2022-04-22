//ダミーの節点を利用した二分木探索。
#include <stdio.h>
#include <stdlib.h>
char buf[128];

struct student
{
    int id;
    char name[32];
    int score;
};
typedef struct student datatype;
struct node
{
    datatype data;
    struct node *left, *right;
};

typedef struct node *list;
list makelist();

void bst_insert(struct node *t, struct student d)
{
    struct node *a, *tem;
    a = t;
    tem = t; 
    while (a->left != a && a->right != a)
    {
        if (a->data.id > d.id)
        { 
            tem = a;
            a = a->left;
        }
        else
        {
            tem = a;
            a = a->right;
        }
    }
    //場所が把握できた。

    list exp = makelist();
    exp->data = d;
    exp->right = exp->left = a;

    if (tem->data.id > d.id)
    {
        tem->left = exp;
    }
    else
    {
        tem->right = exp;
    }
}


void print_bst_dummy(struct node *t, struct node *dummy)
{
    if (t == dummy)
        printf(".\n");
    else
    {
        printf("%d,%s,%d\n", t->data.id, t->data.name, t->data.score);
        print_bst_dummy(t->left, dummy);
        print_bst_dummy(t->right, dummy);
    }
    return;
}

void print_bst(struct node *t)
{
    print_bst_dummy(t->right, t->left);
    return;
}

void find_info(struct node *t, int id)
{
    t->left->data.id = id;
    t = t->right;
    while (t->data.id != id) //葉であるかで判定しない
    {
        if (t->data.id > id)
        {
            t = t->left;
        }
        else
        {
            t = t->right;
        }
    }
    //候補を見つけた
    if (t->left == t || t->right == t)
    {
        printf("Not found.");
    }
    else
    {
        printf("%s,%d", t->data.name, t->data.score);
    }
}

int main()
{
    char buf[128], c;
    int id;
    struct node *t = (struct node *)malloc(sizeof(struct node)),
                *dummy = (struct node *)malloc(sizeof(struct node));
    struct student st;
    t->left = t->right = dummy->left = dummy->right = dummy;
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        sscanf(buf, "%d%c", &id, &c);
        if (c == ',')
        {
            sscanf(buf, "%d,%[^,],%d", &st.id, st.name, &st.score);
            bst_insert(t, st);
        }
    }
    print_bst(t);
    find_info(t, id);
    return 0;
}

list makelist()
{
    list l;
    l = (list)malloc(sizeof(struct node));
    l->left = NULL;
    l->right = NULL;
    return l;
}

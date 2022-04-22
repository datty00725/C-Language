//サブルーチンで二分木探索に用いる機能を補完。

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

struct node *get_tree()
{
    struct node *t;
    if (fgets(buf, sizeof(buf), stdin) == NULL || buf[0] == '.')
    {
        return NULL;
    }
    else
    {
        t = (struct node *)malloc(sizeof(struct node));
        sscanf(buf, "%d,%[^,],%d", &t->data.id, t->data.name, &t->data.score);
        t->left = get_tree();
        t->right = get_tree();
        return t;
    }
}

void print_bst(struct node *t)
{
    if (t == NULL)
    {
        printf(".\n");
    }
    else
    {
        printf("%d,%s,%d\n", t->data.id, t->data.name, t->data.score);
        print_bst(t->left);
        print_bst(t->right);
    }
}

struct node *bst_delete(struct node *t, int id)
{
    struct node *p = t, *q = NULL; // p=root node, q=deleteするnodeのひとつ前
    //(1)tがdeleteの対象を指すまで繰り返す
    while (t->data.id != id)
    {
        q = t;
        if (t->data.id > id)
        {
            t = t->left;
        }
        else if (t->data.id < id)
        {
            t = t->right;
        }
    }
    //(2-1)tの右の子が葉であるとき
    if (t->right == NULL)
    {
        if (q == NULL)
        {
            p = t->left; //(i)deleteの対象がrootのとき
        }
        else if (q->left == t)
        {
            q->left = t->left; //(ii)deleteの対象が親の左の子であるとき
        }
        else
        {
            q->right = t->left; //(iii)deleteの対象が親の右の子であるとき
        }
    }
    //(2-2)tの右の子の左の子が葉であるとき
    else if (t->right->left == NULL)
    {
        if (q == NULL)
        {
            p = t->right;
            t->right->left = t->right; //(i)deleteの対象がrootのとき
        }
        else if (q->left == t)
        {
            q->left = t->right;
            q->left->left = t->left; //(ii)deleteの対象が親の左の子であるとき
        }
        else
        {
            q->right = t->right;
            q->right->left = t->left; //(iii)deleteの対象が親の右の子であるとき
        }
    }
    //(2-3)それ以外のとき
    else
    {
        struct node *r = t, *s;
        r = r->right;
        while (r->left != NULL)
        {
            s = r;
            r = r->left; //**deleteした後に繋ぎ変えるnodeを探す
        }
        if (q == NULL)
        {
            p = r;
        } //(i)deleteの対象がrootのとき
        else if (q->left == t)
        {
            q->left = r;
        } //(ii)deleteの対象が親の左の子であるとき
        else
        {
            q->right = r;
        } //(iii)deleteの対象が親の右の子であるとき
        s->left = r->right;
        r->left = t->left;
        r->right = t->right; // deleteの対象が二分木から外し、**のnodeに繋ぎ変える
    }
    free(t);  // deleteの対象のnodeを開放
    return p; // rootを返す
}

int main()
{
    int id;
    struct node *t = get_tree();
    scanf("%d ", &id);
    t = bst_delete(t, id);
    print_bst(t);
    return 0;
}
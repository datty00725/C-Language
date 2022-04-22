//与えられた二分探索木が赤黒木であるかどうか判定する関数is_rbtree を定義
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

int turn(Prb_node t);

int jou2(Prb_node t);

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

int is_rbtree(struct rb_node *t)
{
    int num, l, r;
    if (!t)
    {
        return 1;
    }
    else
    {
        if (is_red(t))
        {
            if ((t->right && is_red(t->right)) || (t->left && is_red(t->left)))
            {
                return 0;
            }
        }

        l = is_rbtree(t->left);
        r = is_rbtree(t->right);
        if (l == 0 || r == 0 || l != r){ return 0; }

        num = l;
        if (!is_red(t)){ num++; }
        return num;
    }
}

int main()
{
    struct rb_node *t = get_rbtree();
    // printf("all = %d/n", all_black(t));

    if (is_rbtree(t))
        printf("Yes.\n");
    else
        printf("No.\n");

    return 0;
}

Prb_node nod(Prb_node t)
{
    /*
     if (t)
    {
         printf("node is %s,%d,%d\n", t->data.name, t->data.id,t->black);
     }
     else{
         printf("null\n");
     }
     */
    return t;
}

/*
int kazoe(Prb_node t)
{
    if (!t)
    {
        //printf("1\n");
        return 1;
    }
    else
    {
        //printf("2\n");
        if (is_red(nod(t->left)))
        {
            //printf("3\n");
            kazoe(t->left);
        }
        else if (is_red(t->right))
        {
            //printf("4\n");
            kazoe(t->right);
        }
        else
        {
            //printf("5\n");
            int migi = kazoe(t->right);
            int hidari = kazoe(t->left);
            if (migi != hidari)
            {
                //printf("6\n");
                return 0;
            }
            else
            {
                //printf("7\n");
                printf("kazo_migi = %d\n", migi + 1);
                printf("kazo_hidari = %d\n", hidari + 1);
                return migi + 1;
            }
        }
    }
}
*/

/*
int rb_by_turns(Prb_node t) //右と左で黒の数は等しいか
{
    if (!t)
    {
        return 1;
    }
    else
    {
        int migi = kazoe(t->right);
        printf("in turn, migi = %d\n",migi);
        int hidari = kazoe(t->left);
        printf("in turn, hidari = %d\n",hidari);
        if (migi != hidari)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}
*/

int turn(Prb_node t)
{
    if (!t)
    {
        return 1;
    }
    else
    {
        int hidari = turn(t->left);
        int migi = turn(t->right);
        if (hidari != migi)
        {
            return 0;
        }
        if (!is_red(t))
        {
            migi++;
        }
        return migi;
    }
}

int jou2(Prb_node t)
{
    int flag = 1;
    if (is_red(t)) //条件2
    {
        // printf("sdf\n");
        //  Prb_node tem = t;
        //  tem = tem->left;
        if ((t->left && is_red(t->left)) || (t->right && is_red(t->right)))
        {
            // printf("here\n");
           flag = 0;
        }
        else
        {
            jou2(t->right);
            jou2(t->left);
        }
    }
    return flag;
}
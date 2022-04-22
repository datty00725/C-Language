//二分探索木に対してAVL 木を満たすように変形する関数balance を定義
#include <stdio.h>
#include <stdlib.h>

char buf[128]; /* 関数 get_avl で用いるグローバル関数 */

struct student
{
  int id;
  char name[32];
  int score;
};
typedef struct student datatype; /* ← 格納するデータは構造体 student */
struct avl_node
{
  datatype data;
  struct avl_node *left, *right;
  int height;
};

typedef struct avl_node *Pavl_node;

int height(struct avl_node *t);      // t = NULLの場合、tの高さを0にする関数
Pavl_node nod(Pavl_node t);          //要素を確認(デバック用)
void put_height(struct avl_node *t); //高さの調整をする

struct avl_node *get_avl()
{
  /* ※ここは先述したとおり書けば良い */
  struct avl_node *t;
  /* ドットだけなら葉 (NULL) を返す */
  if (fgets(buf, sizeof(buf), stdin) == NULL || buf[0] == '.')
    return NULL;
  else
  {
    /* ドットでなければ接点を表す構造体のアドレス t を用意 */
    t = (struct avl_node *)malloc(sizeof(struct avl_node));
    /* 高さを t->height に、学籍番号、名前、得点を t->data に格納 */
    sscanf(buf, "[%d]%d,%[^,],%d", &t->height, &t->data.id, t->data.name, &t->data.score);
    /* 左の子を t->left に、右の子を t->right に格納 */
    t->left = get_avl();
    t->right = get_avl();
    /* t を返す */
    return t;
  }
}

struct avl_node *rotate_right(struct avl_node *t)
{
  /* ※ここを適切なプログラムで埋める */
  struct avl_node *p;
  if (!t->left)
    return t;
  else
  { //付け替えは題意の通り
    p = t->left;
    t->left = p->right;
    p->right = t;
    put_height(p);
    return p;
  }
}

struct avl_node *rotate_left(struct avl_node *t)
{
  /* ※ここも適切なプログラムで埋める */
  struct avl_node *p;
  if (!t->right)
    return t;
  else
  {
    p = t->right;
    t->right = p->left;
    p->left = t;
    put_height(p);
    return p;
  }
}

struct avl_node *balance(struct avl_node *t)
{
  /* ※ここを適切なプログラムで埋める*/

  if (abs(height(t->left) - height(t->right)) <= 1) //差が1の時
  {
    // printf("1\n");
    return t;
  }
  else if (height(t->left) - height(t->right) == 2)
  {
    // printf("2\n");
    Pavl_node tem = nod(t->left);
    if (height(tem->left) >= height(tem->right))
    {
      // printf("3\n");
      t = rotate_right(nod(t)); //そのまま右回転
    }
    else
    {
      // printf("4\n");
      t->left = rotate_left(nod(tem)); //一旦左回転
      t = rotate_right(nod(t));
    }
  }
  else
  {
    // printf("5\n");
    Pavl_node tem = t->right;
    if (height(tem->right) >= height(tem->left))
    {
      // printf("6\n");
      t = rotate_left(t);
    }
    else
    {
      // printf("7\n");
      t->right = rotate_right(tem);
      t = rotate_left(t);
    }
  }
  put_height(t);
  return t;
}

void print_avl(struct avl_node *t)
{
  if (!t)
  {
    printf(".\n");
  }
  else
  {
    printf("[%d]%d,%s,%d\n", t->height, t->data.id, t->data.name, t->data.score);
    print_avl(t->left);
    print_avl(t->right);
  }
}

int main()
{
  /* 厳密にいえば入力はAVL 木とは限らないが、関数get_avl で入力の木を作れる*/
  struct avl_node *t = get_avl();
  t = balance(t);
  print_avl(t);
  return 0;
}

int height(struct avl_node *t)
{
  if (!t)
  {
    return 0;
  }
  else
  {
    return t->height;
  }
}

Pavl_node nod(Pavl_node t)
{
  // if (t)
  //{
  //     printf("node is %s,%d\n", t->data.name, t->data.id);
  // }
  return t;
}

void put_height(struct avl_node *t)
{
  if (height(t) < height(t->right))
  {
    if (height(t->right->left) >= height(t->right->right))
    {
      // printf("12\n");
      t->right->height = height(nod(t->right->left)) + 1;
    }

    else
    {
      // printf("13\n");
      t->right->height = height(nod(t->right->right)) + 1;
    }
    if (height(t->left) >= height(t->right))
    {
      // printf("14\n");
      t->height = height(nod(t->left)) + 1;
    }
    else
    {
      // printf("15\n");
      t->height = height(nod(t->right)) + 1;
    }
  }
  else
  {
    if (height(t->left->left) >= height(t->left->right))
    {
      // printf("16\n");
      t->left->height = height(nod(t->left->left)) + 1;
    }
    else
    {
      // printf("17\n");
      t->left->height = height(nod(t->left->right)) + 1;
    }
    if (height(t->left) >= height(t->right))
    {
      // printf("18\n");
      t->height = height(nod(t->left)) + 1;
    }
    else
    {
      // printf("19\n");
      t->height = height(nod(t->right)) + 1;
    }
  }
}
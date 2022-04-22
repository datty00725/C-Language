/*
標準入力で与えられる整数n に対し、フィボナッチ数列のn 番めFn を2718 で割った余りを標準出力に
出力するプログラム
*/

#include <stdio.h>
struct golden
{
    long long int a;
    long long int b;
};

#define N 2718



/* mult_golden: 第1引数と第2引数の積を返す関数*/


struct golden mult_golden(struct golden x, struct golden y)
{
    struct golden z;
   
   
    z.a = (((x.a * y.a) > 0 ? x.a * y.a : N + x.a * y.a ) % N + ((x.b * y.b) > 0 ? x.b * y.b : N + x.b * y.b ) % N) % N;
    z.b = (((x.b * y.b) > 0 ? x.b * y.b : N + x.b * y.b ) % N + ((x.b * y.a) > 0 ? x.b * y.a : N + x.b * y.a ) % N + ((x.a * y.b) > 0 ? x.a * y.b : N + x.a * y.b ) % N) % N;
   
    return z;
}


/*
struct golden mult_golden(struct golden x, struct golden y) { //こっちの方が可読性が高い
  struct golden z;
  z.a = (x.a * y.a + x.b * y.b + N) % N;
  z.b = (x.a*y.b + x.b*y.a + x.b*y.b + N) % N;
  return z;
}
*/

/* power_golden: 第1引数の第2引数乗を返す関数*/
struct golden power_golden(struct golden x, int n)
{
    struct golden z;

    /* ここは適切に埋める*/
    if (n == 0)
    {
        z.a = 1;
        //printf("%lld\n",-x.a);
        z.b = 0;
        return z;
    }
    if (n % 2 == 1)
    {
        
        return mult_golden(x, power_golden(x, --n));
    }
    else
    {
        z = power_golden(x, n / 2);
        return mult_golden(z,z);
    }
}

int main(){
    struct golden x;
    int n;
    scanf("%d", &n);
    x.a = 1;
    x.b = -1;
    x = power_golden(x, n - 1);
    printf("%lld\n",x.a);
    return 0;
}
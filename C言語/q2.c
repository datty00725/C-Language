/*
標準入力から与えられた複数行の文字列に対応する図形を標準出力に描画するプログラムです。
入力の各行には0 個以上の数字が空白文字で区切られた文字列a1; a2; : : : ; an が与えられ、それに対する出力では、同じ行のa1 番
目、a2 番目、. . . 、an 番目の文字が`#'、それ以外が空白となっていることとします。
ただし、先頭の文字は0 番目であり、各行において最後の`#' の直後は改行するものとし、数字が何も含まれない行は改行のみを出力します。
なお、入力の各行の文字列は128 文字以下であり、各整数値は80 以下であると仮定しています。

以下入力例です。
--------------------------------------------------------------------------------------------------------
2 3 4 5 6 12 13 14 26 27 28
1 2 5 6 7 11 12 14 15 25 28 29
6 7 11 15 20 24 25 29
6 7 10 11 15 16 19 20 24 25 29 30
7 10 11 15 16 19 20 24 25 29 30
7 8 10 11 16 19 20 23 24 29 30
7 8 10 11 16 19 20 23 24 29 30
7 8 9 10 11 16 17 19 20 23 24 29 30
6 7 9 10 11 16 17 19 20 23 24 29 30
6 7 9 10 11 16 17 19 20 24 25 29 30
5 6 7 9 10 11 16 17 19 20 24 25 29 30
4 5 6 9 10 11 16 17 19 20 24 25 28 29 30
4 5 9 10 11 16 17 19 20 25 26 27 29 30
3 4 9 10 11 16 17 19 20 29 30
3 10 11 16 19 20 29 30
2 10 11 16 19 20 29 30
2 10 11 15 16 19 20 29 30
1 8 10 11 15 16 19 20 29 30
1 2 3 4 5 6 7 11 15 19 20 29
1 2 3 4 5 6 7 12 14 15 19 20 24 25 28 29
0 1 2 3 4 5 6 7 13 18 19 20 21 26 27
----------------------------------------------------
上記出力
----------------------------------------------------
 #####     ###           ###
 ##  ###   ## ##         #  ##
      ##   #   #    #   ##   #
      ##  ##   ##  ##   ##   ##
       #  ##   ##  ##   ##   ##
       ## ##    #  ##  ##    ##
       ## ##    #  ##  ##    ##
       #####    ## ##  ##    ##
      ## ###    ## ##  ##    ##
      ## ###    ## ##   ##   ##
     ### ###    ## ##   ##   ##
    ###  ###    ## ##   ##  ###
    ##   ###    ## ##    ### ##
   ##    ###    ## ##        ##
   #      ##    #  ##        ##
  #       ##    #  ##        ##
  #       ##   ##  ##        ##
 #      # ##   ##  ##        ##
 #######   #   #   ##        #
 #######    # ##   ##   ##  ##
########     #    ####    ##
----------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAXLEN 128
char moji[MAXLEN + 2];

int main(void)
{

    while (fgets(moji, sizeof(moji), stdin) != NULL)
    {
        char *iremono;
        iremono = (char *)malloc(sizeof(moji));
        iremono = moji;
        char *show;
        show = (char *)malloc(sizeof(moji)); //#を入れるchar配列.
        
        for (int i = 0; i < sizeof(moji); i++)
        {
            show[i] = 0; //show配列の初期化
        }
        int i;

        if (sscanf(iremono, "%d", &i) == EOF)
        {
            printf("\n");
        }
        else
        {
            while (sscanf(iremono, "%d", &i) != EOF)
            {
                show[i] = '#';
                iremono = strchr(iremono, ' '); // iremonoを次の空白の場所に移動
                if (iremono == NULL)
                {
                    break; // 空白が見つからなければ終了
                }
                else
                {
                }
                while (*iremono == ' ')
                {
                    ++iremono; // 見つかったら空白でなくなる位置まで移動
                }
            }

            for (int j = 0; j <= i; j++)
            {
                if (show[j] == '#')
                {
                    printf("%c", show[j]);
                }
                else
                {
                    printf(" ");
                }
            }

            printf("\n");
            free(iremono);
            free(show);
        }
    }

    return 0;
}
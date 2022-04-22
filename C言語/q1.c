/*
10個の数字を配列に格納。そのあとそれらの最小値を求めるプログラムです。
*/

#include <stdio.h>
#include <stdlib.h>


int main(void){
    int a[10];

    scanf("%d%d%d%d%d%d%d%d%d%d",&a[0],&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7],&a[8],&a[9]);

    int max = a[0];
    //serch max
    for(int i = 0; i < 10; i++){
        if(max < a[i]){
            max = a[i];
        }
    }
    //printf("aaa %d aaa\n",max);
    int min_1 = max, min_2 = max;

    //serch second min
    for(int i = 0; i < 10; i++){
        if(min_1 >= a[i]){
            min_2 = min_1;
            min_1 = a[i];
        }
        else if((min_1 < a[i]) && (min_2 > a[i])){
            min_2 = a[i];
        }
        
    }
    printf("%d\n",min_2);
    return 0;
}
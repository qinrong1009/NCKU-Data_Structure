#include<stdio.h>
#include<stdlib.h>

#define MAXN 105

int a[MAXN][MAXN];

//全域陣列 會自己初始化為零

void function(){
    a[1][1]=1;
}

// void test(int array[]){
//     printf("%d",array[0]);
// }

// void test(int *array){
//     printf("%d",array[0]);
// }

// void test(int array[2][3]){
//     printf("%d",array[0][0]);
// }

// void test(int **array){
//     printf("%d",array[0]);
// }

int main(){
    int num = 2;
    int oneDimArray[2] = {0};//or = {1,2}一維陣列直接宣告一定要宣告大小或全部元素
    int *oneDimArray2 = (int*)malloc(num * sizeof(int));//陣列就是起始位置的位置 所以要用指標型態宣告（malloc回傳的是這串空間的起始位置）

    int twoDimArray[2][3] = {0};//不能都不給大小只宣告元素 二維陣列不管宣告還是參數都只能省略前面的大小 後面一定要宣告
    int **twoDimArray2 = (int**)malloc(num*sizeof(int*));
    for (int i = 0; i < num; i++)
    {
        twoDimArray2[i] = (int*)malloc(3*sizeof(int));
    }
    //*是宣告該變數為指標變數 陣列本來就是位置[] 所以不管一維二維動態宣告完 使用都不用加*

    /*參數*/
    // oneDimArray[0] = 1;
    // test(oneDimArray);
    //一維的陣列傳指標跟整個陣列都可以 不論直接宣告或動態

    // twoDimArray[0][0] = 1;
    // test(twoDimArray);
    //直接宣告二維只能直接傳 因為他是一個指標 一連串的位置 要指標要自己算位置

    // twoDimArray2[0][0] = 1;
    // test(twoDimArray2);
    //動態宣告二維只能直接傳指標 因為malloc column不連續
    function();
    printf("%lld", a[1][1]);
    
    free(oneDimArray2);
}
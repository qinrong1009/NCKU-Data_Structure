#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[]){
    char string[101];
    int n = scanf("%s",string);
    int check[101];
    int length = strlen(string);
    int isNotFinish = 1;
    for(int i = 0; i<length; i++){
        if(string[i] < 'A' || (string[i] > 'Z' && string[i] < 'a') || string[i] > 'z'){
            check[i] = 0;
        }else{check[i] = i;}
    }
    while (isNotFinish)
    {
        for (int i = length - 1; i >= 0; i--)
        {
            if((string[i] < 'A' || (string[i] > 'Z' && string[i] < 'a') || string[i] > 'z') && check[i] == 0){
                int firstIndex = i+1;
                if(string[firstIndex] < 'A' || (string[firstIndex] > 'Z' && string[firstIndex] < 'a') || string[firstIndex] > 'z'){continue;}
                int tmp = firstIndex + 1;
                while(1){
                    if(check[tmp] != check[firstIndex]){break;}
                    tmp++;
                }
                if(check[tmp] == 0){continue;}
                int secondIndex = tmp;
                tmp = secondIndex + 1;
                int endIndex;
                if(tmp >= length){endIndex = secondIndex;}
                else{
                    while(1){
                        if(tmp >= length){break;}
                        if(check[tmp] != check[secondIndex]){break;}
                        tmp++;
                    }
                    endIndex = tmp - 1;
                }
                for(int ch = i ; ch <= endIndex; ch++){
                    check[ch] = check[firstIndex];
                }
                char temp = string[i];
                for(int ch = i ; ch < secondIndex - 1; ch++){
                    string[ch] = string[ch+1];
                }
                string[secondIndex - 1] = temp;
            }
        }
        int tmp = 1;
        while(1){
            if(tmp >= length){break;}
            if(check[tmp] != check[0]){break;}
            tmp++;
        }
        if(tmp >= length){isNotFinish = 0;}
        // printf("%s",string);
        // for (int j = 0; j < length; j++)
        // {
        //     printf("%d ",check[j]);
        // }
        // printf("\n");
    }
    printf("%s\n",string);
}
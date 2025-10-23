#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[]){
    char string[101];
    int n = scanf("%s",string);
    char check[101];
    strcpy(check,string);
    int length = strlen(string);
    for (int i = 0; i < length; i++)
    {
        if(check[i] == '*' || check[i] == '/'){
            int tmp = i - 1;
            while(1){
                if(tmp <= 0){break;}
                if(check[tmp] != check[i - 1]){break;}
                tmp--;
            }
            int firstIndex;
            if(tmp <= 0){firstIndex = 0;}
            else{firstIndex = tmp + 1;}
            tmp = i + 1;
            while(1){
                if(tmp >= length){break;}
                if(check[tmp] != check[i + 1]){break;}
                tmp++;
            }
            int endIndex;
            if(tmp >= length){endIndex = length - 1;}
            else{endIndex = tmp - 1;}
            for(int j = firstIndex; j <= endIndex; j++){
                check[j] = string[firstIndex];
            }
            char temp = string[i];
            for (int j = i; j < endIndex; j++)
            {
                string[j] = string[j+1];
            }
            string[endIndex] = temp;
        }
    }
    int isNotFinish = 1;
    while(1){
        int tmp = 1;
        while(1){
            if(tmp >= length){break;}
            if(check[tmp] != check[0]){break;}
            tmp++;
        }if(tmp >= length){break;}
        int countIndex = tmp;
        tmp++;
        while(1){
            if(tmp >= length){break;}
            if(check[tmp] != check[countIndex + 1]){tmp -= 1; break;}
            tmp++;
        }if(tmp >= length){tmp = length - 1;}
        int endIndex = tmp;
        for(int i = 0; i<= endIndex; i++){
            check[i] = check[0];
        }
        char temp = string[countIndex];
        for (int i = countIndex; i < endIndex; i++)
        {
            string[i] = string[i+1];
        }
        string[endIndex] = temp;

        tmp = 1;
        while(1){
            if(tmp >= length){break;}
            if(check[tmp] != check[0]){break;}
            tmp++;
        }
        if(tmp >= length){isNotFinish = 0;}
        // printf("%s %s\n",string, check);
    }

    printf("%s",string);
}
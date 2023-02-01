#include <stdio.h>
#include <string.h>

constexpr unsigned long long MAX_LEN = 100000;


void mul(int digits[35000]){
    for(int i=0; i<6; ++i){
        for(int j=0; j<35000; ++j){
            digit[j] *= 63;
        }
        for(int j=0; j<35000; ++j){
            if(digit[j] >= 10){
                digit[j+1] += digit[j] / 10;
                digit[j] %= 10;
            }
        }
    }
}

int* hashF(char str[5*MAX_LEN+1], int size){
    int digits[35000];
    for(int i=0; i<35000; ++i){
        digits[i] = 0;
    }

    for(int i=0; i<size; ++i){
        char c = str[i];
        int ic;
        if(c>='0' && c <= '9') ic = c-'0';
        else if(c>='a' && c <= 'z') ic = c-'a'+10;
        else ic = c-'A'+26;

        digits[i] = 
        
        hash = (hash << 6) + ic;
    }
    return hash;
}

int main(){
    freopen("input.txt", "r" ,stdin);
    int T;
    scanf("%d", &T);

    char str1[5*MAX_LEN+1];
    char str2[MAX_LEN+1];

    for(int test=1; test<=T; ++test){
        scanf("%s", str1);
        int size1 = strlen(str1);

        scanf("%s", str2);
        int size2 = strlen(str2);

        unsigned long long hash1 = hashF(str1, size2);
        unsigned long long hash2 = hashF(str2, size2);

        unsigned long long T1 = 1;
        for(int i=1; i<size2; ++i){
            T1 = (T1<<6);
        }

        int ans=0;
        for(int i=0; i<=size1-size2; ++i){
            if(hash1 == hash2){
                ans++;
            }

            char c = str1[i];
            int ic;
            if(c>='0' && c <= '9') ic = c-'0';
            else if(c>='a' && c <= 'z') ic = c-'a'+10;
            else ic = c-'A'+26;
            hash1 -= T1*ic;

            char c1 = str1[i+size2];
            int ic1;
            if(c1>='0' && c1 <= '9') ic1 = c1-'0';
            else if(c1>='a' && c1 <= 'z') ic1 = c1-'a'+10;
            else ic1 = c1-'A'+26;
            hash1 = (hash1 << 6) + ic1;
        }
        printf("#%d %d\n",test, ans);

    }
    return 0;
}

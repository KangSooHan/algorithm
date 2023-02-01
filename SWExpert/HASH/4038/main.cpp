#include <stdio.h>
#include <string.h>

constexpr unsigned long long MAX_LEN = 100000;

unsigned long long djb2(char str[5*MAX_LEN+1], int size){
    unsigned long long hash = 5381;
    for(int i=0; i<size; ++i){
        char c = str[i];
        int ic;
        if(c>='0' && c <= '9') ic = c-'0'+1;
        else if(c>='a' && c <= 'z') ic = c-'a'+11;
        else ic = c-'A'+37;
        
        hash = ((hash << 6) + hash) + ic;
    }
    return hash;
}

int main(){
   // freopen("input.txt", "r" ,stdin);
    int T;
    scanf("%d", &T);

    char str1[5*MAX_LEN+1];
    char str2[MAX_LEN+1];

    for(int test=1; test<=T; ++test){
        scanf("%s", str1);
        int size1 = strlen(str1);

        scanf("%s", str2);
        int size2 = strlen(str2);

        unsigned long long hash1 = djb2(str1, size2);
        unsigned long long hash2 = djb2(str2, size2);

        unsigned long long T1 = 1;
        for(int i=1; i<size2; ++i){
            T1 = (T1<<6) + T1;
        }
        unsigned long long T2 = ((T1<<6) + T1) * 5381;

        int ans=0;
        for(int i=0; i<=size1-size2; ++i){
            if(hash1 == hash2){
                ans++;
            }

            char c = str1[i];
            int ic;
            if(c>='0' && c <= '9') ic = c-'0'+1;
            else if(c>='a' && c <= 'z') ic = c-'a'+11;
            else ic = c-'A'+37;
            hash1 -= T2 + T1*ic;

            char c1 = str1[i+size2];
            int ic1;
            if(c1>='0' && c1 <= '9') ic1 = c1-'0'+1;
            else if(c1>='a' && c1 <= 'z') ic1 = c1-'a'+11;
            else ic1 = c1-'A'+37;
            hash1 = ((hash1 << 6) + hash1) + ic1 + T2;
        }
        printf("#%d %d\n",test, ans);

    }
    return 0;
}

#include <stdio.h>

void swap(int &a, int &b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}

class MaxHeap{
#define parent ( i >> 1 )
#define left ( i << 1 )
#define right ( i << 1 | 1)
    int pool[10002];
    int size;

public:
    void init(){
        size = 0;
    }

    void push(int data){
        pool[++size] = data;

        for(int i = size; parent != 0; i>>=1){
            if(pool[i] > pool[parent]){
                swap(pool[i], pool[parent]);
            }
            else{
                break;
            }
        }
    }
    int pop(){
        if(size == 0) return -1;
        int ret = pool[1];
        pool[1] = pool[size--];

        for(int i=1; left <= size;){
            if(pool[left] > pool[right]){
                if(pool[left] > pool[i]){
                    swap(pool[left], pool[i]);
                    i = left;
                }
                else break;
            }
            else{
                if(pool[right] > pool[i]){
                    swap(pool[right], pool[i]);
                    i = right;
                }
                else break;
            }
        }
        return ret;
    }
};

MaxHeap MH;

int main(){
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    for(int test=1; test<=T; ++test){
        MH.init();
        int N;
        scanf("%d", &N);
        printf("#%d", test);
        while(N--){
            int cmd;
            scanf("%d", &cmd);
            if(cmd == 1){
                int num;
                scanf("%d", &num);
                MH.push(num);
            }
            else{
                printf(" %d", MH.pop());
            }
        }
        printf("\n");
    }
}   
#include <stdio.h>

#define parent ( i >> 1 )
#define left ( i << 1 )
#define right ( i << 1 | 1)

void swap(int &a, int &b){ int temp; temp = a; a = b; b = temp;}

class MaxHeap{
    int pool[200010];
    int size;
public:
    void init(){
        size = 0;
    }

    void push(int data){
        pool[++size] = data;

        for(int i=size; parent!=0 && pool[parent] < pool[i]; i >>= 1){
            swap(pool[parent], pool[i]);
        }
    }

    int top(){
        return pool[1];
    }

    void pop(){
        pool[1] = pool[size--];

        for(int i=1; i<=left;){
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
    }
};

class MinHeap{
    int pool[200010];
    int size;
public:
    void init(){
        size = 0;
    }
    void push(int data){
        pool[++size] = data;

        for(int i=size; parent!=0 && pool[parent] > pool[i]; i >>= 1){
            swap(pool[parent], pool[i]);
        }
    }

    int top(){
        return pool[1];
    }

    void pop(){
        pool[1] = pool[size--];

        for(int i=1; i<=size;){
            if(pool[left] < pool[right]){
                if(pool[left] < pool[i]){
                    swap(pool[left], pool[i]);
                    i = left;
                }
                else break;
            }
            else{
                if(pool[right] < pool[i]){
                    swap(pool[right], pool[i]);
                    i = right;
                }
                else break;
            }
        }
    }
};

MaxHeap maxh;
MinHeap minh;

int main(){
    int T;
    freopen("input.txt","r", stdin);
    scanf("%d", &T);

    for(int test=1; test<=T; ++test){
        int N, A;
        scanf("%d %d", &N, &A);
        int middle = A;
        int ans = 0;
        while(N--){
            int a, b;
            scanf("%d %d", &a, &b);

            if(middle < a && middle < b){
                maxh.push(middle);
                minh.push(a);
                minh.push(b);
                middle = minh.top();
                minh.pop();
            }
            else if(middle > a && middle > b){
                minh.push(middle);
                maxh.push(a);
                maxh.push(b);
                middle = maxh.top();
                maxh.pop();
            }
            else{
                if(a > b){
                    maxh.push(b);
                    minh.push(a);
                }
                else{
                    maxh.push(a);
                    minh.push(b);
                }
            }
            printf("%d", middle);
            ans += middle;
            if(ans >= 20171109) ans %= 20171109;
        }
        printf("#%d %d\n", test, ans);
    }
}
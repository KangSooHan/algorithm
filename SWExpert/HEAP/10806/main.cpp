#include <stdio.h>
#include <cassert>

struct Info{
    int cnt, val;
};

void swap(Info &a, Info &b){
    Info temp = a; a = b; b = temp;
}

class Heap{
#define parent (i>>1)
#define left (i<<1)
#define right (i<<1|1)
    static constexpr size_t maxh = 1<<14;

    Info pool[maxh+1];
    size_t size;

public:
    Heap() = default;

    void init(){
        size = 0;
    }

    void push(Info x){
        pool[++size] = x;
        for(int i=size; parent!=0; i>>=1){
            if(pool[i].cnt < pool[parent].cnt){
                swap(pool[i], pool[parent]);
            }
            else if(pool[i].cnt == pool[parent].cnt){
                if(pool[i].val < pool[parent].val){
                    swap(pool[i], pool[parent]);
                }
            }
        }
    }

    void pop(){
        assert(size != 0);
        pool[1] = pool[size--];
        for(size_t i=1; left <= size;){
            if(left == size || pool[left].cnt < pool[right].cnt){
                if(pool[i].cnt > pool[left].cnt){
                    swap(pool[i], pool[left]);
                    i = left;
                }
                else if(pool[i].cnt == pool[left].cnt){
                    if(pool[i].val > pool[left].val){
                        swap(pool[i], pool[left]);
                        i = left;
                    }
                    else break;
                }
                else break;
            }
            else{
                if(pool[i].cnt > pool[right].cnt){
                    swap(pool[i], pool[right]);
                    i = right;
                }
                else if(pool[i].cnt == pool[left].cnt){
                    if(pool[i].val > pool[right].val){
                        swap(pool[i], pool[right]);
                        i = right;
                    }
                    else break;
                }
                else break;
            }
        }

    }

    Info top() const{
        assert( size != 0);
        return pool[1];
    }

    bool empty(){
        return size == 0;
    }
};

Heap h {};

int arr[11];

int main(){
    freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);
    for(int test=1; test<=T; ++test){
        int N;
        scanf("%d", &N);

        int min = 1000000001;
        for(int i=0; i<N; ++i){
            scanf("%d", &arr[i]);
            if(min > arr[i]) min = arr[i];
        }

        int k;
        scanf("%d", &k);

        h.init();
        int ans;
        h.push({0, k});
        while(!h.empty()){
            Info cur = h.top();
            h.pop();

            if(cur.val == 0){
                printf("#%d %d\n",test, cur.cnt);
                break;
            }

            if(cur.val < min){
                h.push({cur.cnt + cur.val, 0});
            }

            
            int cnt=0;
            for(int i=0; i<N; ++i){
                h.push({cur.cnt + (cur.val%arr[i]), cur.val / arr[i]});
            }
        }
    }
}

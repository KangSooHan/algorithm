#include <stdio.h>
#include <cstdlib>

void swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

enum CMD
{
    INIT=0,
    RANDINSERT,
    INSERT,
    POP,
    TOP
};

static const char *enumStr [] = 
{"INIT", "RANDINSERT", "INSERT", "POP", "TOP"};

class MaxHeap{
#define parent ( i >> 1)
#define left (i << 1)
#define right ( i<< 1 | 1)
    static constexpr size_t MAXN = 100001;
    
    int data[MAXN+1];
    size_t size;
public:
    MaxHeap() = default;

    void init(){
        size = 0;
    }

    void push(int x){
        data[++size] = x;
        for(int i = size; parent != 0 && data[parent] < data[i]; i>>=1){
            swap(data[parent], data[i]);
        }
    }

    int top(){
        if(size == 0) {
            return -999999;
        }
        return data[1];
    }

    void pop(){
        if(size == 0){
            printf("EMPTY\n");
            return;
        };
        data[1] = data[size--];
        for(int i=1; left<=size;){
            if(left == size || data[left] > data[right]){
                if(data[i] < data[left]){
                    swap(data[i], data[left]);
                    i = left;
                }
                else{
                    break;
                }
            }
            else{
                if(data[i] < data[right]){
                    std:;swap(data[i], data[right]);
                    i = right;
                }
                else{
                    break;
                }
            }
        }
    }
};



int main()
{
    int cmd, x, t;
    MaxHeap MH {};
    while(true)
    {
        printf("Please Enter\n");
        for(int i=0; i<=4; ++i)
        {
            printf("%d : %s\n", i, enumStr[i]);
        }
        scanf("%d", &cmd);
        switch(cmd)
        {
            case INIT:
                printf("Init OKAY!\n");
                MH.init();
                break;
            case RANDINSERT:
                printf("How Many Sample Do You Want To Generate Please Type 0 ~ 100\n");
                scanf("%d", &x);
                if(x<0 || x>100)
                {
                    printf("Invalid Input Size! Please Type 0 ~ 100\n");
                    break;
                }
                for(int i=0; i<x; ++i)
                {
                    MH.push((rand() % 2000)-1000);
                }
                break;
            case INSERT:
                printf("Type Insert Value\n");
                scanf("%d", &x);
                MH.push(x);
                break;
            case POP:
                MH.pop();
                break;
            case TOP:
                t = MH.top();
                if(t == -999999) {printf("EMPTY\n");}
                else {printf("TOP Value : %d\n", MH.top());}
                break;
            default:
                printf("Invalid Command! Please Type\n");
                for(int i=0; i<=4; ++i)
                {
                    printf("%d : %s\n", i, enumStr[i]);
                }
                break;
        }
    }
    return 0;
}

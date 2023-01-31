#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_INPUT 10000
#define MAX_NUM 30000

struct info{
    int id;
    int income;
};

void SWAP(info &a, info &b){
    info temp;
    temp = a;
    a = b;
    b = temp;
}

class MaxHeap{
#define parent ( i >> 1 )
#define left ( i << 1 )
#define right ( i << 1 | 1 )

    info pool[100002];
    int size;

public:
    void init(){
        size = 0;
    }

    void push(int id, int income){
        pool[++size] = {id, income};

        for(int i=size; parent != 0;){
            if(pool[parent].income > pool[i].income){
                break;
            }
            else if(pool[parent].income < pool[i].income){
                SWAP(pool[parent], pool[i]);
                i = parent;
            }
            else{
                if(pool[parent].id > pool[i].id){
                    SWAP(pool[parent], pool[i]);
                    i = parent;
                }
                else break;
            }
        }
    }

    void pop(){
        if (size == 0) return;
        pool[1] = pool[size--];

        for(int i=1; left<=size;){
            if(left == size || pool[left].income > pool[right].income || (pool[left].income == pool[right].income && pool[left].id < pool[right].id)){
                if(pool[i].income < pool[left].income){
                    SWAP(pool[i], pool[left]);
                    i = left;
                }
                else if(pool[i].income == pool[left].income){
                    if(pool[i].id > pool[left].id){
                        SWAP(pool[i], pool[left]);
                        i = left;
                    }
                    else break;
                }
                else break;
            }
            else{
                if(pool[i].income < pool[right].income){
                    SWAP(pool[i], pool[right]);
                    i = right;
                }
                else if(pool[i].income == pool[right].income){
                    if(pool[i].id > pool[right].id){
                        SWAP(pool[i], pool[right]);
                        i = right;
                    }
                    else break;
                }
                else break;
            }
        }
    }

    int top(){
        if( size == 0 ) return -1;
        else return pool[1].id;
    }
};

MaxHeap MH, MH1;

void init(){
    MH.init();
}
void addUser(int uID, int income){
    MH.push(uID, income);
}
int getTop10(int result[10]){
    MH1 = MH;
    int cnt=0;
    while(true){
        int res = MH1.top();
        if(res == -1 || cnt == 10){
            break;
        }
        result[cnt++] = res;
        MH1.pop();
    }
    return cnt;
}

static int input[MAX_INPUT];

static unsigned int seed = 13410;

static unsigned int pseudoRand() {
	seed = seed * 214013 + 2531011;
	return (unsigned int)(seed >> 11) % MAX_NUM;
}

static void makeInput(int inputLen) {
	for (int i = 0; i < inputLen; i++) {
		input[i] = pseudoRand();
	}
}

static int run() {
	int N, userNum, uID = 0;
	int score = 100, result[10], cnt;
	int sum, check;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &userNum);
		makeInput(userNum);
		for (int j = 0; j < userNum; j++) {
			addUser(uID++, input[j]);
		}
		cnt = getTop10(result);

		sum = 0;
		for (int j = 0; j < cnt; j++)
			sum += result[j];
		scanf("%d", &check);    
		if (check != sum)
			score = 0;
	}
	return score;
}

int main(void) {
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		printf("#%d %d\n", tc, run());
	}
	return 0;
}
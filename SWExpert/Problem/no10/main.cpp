#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 200

size_t djb2(char mExpression[100]){
    size_t hash = 5381;
    for(int i=0; i<100; ++i){
        if(mExpression[i] == '\0') break;
        hash = ((hash<<5) + hash) + mExpression[i];
    }
    return hash;
}

char idExpression[5002][100];

struct Node{
    char mExpression[100];
    int val;
    Node* next;
};

Node node_pool[5002];
int node_cnt;

Node* new_node(char mExpression[100]){
    strcpy(node_pool[node_cnt].mExpression, mExpression);
    node_pool[node_cnt].val = 0;
    node_pool[node_cnt].next = nullptr;
    return &node_pool[node_cnt++];
}

class HashMap{
    static constexpr size_t table_size = 1<<14;
    static constexpr size_t DIV = table_size-1;
    Node hpool[table_size];
public:
    
    HashMap() = default;

    void init(){
        node_cnt = 0;
        for(int i=0; i<table_size; ++i){
            hpool[i].next = nullptr;
        }
    }

    int push(char mExpression[100]){
        Node* prev_node = get_prev_node(mExpression);

        if(prev_node->next == nullptr){
            prev_node->next = new_node(mExpression);
            return 0;
        }
        else{
            prev_node->next->val++;
            return prev_node->next->val;
        }
    }

private:
    Node* get_prev_node(char mExpression[100]){
        Node* prev_node = &hpool[djb2(mExpression) & DIV];

        while(prev_node->next != nullptr && strcmp(prev_node->next->mExpression, mExpression)!=0){
            prev_node = prev_node->next;
        }
        return prev_node;
    }
};

HashMap HM {};

struct mVal{
    int cnt[10] = {0};
};

struct stack{
    mVal pool[1001];
    int r;
    void init(){r=0;}
    void push(mVal c){
        pool[r++] = c;
    }
    mVal pop(){ 
        return pool[--r];
    }
    mVal top(){ return pool[r-1];}
    bool empty(){return r==0;}
};


struct stackc{
    char pool[1001];
    int r;
    void init(){r=0;}
    void push(char c){
        pool[r++] = c;
    }
    char pop(){ 
        return pool[--r];
    }
    char top(){ return pool[r-1];}
    bool empty(){return r==0;}
};

stack sNum;
stackc sCal;

int Priority(char c){
    if (c=='(') return 0;
    else if(c=='+' || c=='-') return 1;
    else if(c=='*') return 2;
    return 3;
}

mVal calc(mVal A, mVal B, char c){
    mVal nexp = {0};
    if(c=='+'){
        for(int i=0; i<10; ++i){
            nexp.cnt[i] = A.cnt[i] + B.cnt[i];
        }
    }
    else if(c=='-'){
        for(int i=0; i<10; ++i){
            nexp.cnt[i] = A.cnt[i] - B.cnt[i];
        }
    }
    else{
        nexp.cnt[0] = A.cnt[9] * B.cnt[0] + A.cnt[0] * B.cnt[9];
        nexp.cnt[1] = A.cnt[9] * B.cnt[1] + A.cnt[1] * B.cnt[9];
        nexp.cnt[2] = A.cnt[9] * B.cnt[2] + A.cnt[2] * B.cnt[9];
        nexp.cnt[3] = A.cnt[0] * B.cnt[0];
        nexp.cnt[4] = A.cnt[0] * B.cnt[1] + A.cnt[1] * B.cnt[0];
        nexp.cnt[5] = A.cnt[0] * B.cnt[2] + A.cnt[2] * B.cnt[0];
        nexp.cnt[6] = A.cnt[1] * B.cnt[1];
        nexp.cnt[7] = A.cnt[1] * B.cnt[2] + A.cnt[2] * B.cnt[1];
        nexp.cnt[8] = A.cnt[2] * B.cnt[2];
        nexp.cnt[9] = A.cnt[9] * B.cnt[9];
    }

    return nexp;
}

mVal calcID[5002];

void init(){
    HM.init();
}

int addExpression(int mID, char mExpression[MAX_LEN + 1]){
    sNum.init();
    sCal.init();
    for(int i=0; i<MAX_LEN+1; ++i){
        if(mExpression[i] == '\0') break;
        mVal nexp = {0};
        if(mExpression[i] >= '0' && mExpression[i] <= '9')
        {
            nexp.cnt[9] = mExpression[i] - '0';
            sNum.push(nexp);
        }
        else if(mExpression[i] == 'A' || mExpression[i] == 'B' || mExpression[i] == 'C'){
            nexp.cnt[mExpression[i] - 'A'] = 1;
            sNum.push(nexp);
        }
        else if(mExpression[i] == ')'){
            while(sCal.top() != '('){
                mVal B = sNum.pop();
                mVal A = sNum.pop();
                sNum.push(calc(A, B, sCal.pop()));
            }
            sCal.pop();
        }
        else if(mExpression[i] == '('){
            sCal.push(mExpression[i]);
        }
        else{
            while(!sCal.empty() && Priority(sCal.top()) >= Priority(mExpression[i])){
                mVal B = sNum.pop();
                mVal A = sNum.pop();
                sNum.push(calc(A, B, sCal.pop()));
            }
            sCal.push(mExpression[i]);
        }
    }

    while(!sCal.empty()){
        mVal B = sNum.pop();
        mVal A = sNum.pop();
        sNum.push(calc(A, B, sCal.pop()));
    }
    mVal last = sNum.pop();
    char res[100] = "\0";
    for(int i=0; i<10; ++i){
        char val[10] = "\0";
        char name[2];
        name[1] = '\0';
        name[0] = 'A'+i;

        int num = last.cnt[i];
        int idx;
        if(num<0){
            val[0] = '-';
            idx = 1;
            num = -num;
        }
        else{
            val[0] = '0';
            idx = 0;
        }
        while(num){
            val[idx++] = '0'+num%10;
            num /= 10;
        }
        val[++idx] = '\0';
        
        strcat(res, val);
        strcat(res, name);
    }
    int ans = HM.push(res);
    if(ans == 0){
        if(last.cnt[0] != 0 || last.cnt[3] != 0 || last.cnt[4] != 0 || last.cnt[5] != 0) ans--;
        if(last.cnt[1] != 0 || last.cnt[4] != 0 || last.cnt[6] != 0 || last.cnt[7] != 0) ans--;
        if(last.cnt[2] != 0 || last.cnt[5] != 0 || last.cnt[7] != 0 || last.cnt[8] != 0) ans--;
    }

    calcID[mID] = last;
    return ans;
}


int calcExpression(int mID, int mA, int mB, int mC){
    mVal now = calcID[mID];

    int ans = 0;
    ans += now.cnt[0] * mA;
    ans += now.cnt[1] * mB;
    ans += now.cnt[2] * mC;
    ans += now.cnt[3] * mA * mA;
    ans += now.cnt[4] * mA * mB;
    ans += now.cnt[5] * mA * mC;
    ans += now.cnt[6] * mB * mB;
    ans += now.cnt[7] * mB * mC;
    ans += now.cnt[8] * mC * mC;
    ans += now.cnt[9];

    return ans;
}

#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_CALC 300

static bool run()
{
    int query_num;
    scanf("%d", &query_num);

    int ret, ans;
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);

        if (query == CMD_INIT)
        {
            init();
            ok = true;
        }
        else if (query == CMD_ADD)
        {
            int mID;
            char mExpression[MAX_LEN + 1];
            scanf("%d %s", &mID, mExpression);
            ret = addExpression(mID, mExpression);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
        else if (query == CMD_CALC)
        {
            int mID;
            int mA, mB, mC;
            scanf("%d %d %d %d", &mID, &mA, &mB, &mC);
            ret = calcExpression(mID, mA, mB, mC);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
    }
    return ok;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}

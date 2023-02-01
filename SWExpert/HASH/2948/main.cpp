#include <stdio.h>
#include <string.h>

size_t djb2(const char *str){
    size_t hash = 5381;
    for(;*str; ++str){
        hash = ((hash << 5) + hash) + *str;
    }
    return hash;
}

constexpr size_t MAX_N = 100000;
constexpr size_t MAX_LEN = 50;

struct Node{
    char str[MAX_LEN+1];
    Node* next;
};

Node node_pool[MAX_N+1];
int node_cnt;

Node* new_node(char str[MAX_LEN+1]){
    strcpy(node_pool[node_cnt].str, str);
    node_pool[node_cnt].next = nullptr;
    return &node_pool[node_cnt++];
}

class HashMap{
    static constexpr size_t table_size = 1<<12;
    static constexpr size_t div = table_size - 1;

    Node hash_table[table_size];

public:
    HashMap() = default;

    void init(){
        memset(hash_table, 0, sizeof(hash_table));
        node_cnt = 0;
    }

    void insert(char str[MAX_LEN+1]){
        Node* prev_node = get_prev_node(str);
        prev_node->next = new_node(str);
    }

    bool get(char str[MAX_LEN+1]){
        Node* prev_node = get_prev_node(str);
        while(prev_node->next != nullptr){
            prev_node = prev_node->next;
            if(strcmp(prev_node->str, str) == 0) return true;
        }
        return false;
    }

private:
    Node* get_prev_node(char str[MAX_LEN+1]){
        Node* prev_node = &hash_table[djb2(str) & div];
        printf("%s", prev_node->str);

        while(prev_node->next != nullptr && strcmp(prev_node->next->str, str) != 0){
            prev_node = prev_node->next;
        }
        return prev_node;
    }
};

HashMap HM {};


int main(){
    //freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);

    for(int test=1; test<=T; ++test){
        HM.init();
        int N, M;
        scanf("%d %d", &N, &M);

        char str[MAX_LEN+1];

        for(int i=0; i<N; ++i){
            scanf("%s", str);
            HM.insert(str);
        }

        int ans = 0;
        for(int i=0; i<M; ++i){
            scanf("%s", str);
            if(HM.get(str)) ans++;
        }
        printf("#%d %d\n", test, ans);
    }
}

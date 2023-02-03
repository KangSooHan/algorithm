#include <stdio.h>
#include <string.h>

char buf[402][401];

struct Node{
    int terminal;
    Node* child[26];
};

struct stack{
    Node* pool[401*200];
    int r;

    void init(){r=0;}
    void push(Node* node){pool[r++] = node;}
    Node* pop(){return pool[--r];}
    bool empty(){return r==0;}
};

int node_cnt;
Node node_pool[400*200];

Node* new_node(){
    node_pool[node_cnt].terminal = -1;
    for(int i=0; i<26; ++i){
        node_pool[node_cnt].child[i] = nullptr;
    }
    return &node_pool[node_cnt++];
}

class TRIE{
    Node* root;
    int word_cnt;
    stack s;

public:
    TRIE() = default;

    void init(){
        node_cnt = 0;
        word_cnt = 0;
        root = new_node();
    }

    void push(char str[401]){
        strcpy(buf[word_cnt], str);
        Node* node = root;
        for(; *str; ++str){
            if(node->child[*str-'a'] == nullptr){
                node->child[*str-'a'] = new_node();
                node = node->child[*str-'a'];
            }
            else{
                node = node->child[*str-'a'];
            }
        }
        node->terminal = word_cnt++;
    }

    int find(int k){
        s.init();
        s.push(root);
        int cnt = 1;
        while(!s.empty()){
            Node* node = s.pop();
            if(node->terminal != -1){
                if(cnt==k){
                    return node->terminal;
                }
                cnt++;
            }
            for(int i=25; i>=0; --i){
                if(node->child[i] == nullptr) continue;
                s.push(node->child[i]);
            }
        }
        return -1;
    }
};

TRIE trie {};

int main(){
    freopen("input.txt", "r", stdin);

    int T;
    char str[401];
    scanf("%d", &T);

    for(int test=1; test<=T; ++test){
        trie.init();
        int k;
        scanf("%d", &k);
        scanf("%s", str);

        int size = strlen(str);
        char str1[401];
        for(int i=0; i<size; ++i){
            strcpy(str1, str+i);
            trie.push(str1);
        }

        int idx = trie.find(k);
        if(idx==-1) printf("#%d none",test);
        else printf("#%d %s\n",test, buf[idx]);
    }
}

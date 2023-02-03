#include <stdio.h>
#include <string.h>

char ans[401];

struct Node{
    int depth;
    Node* child[26];
};


struct stack{
    Node* pool[402];
    int r;

    void init(){r=0;}
    void push(Node* node){pool[r++] = node;}
    Node* pop(){return pool[--r];}
    bool empty(){return r==0;}
};

struct stack1{
    char pool[402];
    int r;

    void init(){r=0;}
    void push(char c){pool[r++] = c;}
    char pop(){return pool[--r];}
    bool empty(){return r==0;}
};

int node_cnt;
Node node_pool[402*200];

Node* new_node(){
    for(int i=0; i<26; ++i){
        node_pool[node_cnt].child[i] = nullptr;
    }
    return &node_pool[node_cnt++];
}

class TRIE{
    Node* root;
    stack s;
    stack1 s1;
public:
    TRIE() = default;

    void init(){
        node_cnt = 0;
        root = new_node();
        root->depth = 0;
    }

    void push(char str[401]){
        Node* node = root;
        for(; *str; ++str){
            if(node->child[*str-'a'] == nullptr){
                node->child[*str-'a'] = new_node();
                node->child[*str-'a']->depth = node->depth+1;
            }
            node = node->child[*str-'a'];
        }
    }

    bool find(int k){
        s.init(), s1.init();
        s.push(root), s1.push('\0');

        int cnt=0;
        while(!s.empty()){
            Node* node = s.pop();
            char c = s1.pop();
            if(node->depth != 0){
                ans[node->depth-1] = c;
                ans[node->depth] = '\0';
            }
            if(cnt==k){
                return true;
            }
            for(int i=25; i>=0; --i){
                if(node->child[i] == nullptr) continue;
                s.push(node->child[i]), s1.push('a'+i);
            }
            cnt++;
        }
        return false;

    }
};

TRIE trie {};

int main(){
    freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);
    char str[401];
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
        bool flag = trie.find(k);
        if(!flag) printf("#%d none\n", test);
        else printf("#%d %s\n",test, ans);
    }
}

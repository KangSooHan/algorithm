#include <stdio.h>
#include <string.h>

bool pic1[2001][2001];
bool pic2[2001][2001];


int H, W, N, M;

size_t  hashF(bool line[2001])
{
    size_t val = 0;
    for(int i=0; i<H; ++i){
        val = (val<<1) + line[i];
    }
    return val;
}


/*
struct Node{
    size_t line[2001];
    Node* next;
};

Node node_pool[2001];
int node_cnt;

class HashMap{
    static constexpr size_t table_size = 1<<10;
    static constexpr size_t DIV = table_size-1;
    Node hash_table[table_size];
public:
    HashMap() = default;

    void init(){
        node_cnt = 0;
        memset(hash_table, 0, sizeof(hash_table));
    }

    void insert(bool line[2001]){
        Node* prev_node = get_prev_node(line);
    }

private:
    Node* get_prev_node(bool line[2001]){
        Node* pred_node = &hash_table[hashF1(line) % DIV];
    }

};
*/

int main(){
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    for(int test=1; test<=T; ++test){
        scanf("%d %d %d %d", &H, &W, &N, &M);

        for(int i=0; i<H; ++i){
            for(int j=0; j<W; ++j){
                char c;
                scanf(" %c", &c);
                pic1[i][j] = c=='o' ? true : false;
            }
            size_t val = hashF(pic1[i]);
            printf("%llu ", val);
        }

        for(int i=0; i<N; ++i){
            for(int j=0; j<M; ++j){
                char c;
                scanf(" %c", &c);
                pic2[i][j] = c=='o' ? true : false;
            }
        }
    }

}

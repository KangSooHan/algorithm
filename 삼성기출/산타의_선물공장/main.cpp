#include <stdio.h>

struct Node{
    int id, w, bnum;
    Node *next, *prev;
    Node *hnext;
};

Node node_pool[100001];
int node_cnt, n, m;
int belt[11];

Node* new_node(int id, int w, int bnum){
    node_pool[node_cnt].id = id;
    node_pool[node_cnt].w = w;
    node_pool[node_cnt].bnum = bnum;
    node_pool[node_cnt].next = nullptr;
    node_pool[node_cnt].prev = nullptr;
    node_pool[node_cnt].hnext = nullptr;
    return &node_pool[node_cnt++];
}

class DLL{
    static constexpr size_t tsize = 1<<14;
    static constexpr size_t DIV = tsize-1;
    Node htable[tsize];
    Node *head[11], *tail[11];
public:
    DLL() = default;

    void init(){
        node_cnt = 0;
        for(int i=0; i<m; ++i){
            belt[i] = i;
            head[i] = new_node(0, 0, i);
            tail[i] = new_node(0, 0, i);

            head[i]->next = tail[i];
            head[i]->prev = nullptr;
            tail[i]->next = nullptr;
            tail[i]->prev = head[i];
        }
    }

    Node* get(int id){
        Node* prev_node = get_prev_node(id);
        return prev_node->hnext;
    }

    void insert(int id, int w, int bnum){
        Node* prev_node = get_prev_node(id);
        Node* node = new_node(id, w, bnum);

        prev_node->hnext = node;

        node->next = tail[bnum];
        tail[bnum]->prev->next = node;
        node->next = tail[bnum];
        node->prev = tail[bnum]->prev;
        tail[bnum]->prev = node;
    }

    int pop(int w_max){
        int ans=0;
        for(int i=0; i<m; ++i){
            if(belt[i] != i) continue;
            if(head[i]->next == tail[i]) continue;

            Node* node = head[i]->next;
            node->prev->next = node->next;
            node->next->prev = node->prev;
            if(node->w > w_max){
                tail[i]->prev->next = node;
                node->prev = tail[i]->prev;
                node->next = tail[i];
                tail[i]->prev = node;
            }
            else{
                Node* prev_node = get_prev_node(node->id);
                prev_node->hnext = prev_node->hnext->hnext;
                ans += node->w;
            }
        }
        return ans;
    }

    int remove(int r_id){
        Node* prev_node = get_prev_node(r_id);
        if(prev_node->hnext == nullptr) return -1;

        Node* node = prev_node->hnext;
        prev_node->hnext = prev_node->hnext->hnext;

        node->next->prev = node->prev;
        node->prev->next = node->next;
        return r_id;
    }

    int check(int f_id){
        Node* prev_node = get_prev_node(f_id);
        if(prev_node->hnext == nullptr) return -1;

        Node* node = prev_node->hnext;

        int bnum = belt[node->bnum];


        tail[bnum]->prev->next = head[bnum]->next;
        head[bnum]->next->prev = tail[bnum]->prev;
        head[bnum]->next = node;
        node->prev->next = tail[bnum];
        tail[bnum]->prev = node->prev;
        node->prev = head[bnum];

        return belt[node->bnum]+1;
    }

    int destroy(int b_num){
        b_num--;
        if(belt[b_num] != b_num) return -1;
        for(int i=1; i<m; ++i){
            int bnum = (b_num+i)%m;
            if(belt[bnum] != bnum) continue;
            belt[b_num] = bnum;
            break;
        }

        for(int i=0; i<m; ++i){
            if(belt[i] == b_num){
                belt[i] = belt[b_num];
            }
        }

        if(head[b_num]->next == tail[b_num]) return b_num+1;

        tail[belt[b_num]]->prev->next = head[b_num]->next;
        head[b_num]->next->prev = tail[belt[b_num]]->prev;

        tail[b_num]->prev->next = tail[belt[b_num]];
        tail[belt[b_num]]->prev = tail[b_num]->prev;
        return b_num+1;
    }

private:
    Node* get_prev_node(int id){
        Node* prev_node = &htable[(id%5381) & DIV];

        while(prev_node->hnext != nullptr && prev_node->hnext->id != id){
            prev_node = prev_node->hnext;
        }
        return prev_node;
    }
};

DLL dll {};

int main(){
    freopen("input.txt", "r", stdin);
    int q;
    scanf("%d", &q);

    int cmd, w_max, r_id, f_id, b_num;
    int ids[100001];
    int ws[100001];
    while(q--){
        scanf("%d", &cmd);
        switch(cmd){
            case 100:
                scanf("%d %d", &n, &m); 
                dll.init();
                for(int i=0; i<n; ++i){
                    scanf("%d", &ids[i]);         
                }
                for(int i=0; i<n; ++i){
                    scanf("%d", &ws[i]);
                }
                for(int i=0; i<n; ++i){
                    dll.insert(ids[i], ws[i], i*m/n);
                }
                break;
            case 200:
                scanf("%d", &w_max);
                printf("%d\n", dll.pop(w_max));
                break;
            case 300:
                scanf("%d", &r_id);
                printf("%d\n", dll.remove(r_id));
                break;
            case 400:
                scanf("%d", &f_id);
                printf("%d\n", dll.check(f_id));
                break;
            case 500:
                scanf("%d", &b_num);
                printf("%d\n", dll.destroy(b_num));
            default:
                break;
        }
    }
}

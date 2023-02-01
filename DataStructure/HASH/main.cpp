#include <stdio.h>
#include <string.h>

enum command{
    INIT,
    INSERT,
    REMOVE,
    GET
};

size_t djb2(const char* str){
    size_t hash = 5381;

    for(; *str; ++str){
        hash = ((hash << 5) + hash) + *str;
    }
    return hash;
}

constexpr size_t MAX_N = 10000;
constexpr size_t MAX_LEN = 10;

struct Node{
    char str[MAX_LEN+1];
    int data;
    Node* next;
};

int node_cnt = 0;

Node node_pool[MAX_N+1];


Node* new_node(const char str[MAX_LEN+1], int data)
{
    strcpy(node_pool[node_cnt].str, str);
    node_pool[node_cnt].data = data;
    node_pool[node_cnt].next = nullptr;

    return &node_pool[node_cnt++];
}

class HashMap{
    static constexpr size_t TABLE_SIZE = 1<<12;
    static constexpr size_t DIV = TABLE_SIZE-1;

    Node hash_table[TABLE_SIZE];

public:
    HashMap() = default;

    void init(){
        memset(hash_table, 0, sizeof(hash_table));
        node_cnt = 0;
    }

    void insert(const char str[MAX_LEN+1], int data){
        Node* const prev_node = get_prev_node(str);

        if(prev_node->next == nullptr){
            prev_node->next = new_node(str, data);
        }
        else{
            prev_node->next->data = data;
        }
    }

    void remove(const char str[MAX_LEN+1]){
        Node* const prev_node = get_prev_node(str);
        if(prev_node->next != nullptr){
            prev_node->next = prev_node->next->next;
        }
    }

    Node* get(const char str[MAX_LEN+1]){
        return get_prev_node(str)->next;
    }


private:
    Node* get_prev_node(const char str[MAX_LEN+1]){
        Node* prev_ptr = &hash_table[djb2(str) & DIV];
        while(prev_ptr->next != nullptr && strcmp(prev_ptr->next->str, str) != 0){
            prev_ptr = prev_ptr->next;
        }
        return prev_ptr;
    }
};

HashMap HM {};

int main(){
    int cmd, x;
    char str[MAX_LEN+1];
    Node* ptr;
    while(true){
        scanf("%d", &cmd);

        switch(cmd){
            case INIT:
                HM.init();
                break;
            case INSERT:
                scanf("%s %d", str, &x);
                if(strlen(str) > MAX_LEN){
                    printf("Invalid Key Length\n");
                }
                else{
                    HM.insert(str, x);
                }
                break;
            case REMOVE:
                scanf("%s", str);
                if(strlen(str) > MAX_LEN){
                    printf("Invalid Key Length\n");
                }
                else{
                    HM.remove(str);
                }
                break;
            case GET:
                scanf("%s", str);
                ptr = HM.get(str);
                if(strlen(str) > MAX_LEN){
                    printf("Invalid Key Length\n");
                }
                else{
                    printf("%s : %d", str, ptr->data);
                }
                break;
            default:
                printf("INVALID COMMAND\n");
        }
    }
    return 0;
}

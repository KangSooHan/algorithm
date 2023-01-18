#include <stdio.h>
#include <malloc.h>

struct Node{
    int data;
    Node *next, *prev;
};

class doublyLinkedList{
    Node *head, *tail;
    int node_cnt;

public:
    doublyLinkedList() = default;

    void init(){
        head = new_node();
        tail = new_node();

        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;

        node_cnt = 0;
    }

    void insert(int pos, int data)
    {
        Node* node = find(pos);
        Node* insert_node = new_node(data);
        
        insert_node->next = node;
        insert_node->prev = node->prev;
        node->prev->next = insert_node;
        node->prev = insert_node;
        node_cnt++;
    }

    void change(int pos, int data)
    {
        Node* node = find(pos);
        node->data = data;
    }

    void print(){
        Node* node = head->next;

        for(int i=0; i<node_cnt; ++i)
        {
            node = node->next;
        }
    }

    void append(int cnt, int arr[])
    {
        for(int i=0; i<cnt; ++i)
        {
            Node* node = new_node(arr[i]);
            tail->prev->next = node;
            node->prev = tail->prev;
            node->next = tail;
            tail->prev = node;
            node_cnt++;
        }
    }

    void remove(int pos)
    {
        Node* node = find(pos)->prev;
        node->next->next->prev = node;
        node->next = node->next->next;
        node_cnt--;
    }

    int find_value(int pos)
    {
        if(pos > node_cnt) return -1;

        return find(pos)->data;
    }

    Node* find(int pos)
    {
        Node* node = head;
        for(int cnt=0; cnt<=pos; ++cnt)
        {
            node = node->next;
        }
        return node;
    }

private:
    Node* new_node()
    {
        Node* node = (Node*)malloc(sizeof(Node));
        node->next = nullptr;
        node->prev = nullptr;
        return node;
    }

    Node* new_node(int data)
    {
        Node* node = (Node*)malloc(sizeof(Node));
        node->data = data;
        node->next = nullptr;
        node->prev = nullptr;
        return node;
    }
};


int main(){
    freopen("input.txt", "r", stdin);

    doublyLinkedList dll {};

    int T;
    scanf("%d", &T);

    for(int test=1; test<=T; ++test)
    {
        dll.init();
        int n, m, l;
        scanf("%d %d %d", &n, &m, &l);

        int *origin = (int*)malloc(sizeof(int) * n);
        for(int i=0; i<n; ++i){
            scanf("%d", &origin[i]);
        }
        dll.append(n, origin);

        for(int i=0; i<m; ++i)
        {
            char command;
            scanf(" %c", &command);

            if(command=='I'){
                int idx, data;
                scanf("%d %d", &idx, &data);
                dll.insert(idx, data);
                dll.print();
            }
            else if(command=='D'){
                int idx;
                scanf("%d", &idx);
                dll.remove(idx);
                dll.print();
            }
            else{
                int idx, data;
                scanf("%d %d", &idx, &data);
                dll.change(idx, data);
                dll.print();
            }
        }

        int ans = dll.find_value(l);

        printf("#%d %d\n", test, ans);
    }

    return 0;
}

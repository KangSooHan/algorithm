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
    doublyLinkedList () = default;
    void init(){
        head = new_node();
        tail = new_node();
        head->next = tail;
        tail->prev = head;
        node_cnt = 0;
    }

    void addNode2Head(int data)
    {
        Node* newNode = new_node(data);

        newNode->next = head->next;
        head->next->prev = newNode;
        newNode->prev = head;
        head->next = newNode;

        node_cnt++;
    }

    void addNode2Tail(int data)
    {
        Node* newNode = new_node(data);

        newNode->prev = tail->prev;
        newNode->next = tail;
        tail->prev->next = newNode;
        tail->prev = newNode;

        node_cnt++;
    }

    void addNode2Num(int data, int num)
    {
        Node* node = idxFind(num);

        Node* newNode = new_node(data);

        newNode->next = node->next;
        newNode->prev = node;
        node->next->prev = newNode;
        node->next = newNode;

        node_cnt++;
   }

   void removeNode(int data)
   {
        Node* node = valFind(data);

        node->next->prev = node->prev;
        node->prev->next = node->next;

        node_cnt--;
   }

    void getList(int output[])
    {
        Node* node = head;
        int cnt = 0;
        while(node->next != tail)
        {
            node = node->next;
            output[cnt++] = node->data;
        }
    }

    void print()
    {
        Node* node = head;
        printf("PRINT LIST :");
        while(node->next != tail )
        {
            node = node->next;
            printf(" %d", node->data);
        }
        printf("\n");
    }





private:
    Node* new_node()
    {
        Node* node = (Node*)malloc(sizeof(Node));
        node->prev = nullptr;
        node->next = nullptr;
        return node;
    }
    Node* new_node(int data)
    {
        Node* node = (Node*)malloc(sizeof(Node));
        node->data = data;
        node->prev = nullptr;
        node->next = nullptr;
        return node;
    }

    Node* idxFind(int idx)
    {

        if(node_cnt / 2 > idx)
        {
            Node* node = head;
            for(int i=0; i<idx; ++i)
            {
                node = node->next;
            }
            return node;
        }

        else
        {
            Node* node = tail;
            for(int i=node_cnt; i>=idx; --i)
            {
                node = node->prev;
            }
            return node;
        }
    }

    Node* valFind(int data)
    {
        Node* node = head;
        bool flag=false;
        while(node->next != nullptr)
        {
            node = node->next;
            if(node->data == data){
                flag = true;
                break;
            }
        }

        if(flag) return node;
        else return head;
    }



};


int main(){
    doublyLinkedList dll {};

    dll.init();

    // 2
    dll.addNode2Head(2);
    dll.print();
    // 1 2
    dll.addNode2Head(1);
    dll.print();
    // 1 2 4
    dll.addNode2Tail(4);
    dll.print();
    // 1 2 4 4
    dll.addNode2Tail(4);
    dll.print();
    // 0 1 2 4 4
    dll.addNode2Num(0, 0);
    dll.print();
    // 0 1 2 3 4 4 
    dll.addNode2Num(3, 3);
    dll.print();
    // 0 1 2 3 4 4 5
    dll.addNode2Num(5, 6); // add by index
    dll.print();
    // 0 1 2 3 4 5
    dll.removeNode(4); // remove by value
    dll.print();

    int output[6];
    dll.getList(output);
    printf("List : ");
    for(int i=0; i<6; ++i)
    {
        printf(" %d", output[i]);
    }
    printf("\n");

    return 0;
}

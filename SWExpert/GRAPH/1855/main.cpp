#include <stdio.h>
#include <vector>

int N;

struct Node{
    std::vector<int> child;
    int depth;
    int parent;
};

Node node_pool[100002];

struct queue{
    int pool[100002];
    int r, l;

    void init(){
        r = l = 0;
    }

    void push(int data)
    {
        pool[r++] = data;
    }

    int pop(){
        return pool[l++];
    }
    bool empty(){
        return r==l;
    }

    int size(){
        return r-l;
    }
};

queue q;

class Tree{
public:
    Tree() = default;

    void init(){
        node_pool[1].child.clear();
        node_pool[1].depth = 1;
    }

    void insert(int idx, int parent)
    {
        node_pool[parent].child.emplace_back(idx);
        node_pool[idx].depth = node_pool[parent].depth + 1;
        node_pool[idx].parent = parent;
        node_pool[idx].child.clear();
    }

    int calc(){
        q.init();
        q.push(1);
        int prev = 1;
        int ans = 0;
        while(!q.empty())
        {
            int cur = q.pop();
            int size = node_pool[cur].child.size();
            for(int i=0; i<size; ++i)
            {
                q.push(node_pool[cur].child[i]);
            }

            ans += len(prev, cur);
            prev = cur;
        }
        return ans;
    }

private:
    int len(int start, int end)
    {
        int cnt = 0;
        while(node_pool[start].depth != node_pool[end].depth)
        {
            if(node_pool[start].depth > node_pool[end].depth)
            {
                start = node_pool[start].parent;
            }
            else{
                end = node_pool[end].parent;
            }
            cnt++;
        }

        while(start != end)
        {
            cnt += 2;
            start = node_pool[start].parent;
            end = node_pool[end].parent;
        }
        return cnt;
    }
};

Tree tree {};

int main(){
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    for(int test=1; test<=T; ++test)
    {
        tree.init();
        scanf("%d", &N);
        for(int i=2; i<=N; ++i){
            int parent;
            scanf("%d", &parent);
            tree.insert(i, parent);
        }
        printf("#%d %d\n", test, tree.calc());
    }
    return 0;
}

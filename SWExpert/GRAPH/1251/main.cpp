#include <stdio.h>
#include <queue>
#include <cmath>

int N;
double E;
int posX[1001];
int posY[1001];
int parent[1001];

struct Info{
    int start;
    int end;
    double cost;

};

struct CMP{
    bool operator ()(const Info &a, const Info &b) const{
        return a.cost > b.cost;
    }
};


int findParent(int num)
{
    if(num == parent[num])
        return num;
    return num = findParent(parent[num]);
}

void merge(int start, int end)
{
    int n1 = findParent(start);
    int n2 = findParent(end);
    parent[n2] = n1;
}

int main(){
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    for(int test=1; test<=2; ++test)
    {
        scanf("%d", &N);
        std::priority_queue<Info,std::vector<Info>, CMP> pq;

        for(int i=0; i<N; ++i){
            scanf("%d", &posX[i]);
            parent[i] = i;
        }

        for(int i=0; i<N; ++i){
            scanf("%d", &posY[i]);
        }

        scanf("%lf", &E);
        for(int i=0; i<N; ++i){
            for(int j=i+1; j<N; ++j){
                double dis = sqrt(pow(posX[i] - posX[j], 2) + pow(posY[i] - posY[j], 2));
                pq.push({i, j, dis});
            }
        }

        double res = 0;
        while(!pq.empty())
        {
            Info cur = pq.top();
            pq.pop();

            if(findParent(cur.start) != findParent(cur.end)){
                merge(cur.start, cur.end);
                res += E * pow(cur.cost, 2);
            }
        }

        printf("#%d %d\n", test,(int)round(res));
    }


    return 0;
}

#include <stdio.h>

#define INF 9999999

int min(int a, int b)
{
    return a>b ? b : a;
}

int graph[101][101];

int main(){
    freopen("input.txt", "r", stdin);

    int N, M;

    scanf("%d", &N);
    scanf("%d", &M);

    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            graph[i][j] = INF;
        }
    }

    for(int i=0; i<M; ++i)
    {
        int from, to, w;
        scanf("%d %d %d", &from, &to, &w);
        graph[from-1][to-1] = min(graph[from-1][to-1], w);
    }

    for(int i=0; i<N; ++i){             // i vertex 경유 
        for(int j=0; j<N; ++j){         // from vertex
            for(int k=0; k<N; ++k){     // to vertex
                graph[j][k] = min(graph[j][k], graph[j][i] + graph[i][k]);
            }
        }
    }

    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            printf("%d ", graph[i][j] == INF || i==j ? 0 : graph[i][j]);
        }
        printf("\n");
    }
    return 0;

}

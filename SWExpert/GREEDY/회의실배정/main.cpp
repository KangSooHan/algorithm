#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> time;

struct cmp{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b){
        if(a.second == b.second) return a.first <= b.first;
        return a.second <= b.second;
    }
};

int main(){
    freopen("input.txt", "r", stdin);
    
    int n;
    scanf("%d", &n);

    for(int i=0; i<n; ++i){
        int s, e;
        scanf("%d %d", &s, &e);
        time.emplace_back(make_pair(s, e));
    }

    sort(time.begin(), time.end(), cmp());

    int cnt = 1;
    int t= time[0].second;
    for(int i=1; i<n; ++i){
        if(time[i].first >= t) {
            cnt++;
            t = time[i].second;
        }
    }
    printf("%d\n", cnt);
}

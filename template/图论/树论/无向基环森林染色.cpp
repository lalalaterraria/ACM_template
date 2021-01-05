#include<bits/stdc++.h>
using namespace std;
int col[100010];
vector<int> e[100010];
int dfs(int u,int fa){
    if(col[u]) return 1;
    col[u]=1;int ret=0;
    for(auto &v:e[u]){
        if(v==fa)continue;
        if(ret^=dfs(v,u)) col[u]=2;
    }
    return ret;
}
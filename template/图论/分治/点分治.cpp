#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e4 + 10;
const int lim = 1e7 + 10;
vector<pair<int,int> > e[maxn];
int sz[maxn],vis[maxn];
int dis[lim];
vector<int> op;
int k[maxn], ans[maxn]; // 当前询问的距离, 答案
int n,m;
void dfs(int u, int fa, int dep,int flg){
    if(dep>lim) return;
    dis[dep]++;
    op.push_back(dep);
    for(int i=1;i<=m;i++){
        if(k[i]-dep>=0) ans[i]+=flg*dis[k[i]-dep];
    }
    for(auto it:e[u]){
        int v = it.first, w = it.second;
        if(v==fa || vis[v]) continue;
        dfs(v, u, dep + w, flg);
    }
}

void dfs_cal(int u, int dep, int flg){
    dfs(u, 0, dep, flg);
    // 清空dis
    for(auto &it:op) dis[it]--;
    // 不要忘了清空op
    op.clear();
}

void dfs_rt(int u, int fa,int tot,int &rt){
    int mx = 0; sz[u] = 1;
    for(auto it:e[u]){
        int v = it.first;
        if(v==fa || vis[v]) continue;
        dfs_rt(v, u, tot, rt);
        sz[u] += sz[v];
        mx = max(mx, sz[v]);
    }
    mx = max(mx, tot - sz[u]);
    if(mx <= tot/2) rt = u;
}

void dfs_div(int u,int tot){
    int rt; dfs_rt(u, 0, tot, rt);

    // 注意换根
    dfs_cal(rt, 0, 1);
    vis[rt] = 1;
    for(auto it:e[rt]){
        int v = it.first, w = it.second;
        if(vis[v]) continue;
        dfs_cal(v, w, -1);
        dfs_div(v, sz[rt]>sz[v]?sz[v]:tot-sz[rt]);
    }
    vis[rt] = 0;
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i = 1; i <= n; ++i) e[i].clear();
    for(int i=1;i<n;i++){
        int a,b,w;cin>>a>>b>>w;
        e[a].push_back({b,w});
        e[b].push_back({a,w});
    }
    for(int i=1;i<=m;i++) cin>>k[i];

    dfs_div(1,n);
    for(int i=1;i<=m;i++){
        cout<<(ans[i]?"AYE":"NAY")<<endl;
    }
}
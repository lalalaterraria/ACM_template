#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
vector<int> e[N];
int dfn[N],low[N],tot,s[N],tp;
int col[N],sz[N],c;
void tarjan(int u){
    low[u]=dfn[u]=++tot,s[++tp]=u;
    for(auto &v:e[u]){
        if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
        if(!col[v]) low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        for(++c;s[tp]!=u;)
        col[s[--tp]]=c,sz[c]++;
        col[s[--tp]]=c,sz[c]++;
    }
}
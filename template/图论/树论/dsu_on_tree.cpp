// sum_i sum_j [col_i ^ col_j == col_lca](i^j)
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("sse,sse2,sse3,sse4,avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1100010;
vector<int> e[maxn];
int col[maxn],sz[maxn],ms[maxn];
void dfs_pre(int u,int fa) {
	sz[u]=1;
	for(auto &v:e[u]){
		if(v==fa)continue;
		dfs_pre(v,u);
		if(sz[v]>sz[ms[u]]) ms[u]=v;
		sz[u]+=sz[v];
	}
}
int tp[maxn][20][2];
ll now_ans=0;
void dfs_cal(int u,int fa,int flg){
	for(int i=0;i<20;i++){
		tp[col[u]][i][(u>>i)&1]+=flg;
	}
	for(auto &v:e[u]){
        if(v==fa) continue;
        dfs_cal(v,u,flg);
    }
}
void dfs_ans(int u,int fa,int rt){
	if(col[rt]){
		for(int i=0;i<20;i++){
			now_ans+=(1ll<<i)*tp[col[u]^col[rt]][i][((u>>i)&1)^1];
		}
	}
	for(auto &v:e[u]){
        if(v==fa) continue;
        dfs_ans(v,u,rt);
    }
}
// flg暴力标记
void dfs(int u,int fa,bool flg){
	for(auto &v:e[u]){
	    if(v==fa||v==ms[u]) continue;
        dfs(v,u,1);
    }
	if(ms[u]) dfs(ms[u],u,0);

	for(int i=0;i<20;i++){
		tp[col[u]][i][(u>>i)&1]++;
	}

	for(auto &v:e[u]){
        if(v==fa||v==ms[u]) continue;
        dfs_ans(v,u,u);
		dfs_cal(v,u,1);
    }

	if(flg) dfs_cal(u,fa,-1);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++) cin>>col[i];
	for(int i=1;i<n;i++){
		int a,b;cin>>a>>b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	dfs_pre(1,0);
	dfs(1,0,0);
	cout<<now_ans<<endl;
}
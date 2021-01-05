#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll inf = 1e18;
const int maxn = 1e5+10;
struct Dinic { // 最小费用最大流，类dinic，spfa增广
	struct Edge { int v, rev; ll cap, cot; };
	vector<Edge> G[maxn];
	ll dis[maxn];
	int cur[maxn], vis[maxn], n, sp, tp;
	void init(int nn) {
		n = nn;
		for (int i = 1; i <= n; i++) G[i].clear();
	}
	void add(int u, int v, ll cap, ll cot) {
		// cout<<"add:"<<u<<" "<<v<<" "<<cap<<" "<<cot<<endl;
		G[u].push_back({ v, int(G[v].size()), cap, cot });
		G[v].push_back({ u, int(G[u].size()) - 1, 0, -cot });
	}
	int bfs() {
		queue<int> q;
		for (int i = 1; i <= n; i++) dis[i] = inf, vis[i] = 0;
		dis[sp] = 0, q.push(sp), vis[sp] = 1;
		while (!q.empty()) {
			int u = q.front(); q.pop(); vis[u] = 0;
			for (Edge &e : G[u]) {
				if (e.cap && dis[e.v] > dis[u] + e.cot) {
					dis[e.v] = dis[u] + e.cot;
					if (!vis[e.v]) q.push(e.v), vis[e.v] = 1;
				}
			}
		} return dis[tp] != inf;
	}
	ll dfs(int u, ll flow) {
		if (u == tp || !flow) return flow;
		ll ret = 0, tmp; vis[u] = 1;
		for (int i = cur[u]; i < int(G[u].size()); i++) {
			Edge &e = G[u][i];
			if (!vis[e.v] && dis[e.v] == dis[u] + e.cot 
			&& (tmp = dfs(e.v, min(e.cap, flow - ret)))) {
				ret += tmp, e.cap -= tmp, G[e.v][e.rev].cap += tmp;
				if (ret == flow) { vis[u] = 0; return ret; }
			}
		}
		if (!ret) vis[u] = 1;
		return ret;
	}
	pair<ll, ll> solve(int s, int t) {
		sp = s, tp = t;
		ll mf = 0, mc = 0;
		while (bfs()) {
			for (int i = 1; i <= n; i++) cur[i] = 0;
			ll tmp = dfs(sp, inf);
			mf += tmp, mc += tmp * dis[tp];
		}
		return { mf, mc };
	}
} dinic;

int main(){
	int n,m,s,t;cin>>n>>m>>s>>t;
	// 初始化别忘
	dinic.init(n);
	for(int i=1;i<=m;i++){
		int a,b,c,d;cin>>a>>b>>c>>d;
		dinic.add(a,b,c,d);
	}
	auto ans=dinic.solve(s,t);
	cout<<ans.first<<" "<<ans.second<<endl;
}
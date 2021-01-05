#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll inf=1e18;
const int maxn=1e5+10;
struct Dinic {
	struct Edge { int v, rev; ll cap; };
	vector<Edge> G[maxn];
	int dis[maxn], cur[maxn], n, sp, tp;
	void init(int nn) {
		n = nn;
		for (int i = 1; i <= n; i++) G[i].clear();
	}
	// 默认有向边，add(u, v, w, w)无向
	void add(int u, int v, ll cap, ll rcap = 0) {
		G[u].push_back({ v, int(G[v].size()), cap });
		G[v].push_back({ u, int(G[u].size()) - 1, rcap });
	}
	int bfs() {
		queue<int> q;
		for (int i = 1; i <= n; i++) dis[i] = 0;
		dis[sp] = 1, q.push(sp);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (Edge &e : G[u]) {
				if (e.cap && !dis[e.v]) {
					dis[e.v] = dis[u] + 1;
					if (e.v == tp) return 1;
					q.push(e.v);
				}
			}
		}
		return 0;
	}
	ll dfs(int u, ll flow) {
		if (u == tp || !flow) return flow;
		ll ret = 0, tmp;
		for (int &i = cur[u]; i < int(G[u].size()); i++) {
			Edge &e = G[u][i];
			if (dis[e.v] == dis[u] + 1 && (tmp = dfs(e.v, min(e.cap, flow - ret)))) {
				e.cap -= tmp, G[e.v][e.rev].cap += tmp, ret += tmp;
				if (ret == flow) return ret;
			}
		}
		if (!ret) dis[u] = 0;
		return ret;
	}
	ll solve(int s, int t) {
		sp = s, tp = t;
		ll ret = 0;
		while (bfs()) {
			for (int i = 1; i <= n; i++) cur[i] = 0;
			ret += dfs(sp, inf);
		}
		return ret;
	}
} dinic;

int main(){
	int n,m,s,t;cin>>n>>m>>s>>t;
	// 初始化别忘
	dinic.init(n);
	for(int i=1;i<=m;i++){
		int a,b,c;cin>>a>>b>>c;
		dinic.add(a,b,c);
	}
	cout<<dinic.solve(s,t)<<endl;
}
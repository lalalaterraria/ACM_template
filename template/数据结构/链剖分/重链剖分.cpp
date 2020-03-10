// https://loj.ac/problem/139
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define ll long long
const int maxn = 1e5 + 10;
vector<int> e[maxn];
// 子树大小，重儿子，父亲，深度
int sz[maxn], son[maxn], fa[maxn], dep[maxn];
void dfs1(int u) {
	sz[u] = 1; son[u] = 0; dep[u] = dep[fa[u]] + 1;
	for (auto &v:e[u]) {
		if (v == fa[u]) continue;
		fa[v] = u; dfs1(v);
		sz[u] += sz[v];
		son[u] = sz[v] > sz[son[u]] ? v : son[u];
	}
}
// 重儿子序，重链头, num
int dfn[maxn], top[maxn], num;
void dfs2(int u, int t) {
	dfn[u] = ++num; top[u] = t;
	if (son[u]) dfs2(son[u], t);
	for (auto &v:e[u]) {
		if (v != fa[u] && v != son[u]) dfs2(v, v);
	}
}
// 最近公共祖先
int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

// 线段树
#define ls rt<<1
#define rs rt<<1|1
#define mid (l+r)/2
ll sum[maxn<<2], laze[maxn<<2];
void php(int rt) { sum[rt] = sum[ls] + sum[rs]; }
void phd(int rt,int l,int r) {
	if (laze[rt] == 0)return;
	laze[ls] += laze[rt];
	laze[rs] += laze[rt];

	sum[ls] += laze[rt] * (mid - l + 1);
	sum[rs] += laze[rt] * (r - mid);

	laze[rt] = 0;
}
void upd(int rt, int l, int r, int x, int y, int val) {
	if (x > y)return;
	if (x <= l && r <= y) {
		sum[rt] += 1ll * (r - l + 1)*val;
		laze[rt] += val;
		return;
	}
	phd(rt, l, r);
	if (x <= mid)upd(ls, l, mid, x, y, val);
	if (y > mid)upd(rs, mid + 1, r, x, y, val);
	php(rt);
}
ll que(int rt, int l, int r, int x, int y) {
	if (x > y)return 0;
	if (x <= l && r <= y) {
		return sum[rt];
	}
	phd(rt, l, r);
	ll ret = 0;
	if (x <= mid)ret += que(ls, l, mid, x, y);
	if (y > mid)ret += que(rs, mid + 1, r, x, y);
	return ret;
}
void build(int rt,int l,int r,ll a[]){
    if(l==r){
        sum[rt] = a[l];
        return;
    }
    build(ls, l, mid, a);
    build(rs, mid+1, r, a);
    php(rt);
}

// 路径修改查询
void upd1(int n, int u, int v, int val) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		upd(1, 1, n, dfn[top[u]], dfn[u], val);
		u = fa[top[u]];
	}
	if (dep[u] < dep[v])swap(u, v);
	upd(1, 1, n, dfn[v], dfn[u], val);
}
ll que1(int n, int u, int v) {
	ll ret = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		ret += que(1, 1, n, dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	if (dep[u] < dep[v])swap(u, v);
	ret += que(1, 1, n, dfn[v], dfn[u]);
	return ret;
}

// 子树修改查询
void upd2(int n, int u, int val,int rt) {

	// 注意只能进入一条修改分支
	if (u == rt) upd(1, 1, n, 1, n, val);
	else if (dfn[u] <= dfn[rt] && dfn[rt] <= dfn[u] + sz[u] - 1) {
		int v = rt;
		while (top[v] != top[u] && fa[v] != u)v = top[fa[v]];
		if (fa[v] != u) v = son[u];
		upd(1, 1, n, 1, dfn[v] - 1, val);
		upd(1, 1, n, dfn[v] + sz[v], n, val);
	}
	else upd(1, 1, n, dfn[u], dfn[u] + sz[u] - 1, val);

	// 不换根
    // upd(1, 1, n, dfn[u], dfn[u] + sz[u] - 1, val);
}
ll que2(int n,int u,int rt) {

	// 查询因为是return所以不用else if
	if (u == rt) return que(1, 1, n, 1, n);
	else if (dfn[u] < dfn[rt] && dfn[rt] <= dfn[u] + sz[u] - 1) {
		int v = rt;
		while (top[v] != top[u] && fa[v] != u)v = top[fa[v]];
		if (fa[v] != u) v = son[u];
		return que(1, 1, n, 1, dfn[v] - 1)
		+ que(1, 1, n, dfn[v] + sz[v], n);
	}
    else return que(1, 1, n, dfn[u], dfn[u] + sz[u] - 1);

	// 不换根
	// return que(1, 1, n, dfn[u], dfn[u] + sz[u] - 1);
}

ll a[maxn], b[maxn];
signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 2; i <= n; i++) {
		int u; cin >> u;
		e[i].push_back(u);
		e[u].push_back(i);
	}

    // 预处理
	int rt = 1;
	dfs1(rt); dfs2(rt, rt);
	for (int i = 1; i <= n; i++) b[dfn[i]] = a[i];
    build(1, 1, n, b);

	int m; cin >> m;
	for (int i = 1; i <= m; i++) {
		int tag, u, v, k; cin >> tag;
		if (tag == 1) {
            // 换根：将一个指定的节点设置为树的新根。
			cin >> u;
            rt = u;
		}
		else if (tag == 2) {
            // 修改路径权值：给定两个节点，将这两个节点间路径上的所有节点权值（含这两个节点）增加一个给定的值。
			cin >> u >> v >> k;
			upd1(n, u, v, k);
		}
		else if (tag == 3) {
            // 修改子树权值：给定一个节点，将以该节点为根的子树内的所有节点权值增加一个给定的值。
			cin >> u >> k;
			upd2(n, u, k, rt);
		}
		else if (tag == 4) {
            // 询问路径：询问某条路径上节点的权值和。
			cin >> u >> v;
			cout << que1(n, u, v) << endl;
		}
		else if (tag == 5) {
            // 询问子树：询问某个子树内节点的权值和。
			cin >> u;
			cout << que2(n, u, rt) << endl;
		}
	}
}
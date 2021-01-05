#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 5e4 + 10;
// 注意这个模数是2e9且爆int的
const ll mod = 2281701377;
const ll inv2 = (mod+1)/2;

ll mypow(ll a, ll b) {
	ll ret = 1;
	while (b) {
		if (b & 1)ret = ret * a%mod;
		a = a * a%mod; b >>= 1;
	}
	return ret;
}

int rev[maxn*4];
void ntt(ll x[], int len, int on) {
	for (int i = 0; i < len; i++) rev[i] = (i & 1)*(len >> 1) + (rev[i >> 1] >> 1);
	for (int i = 0; i < len; i++) if (i < rev[i]) swap(x[i], x[rev[i]]);
	for (int i = 2; i <= len; i <<= 1) {
		ll gn = mypow(3, (mod - 1) / i);
		int d = i >> 1;
		for (int j = 0; j < len; j += i) {
			ll g = 1;
			for (int k = j; k < j + d; k++) {
				ll a = x[k], b = g * x[k + d] % mod;
				(x[k] = a + b) < mod ? 0 : x[k] -= mod;
				(x[k + d] = a - b) >= 0 ? 0 : x[k + d] += mod;
				g = gn * g % mod;
			}
		}
	}
	if (on == -1) {
		reverse(x + 1, x + len);
		ll inv = mypow(len, mod - 2);
		for (int i = 0; i < len; i++) {
			x[i] = x[i] * inv%mod;
		}
	}
}

vector<int> e[maxn];
int sz[maxn],vis[maxn];
ll x[maxn*4],ans[maxn*4];
int dfs(int u, int fa, int dep){
    x[dep]++;int ret=dep;
    for(auto &v:e[u]){
        if(v==fa || vis[v]) continue;
        ret=max(ret,dfs(v, u, dep+1));
    }
    return ret;
}

void dfs_cal(int u, int dep, int flg){
    int mx=dfs(u, 0, dep);
    int len=1<<(32-__builtin_clz(mx+mx));
    ntt(x,len,1);
    for(int i=0;i<len;i++) x[i]=x[i]*x[i]%mod;
    ntt(x,len,-1);
    for(int i=0;i<len;i++){
        ans[i]=(ans[i]+flg*x[i]+mod)%mod;
        x[i]=0;
    }
}

void dfs_rt(int u, int fa,int tot,int &rt){
    int mx = 0; sz[u] = 1;
    for(auto v:e[u]){
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
    for(auto v:e[rt]){
        if(vis[v]) continue;
        dfs_cal(v, 1, -1);
        dfs_div(v, sz[rt]>sz[v]?sz[v]:tot-sz[rt]);
    }
    vis[rt] = 0;
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cout<<setprecision(9)<<fixed;
    int n; cin>>n;
    for(int i = 1; i <= n; ++i) e[i].clear();
    for(int i=1;i<n;i++){
        int a,b;cin>>a>>b;
        e[a].push_back(b);
        e[b].push_back(a);
    }

    dfs_div(1,n);
    // 不折半会爆mod
    for(int i=1;i<=n;i++) ans[i]=ans[i]*inv2%mod;

    ll tot=ans[1],p=0;
    for(int i=2;i<=n;i++){
        tot=(tot+ans[i])%mod;int flg=0;
        for(int j=2;j*j<=i;j++){
            if(i%j==0){
                flg=1;
                break;
            }
        }
        if(flg==0) p=(p+ans[i])%mod; 
    }
    cout<<(double)p/tot<<endl;
}
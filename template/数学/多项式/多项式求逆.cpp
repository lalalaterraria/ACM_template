#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 2100000
const ll mod = 998244353;

ll mypow(ll a, ll b) {
	ll ret = 1;
	while (b) {
		if (b & 1)ret = ret * a%mod;
		a = a * a%mod; b >>= 1;
	}
	return ret;
}

int rev[maxn];
void ntt(ll x[], int len, int on) {
	for (int i = 0; i < len; i++)rev[i] = (i & 1)*(len >> 1) + (rev[i >> 1] >> 1);
	for (int i = 0; i < len; i++)if (i < rev[i])swap(x[i], x[rev[i]]);
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
		int inv = mypow(len, mod - 2);
		for (int i = 0; i < len; i++) {
			x[i] = x[i] * inv%mod;
		}
	}
}

ll c[maxn];
void work(int now,ll a[],ll b[]) {
	if(now==1) {b[0]=mypow(a[0],mod-2);return;}
	work(now+1>>1,a,b); // now/2向上取整
	int len=1<<(32-__builtin_clz(now));
	
	for(int i=0;i<len;++i) c[i]=i<now?a[i]:0;
	ntt(b,len,1),ntt(c,len,1);
	for(int i=0;i<len;++i)
		b[i]=1LL*(2-1LL*c[i]*b[i]%mod+mod)%mod*b[i]%mod;
	ntt(b,len,-1);
	for(int i=now;i<len;++i) b[i]=0;
}

ll a[maxn], b[maxn];
int main(){

	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	for(int i=0;i<n;++i) cin>>a[i];
	work(n,a,b);
	for(int i=0;i<n;++i) cout<<b[i]<<" \n"[i==n-1];
}
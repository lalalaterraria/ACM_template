#include<iostream>
#include<algorithm>
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

void work(ll x[], ll y[], int len) {
	ntt(x, len, 1); ntt(y, len, 1);
	for (int i = 0; i < len; i++)x[i] = x[i] * y[i] % mod;
	ntt(x, len, -1);
}

// f(n) = h(x)+∑(i=1 to n)g(i)*f(n-i), f(0)=1
// 那么开始讲f赋值为h即可
ll f[maxn],g[maxn];
ll a[maxn],b[maxn];
void cdq(int l,int r,int len){
	if(l==r) return;
	int mid=l+r>>1;

	//中序保证左半已经算完
	cdq(l,mid,len>>1);

	for(int i=0;i<len;i++)a[i]=i<len/2?f[l+i]:0,b[i]=g[i];
	ntt(a,len,1);ntt(b,len,1);
	for(int i=0;i<len;i++)a[i]=a[i]*b[i]%mod;
	ntt(a,len,-1);
	for(int i=mid+1;i<=r;i++)f[i]=(f[i]+a[i-l])%mod;

	cdq(mid+1,r,len>>1);
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	for(int i=1;i<n;i++)cin>>g[i];
	int len=1;while(len<n)len<<=1;

	f[0]=1; // 非常关键
	cdq(0,len-1,len);
	
	for(int i=0;i<n;i++)cout<<f[i]<<" ";cout<<endl;
}
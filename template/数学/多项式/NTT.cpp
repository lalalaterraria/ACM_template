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

void work(ll x[], int m, ll y[], int n) {

	//这里的x和y都包含常数项0次，m和n为最高次
	int len = 1;
	while (len <= m + n)len <<= 1;

	ntt(x, len, 1); ntt(y, len, 1);
	for (int i = 0; i < len; i++)x[i] = x[i] * y[i] % mod;
	//解的时候注意下是否x,y都要解(复利用)
	ntt(x, len, -1);

	for (int i = 0; i <= m + n; i++) cout << x[i] << " "; cout << endl;
}

ll x[maxn], y[maxn];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m; cin >> n >> m;
	for (int i = 0; i <= n; i++)cin >> x[i];
	for (int i = 0; i <= m; i++)cin >> y[i];
	work(x, m, y, n);
}
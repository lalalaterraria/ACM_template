#include<bits/stdc++.h>
using namespace std;
/*

// g 是mod(r*2^k+1)的原根

P 					r	k	g
3   				1   1   2
5   				1   2   2
17  				1   4   3
97  				3   5   5
193 				3   6   5
257 				1   8   3
7681    			15  9   17
12289   			3   12  11
40961   			5   13  3
65537   			1   16  3
786433  			3   18  10
5767169 			11  19  3
7340033 			7   20  3
23068673    		11  21  3
104857601   		25  22  3
167772161   		5   25  3
469762049   		7   26  3
998244353			119 23  3
1004535809  		479 21  3
2013265921  		15  27  31
2281701377  		17  27  3
3221225473  		3   30  5
75161927681 		35  31  3
77309411329 		9   33  7
206158430209    	3   36  22
2061584302081   	15  37  7
2748779069441   	5   39  3
6597069766657   	3   41  5
39582418599937 		9   42  5
79164837199873  	9   43  5
263882790666241 	15  44  7
1231453023109121    35  45  3
1337006139375617    19  46  3
3799912185593857    27  47  5
4222124650659841    15  48  19
7881299347898369    7   50  6
31525197391593473   7   52  3
180143985094819841  5   55  6
1945555039024054273 27  56  5
4179340454199820289 29  57  3
*/

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
	for (int i = 0; i < len; i++) rev[i] = (i & 1)*(len >> 1) + (rev[i >> 1] >> 1);
	for (int i = 0; i < len; i++) if (i < rev[i])swap(x[i], x[rev[i]]);
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

void work(ll x[], int n, ll y[], int m) {

	// 这里的x和y都包含常数项0次，m和n为最高次
	// 注意填充0
	int len = 1<<(32-__builtin_clz(n + m));
	for (int i = n + 1; i < len; i++) x[i] = 0;
    for (int i = m + 1; i < len; i++) y[i] = 0;

	ntt(x, len, 1); ntt(y, len, 1);
	for (int i = 0; i < len; i++)x[i] = x[i] * y[i] % mod;
	// 解的时候注意下是否x,y都要解(复利用)
	ntt(x, len, -1);

	// for (int i = 0; i <= m + n; i++) cout << x[i] << " "; cout << endl;
}

ll x[maxn], y[maxn];
int main(){

	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m; cin >> n >> m;
	for (int i = 0; i <= n; i++)cin >> x[i];
	for (int i = 0; i <= m; i++)cin >> y[i];
	work(x, m, y, n);
}
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

inline ll mul(ll a, ll b, ll p) {
    return (__int128_t)a * b % p;
}
ll mypow(ll a, ll b, ll mod) {
	ll ret = 1;
	while (b) {
		if (b & 1) ret = mul(ret, a, mod);
		a = mul(a, a, mod); b >>= 1;
	}
	return ret;
}

mt19937 rd(time(0));
struct Mill {
	// 1到tot，fac={质数，次数}。
	// fac有排序从小到大。
    ll n,bk[22000]; pair<ll,int> fac[22000]; int tot;
    const int C = 255;
    const int S = 10;
    bool check(ll a, ll n) {
        ll m = n - 1, x, y = 0;int j = 0;
        while((m & 1)==0) m >>= 1, j++;
        x = mypow(a, m, n);
        for (int i = 1; i <= j; x = y, i++) {
            y = mul(x, x, n);
            if (y == 1 && x != 1 && x != n - 1) return 1;
        }
        return y != 1;
    }
    bool miller_rabin(ll n) {
        if (n < 2) return 0;
        else if (n == 2) return 1;
        else if ((n & 1)==0) return 0;
        for (int i = 0; i < S; ++i) {
            if (check(rd() % (n - 1) + 1, n)) {
                return 0;
            }
        }
        return 1;
    }
    ll pollard_rho(ll n, int c) {
        ll k = 2, x = rd() % n, y = x, d;
        for(ll i = 2;;i++) {
            x = (mul(x, x, n) + c) % n;
            d = __gcd(y - x, n);
            if (d > 1 && d < n) return d;
            if (y == x) return n;
            if (i == k) y = x, k <<= 1;
        }
    }
    void findfac(ll n, int c) {
        if (n == 1) return;
        if (miller_rabin(n)) {
            bk[++*bk] = n;
            return;
        }
        ll m = n;
        while (m == n) m = pollard_rho(n, c--);
        findfac(m, c);
        findfac(n / m, c);
    }
    void gao(ll nn) {
        n = nn; *bk = 0, tot = 1;
        findfac(n, C);
        sort(bk + 1, bk + 1 + *bk);
        fac[1] = {bk[1], 1};
        for (int i = 2; i <= *bk; ++i) {
            if (bk[i] == bk[i - 1]) fac[tot].second++;
            else fac[++tot] = {bk[i], 1};
        }
    }
}mill;

int main(){
	int t;cin>>t;
	while(t--){
		ll x;cin>>x;
		mill.gao(x);
		if(mill.tot==1&&mill.fac[1].second==1) cout<<"Prime"<<endl;
		else cout<<mill.fac[mill.tot].first<<endl;
	}
}
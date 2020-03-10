#include<iostream>
#include<algorithm>
#include<vector>

#define ll long long
using namespace std;

#define lowb(x) ((x)&(-x))
#define maxn 2050

int n, m;
ll c1[maxn][maxn], c2[maxn][maxn], c3[maxn][maxn], c4[maxn][maxn];

void add(ll x, ll y, ll dt) {
	for (ll i = x; i <= n; i += lowb(i))
		for (ll j = y; j <= m; j += lowb(j)) {
			c1[i][j] += dt;
			c2[i][j] += dt * y;
			c3[i][j] += dt * x;
			c4[i][j] += dt * x * y;
		}
}

ll calc(ll x, ll y) {
	ll ret = 0;
	for (ll i = x; i > 0; i -= lowb(i))
		for (ll j = y; j > 0; j -= lowb(j)) {
			ret = ret
				+ (x + 1) * (y + 1) * c1[i][j]
				- (x + 1) * c2[i][j]
				- (y + 1) * c3[i][j]
				+ c4[i][j];
		}
	return ret;
}

void upd(ll X1, ll Y1, ll X2, ll Y2, ll dt) {
	add(X1, Y1, dt);
	add(X2 + 1, Y1, -dt);
	add(X1, Y2 + 1, -dt);
	add(X2 + 1, Y2 + 1, dt);
}
ll que(ll X1, ll Y1, ll X2, ll Y2) {
	return
		calc(X2, Y2) + calc(X1 - 1, Y1 - 1) -
		calc(X1 - 1, Y2) - calc(X2, Y1 - 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	int tag, a, b, c, d, x;
	while (cin >> tag >> a >> b >> c >> d) {
		if (tag == 1) {
			cin >> x;
			upd(a, b, c, d, x);
		}
		else cout << que(a, b, c, d) << endl;
	}
}
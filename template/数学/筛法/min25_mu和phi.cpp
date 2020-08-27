// 前置筛/phi/mu筛，验了2^31，应该可以过 LL，记得改maxn
#include<bits/stdc++.h>
using namespace std;
#define LL long long

//根号n大小
const int maxn = 1e5+10;
LL g[2][maxn<<1], h[2][maxn];
int id1[maxn], id2[maxn], m; LL w[maxn << 1];
int P[maxn],cnt;bool vis[maxn];
LL n;int sqr;

inline int ind(LL x) {
	return x <= sqr ? id1[x] : id2[n / x];
}

LL Smu(LL x, int j) {
	if (x <= 1 || P[j] > x)return 0;

	//ret = G(x) - H(j - 1)
	LL ret = - g[0][ind(x)] + h[0][j-1];
	for (int k = j; k <= cnt && 1LL * P[k] * P[k] <= x; k++) {
		for (LL pi = P[k], i = 1; pi*P[k] <= x; pi *= P[k], i++) {

			//ret += s * f(p^i) + f(p ^ (i + 1))
			ret += Smu(x/pi, k+1) * (i==1?-1:0);
		}
	}
	return ret;
}

LL Sphi(LL x, int j) {
	if (x <= 1 || P[j] > x)return 0;

	//ret = G(x) - H(j - 1)
	LL ret = (g[1][ind(x)] - g[0][ind(x)]) - (h[1][j-1] - h[0][j-1]);
	for (int k = j; k <= cnt && 1LL * P[k] * P[k] <= x; k++) {
		for (LL pi = P[k]; pi*P[k] <= x; pi *= P[k]) {

			//ret += s * f(p^i) + f(p ^ (i + 1))
			ret += Sphi(x/pi, k+1) * pi/P[k]*(P[k]-1) + pi*(P[k]-1);
		}
	}
	return ret;
}

// 注意对每个不同的n都需要初始化
void solve() {

	//init
	m = 0, cnt = 0, sqr = sqrt(n);
	memset(vis, 0, sqr + 10);
	
	//筛质数，算h
	for (int i = 2; i <= sqr; i++) {
		if (!vis[i]) {
			P[++cnt] = i;
			h[0][cnt] = h[0][cnt-1] + 1;
			h[1][cnt] = h[1][cnt-1] + i;
		}
		for (int j = 1; j <= cnt && P[j]*i <= sqr; j++) {
			vis[i*P[j]] = 1;
			if (i%P[j] == 0)break;
		}
	}

	//计算g的边界:自然幂数和;g(1)不算,最后记得减一
	for (LL i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i); w[++m] = n / i;
		if (w[m] <= sqr) id1[w[m]] = m;
		else id2[n / w[m]] = m;

		g[0][m] = w[m] - 1;
		g[1][m] = w[m] * (w[m] + 1) / 2 - 1;
	}

	//完成g的计算:自然幂数质数和;滚动数组
	for (int j = 1; j <= cnt; j++) {
		for (int i = 1; i <= m && 1LL * P[j] * P[j] <= w[i]; i++) {
			//g[n]=g[n]-P[j]^k*(g[n/P[j]]-h[j-1])

			g[0][i] = g[0][i] - (g[0][ind(w[i]/P[j])]-h[0][j - 1]);
			g[1][i] = g[1][i] - P[j]*(g[1][ind(w[i]/P[j])] - h[1][j-1]);
		}
	}

	//输出S(n,1)+F(1),注意符号
	cout<<(Sphi(n, 1) + 1)<<" "<<(Smu(n,1) + 1)<<endl;
}
int main() {
	int t;cin>>t;
	while(t--){
		cin>>n;solve();
	}
}
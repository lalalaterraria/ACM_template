#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
#define LL long long

//高性能场合
#define M(x)		((x)%mod)
#define SFAdd(x,y)	((x+=y)<mod?x:x-=mod)		//int正数+=
#define SFSub(x,y)	((x-=y)<0?x+=mod:x)			//int正数-=
#define Add(a,x,y)	((a=(x)+(y))<mod?a:a-=mod)	//int正数相加
#define Sub(a,x,y)	((a=(x)-(y))<0?a+=mod:a)	//int正数相减

/*
模数备用
const LL mod = 998244353;
const LL inv2 = (mod + 1) / 2;
const LL inv6 = (mod + 1) / 6;
*/

const LL mod = 1e9 + 7;
const LL inv2 = (mod + 1) / 2;
const LL inv6 = (mod + 1) / 6;

//根号n大小
const int maxn = 1e5 + 10;

//(h,g)->(H,G)->S
//自然幂数质数和(前半,因子项)->多项式质数前缀和(前半，因子项)->多项式前缀和
LL g[3][maxn<<1], h[3][maxn];
int id1[maxn], id2[maxn], m; LL w[maxn << 1];
int P[maxn],cnt;bool vis[maxn];
LL n;int sqr;

inline int ind(LL x) {
	return x <= sqr ? id1[x] : id2[n / x];
}

//这个是f(p^i)计算函数
inline int fpi(LL pi) {
	return M(pi * (pi - 1));
}

//这里是核心的递归表达式式
LL S(LL x, int j) {
	if (x <= 1 || P[j] > x)return 0;

	//ret = G(x) - H(j - 1)
	LL ret = (g[2][ind(x)] - g[1][ind(x)]) - (h[2][j - 1] - h[1][j - 1]);
	for (int k = j; k <= cnt && 1LL * P[k] * P[k] <= x; k++) {
		for (LL pi = P[k], i = 1; pi*P[k] <= x; pi *= P[k], i++) {

			//ret += s * f(p^i) + f(p ^ (i + 1))
			ret += M(S(x / pi, k + 1)*fpi(pi)) + fpi(M(pi*P[k]));
		}
	}
	return M(ret);
}

void solve() {
	//init
	m = 0; cnt = 0;
	memset(vis, 0, sizeof vis);
	sqr = sqrt(n);

	//筛质数，算h
	for (int i = 2; i <= sqr; i++) {
		if (!vis[i]) {
			P[++cnt] = i;
			h[0][cnt] = h[0][cnt - 1] + 1;
			Add(h[1][cnt],h[1][cnt - 1],i);
			Add(h[2][cnt],h[2][cnt - 1],M(1LL * i * i));
		}
		for (int j = 1; j <= cnt && P[j] * i <= sqr; j++) {
			vis[i*P[j]] = 1;
			if (i%P[j] == 0)break;
		}
	}

	//计算g的边界:自然幂数和;g(1)不算,最后记得减一
	for (LL i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i); w[++m] = n / i;
		if (w[m] <= sqr)id1[w[m]] = m;
		else id2[n / w[m]] = m;

		g[0][m] = M(w[m] - 1);
		Sub(g[1][m], M(M(M(w[m] + 1)*M(w[m]))*inv2), 1);
		Sub(g[2][m], M(M(M(w[m])*M(w[m] + 1))*M(M(2 * w[m] + 1)*inv6)), 1);
	}
	//完成g的计算:自然幂数质数和;滚动数组
	for (int j = 1; j <= cnt; j++) {
		for (int i = 1; i <= m && 1LL * P[j] * P[j] <= w[i]; i++) {
			//g[n]=g[n]-P[j]^k*(g[n/P[j]]-h[j-1])

			g[0][i] = g[0][i] - (g[0][ind(w[i] / P[j])] - h[0][j - 1]);
			SFSub(g[1][i], M(P[j] * (g[1][ind(w[i] / P[j])] - h[1][j - 1] + mod)));
			SFSub(g[2][i], M(M(1LL * P[j] * P[j]) * (g[2][ind(w[i] / P[j])] - h[2][j - 1] + mod)));
		}
	}

	//输出S(n,1)+F(1),注意符号
	LL ans = M(S(n, 1) + 1 + mod);
	cout << ans << endl;
}
int main() {
	cin >> n; solve();
}
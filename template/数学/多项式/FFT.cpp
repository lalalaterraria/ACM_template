#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

const double pi = acos(-1);
struct cp {
	double x, y;
	cp operator+(cp a) { return { x + a.x,y + a.y }; }
	cp operator-(cp a) { return { x - a.x,y - a.y }; }
	cp operator*(cp a) { return { x*a.x - y * a.y,x*a.y + y * a.x }; }
};

const int maxn = 2100010;
int rev[maxn]; cp w[maxn];
void fft(cp x[], int len, int on) {

	for (int i = 0; i < len; i++) rev[i] = (i & 1)*(len >> 1) + (rev[i >> 1] >> 1);
	for (int i = 0; i < len; i++) if (i < rev[i])swap(x[i], x[rev[i]]);
	for (int i = 2; i <= len; i <<= 1) {
		int wn = len / i, d = i >> 1;
		for (int j = 0; j < len; j += i) {
			int wk = 0;
			for (int k = j; k < j + d; k++) {
				cp a = x[k], b = w[wk] * x[k + d];
				x[k] = a + b, x[k + d] = a - b;
				wk += wn;
			}
		}
	}
	if (on == -1){
		reverse(x + 1, x + len);
		for (int i = 0; i < len; i++){
			x[i].x /= len, x[i].y /= len;
		}
	}
}

cp a[maxn];int ans[maxn];
void work(cp a[], int len, int ans[]) {

	for (int i = 0; i < len / 2; i++) {
		double alpha = 2 * pi*i / len;
		double c = cos(alpha), s = sin(alpha);
		w[i] = { c,s }; w[i + len / 2] = { -c,-s };
	}

	fft(a, len, 1);
	for (int i = 0; i < len; i++) a[i] = a[i] * a[i];
	fft(a, len, -1);

	// 共轭复数优化fft需要取虚部的一半
	// 勿使用round, 请使用int(x+0.5)(负0), 对于负数为int(x-0.5)
	for (int i = 0; i < len; i++) ans[i] = int(a[i].y + 0.5) / 2;
	
}


int main() {

	ios::sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	for (int i = 0; i <= n; i++)cin >> a[i].x;
	for (int i = 0; i <= m; i++)cin >> a[i].y;

	// 记得长度是相加后的长度
	int len=1<<(32-__builtin_clz(m+n));
	work(a, len, ans);
	
	for (int i = 0; i <= m + n; i++) {
		cout << ans[i] << " \n"[i == m + n];
	}
}
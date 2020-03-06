#include<iostream>
#include<algorithm>
using namespace std;
const int mod = 998244353;
#define SFAdd(x,y)	((x+=y)<mod?x:x-=mod)
#define SFSub(x,y)	((x-=y)<0?x+=mod:x)
#define Add(a,x,y)	((a=x+y)<mod?a:a-=mod)
#define Sub(a,x,y)	((a=x-y)<0?a+=mod:a)
#define Div2(x)	(x&1?(x+=mod)>>=1:x>>=1)

void FWT_or(int a[], int n, int on) {
	for (int i = 1; i < n; i <<= 1)
		for (int j = 0; j < n; j += i << 1)
			for (int k = j; k < i + j; k++)
				on == 1 ? SFAdd(a[i + k], a[k]) : SFSub(a[i + k], a[k]);
}
void FWT_and(int a[], int n, int on) {
	for (int i = 1; i < n; i <<= 1)
		for (int j = 0; j < n; j += i << 1)
			for (int k = j; k < i + j; k++)
				on == 1 ? SFAdd(a[k], a[i + k]) : SFSub(a[k], a[i + k]);
}
void FWT_xor(int a[], int n, int on) {
	for (int i = 1; i < n; i <<= 1)
		for (int j = 0; j < n; j += i << 1)
			for (int k = j; k < i + j; k++) {
				int x = a[k], y = a[i + k];
				Add(a[k], x, y); Sub(a[i + k], x, y);
				if (on == -1)Div2(a[k]), Div2(a[i + k]);
			}
}
int a[1 << 17], b[1 << 17], c[1 << 17];
int main() {
	ios::sync_with_stdio(0); cin.tie(0); int n; cin >> n;
	for (int i = 0; i < 1 << n; i++) cin >> a[i];
	for (int i = 0; i < 1 << n; i++) cin >> b[i];

	//先转为点值表示 再乘 再还原
	FWT_or(a, 1 << n, 1), FWT_or(b, 1 << n, 1);
	for (int i = 0; i < 1 << n; i++) c[i] = 1ll * a[i] * b[i] % mod;
	FWT_or(c, 1 << n, -1); FWT_or(a, 1 << n, -1); FWT_or(b, 1 << n, -1);
	for (int i = 0; i < 1 << n; i++)cout << c[i] << " "; cout << endl;

	FWT_and(a, 1 << n, 1), FWT_and(b, 1 << n, 1);
	for (int i = 0; i < 1 << n; i++) c[i] = 1ll * a[i] * b[i] % mod;
	FWT_and(c, 1 << n, -1); FWT_and(a, 1 << n, -1); FWT_and(b, 1 << n, -1);
	for (int i = 0; i < 1 << n; i++)cout << c[i] << " "; cout << endl;

	FWT_xor(a, 1 << n, 1), FWT_xor(b, 1 << n, 1);
	for (int i = 0; i < 1 << n; i++) c[i] = 1ll * a[i] * b[i] % mod;
	FWT_xor(c, 1 << n, -1); FWT_xor(a, 1 << n, -1); FWT_xor(b, 1 << n, -1);
	for (int i = 0; i < 1 << n; i++)cout << c[i] << " "; cout << endl;
}
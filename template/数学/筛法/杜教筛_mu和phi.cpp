#include<iostream>
#include<unordered_map>
using namespace std;
#define ll long long
const int maxn = 1e7;

int P[maxn], cnt; bool vis[maxn];
//虽然用phi和mu命名，但这里表示前缀和
ll phi[maxn]; int mu[maxn];
unordered_map<int, int> Mmu;
unordered_map<int, ll> Mphi;

//初始化
void init(){
	mu[1] = phi[1] = 1;
	for (int i = 2; i < maxn; i++) {
		if (!vis[i]) P[cnt++] = i, mu[i] = -1, phi[i] = i - 1;
		for (int j = 0; j < cnt && P[j] * i < maxn; j++) {
			int now = P[j] * i;
			vis[now] = 1;
			if (i%P[j] == 0) {
				phi[now] = P[j] * phi[i];
				break;
			} 
			else {
				phi[now] = (P[j] - 1) * phi[i];
				mu[now] = -mu[i];
			}
		}
	}
	for (int i = 1; i < maxn; i++) mu[i] += mu[i - 1], phi[i] += phi[i - 1];
}

//计算phi前缀和
ll Sphi(ll x){
	if (x < maxn) return phi[x];
	if (Mphi[x]) return Mphi[x];
	//如果带mod这里改逆元
	ll ret = x * (x + 1) / 2;
	for (ll i = 2, j; i <= x; i = j + 1){
		j = x / (x / i);
		ret -= (j - i + 1)*Sphi(x / i);
	}
	//记忆化：返回值储存在无序map里
	return Mphi[x] = ret;
}

//计算mu前缀和
ll Smu(int x){
	if (x < maxn) return mu[x];
	if (Mmu[x]) return Mmu[x];
	int ret = 1;
	for (ll i = 2, j; i <= x; i = j + 1){
		j = x / (x / i);
		ret -= (j - i + 1)*Smu(x / i);
	}
	return Mmu[x] = ret;
}

int main(){
	init();
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		cout << Sphi(n) << " " << Smu(n) << endl;
	}
}
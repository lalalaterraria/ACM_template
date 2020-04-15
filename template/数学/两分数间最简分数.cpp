#include<bits/stdc++.h>
using namespace std;
#define ll long long
// 传入的不一定是最简分数
pair<ll, ll> calcu(pair<ll, ll> a, pair<ll, ll> b) {
	if (a.first == 0) a = { 1, 1ll << 60 };
	if (b.first == 0) b = { 1, 1ll << 60 };
	if (a.first < a.second && b.first > b.second) return { 1, 1 };
	if (a.first >= a.second) {
		const ll d = a.first / a.second;
		auto p = calcu({ a.first - d * a.second, a.second }, { b.first - d * b.second, b.second });
		p.first += p.second * d;
		return p;
	}
	auto p = calcu({ b.second, b.first }, { a.second, a.first });
	return { p.second, p.first };
}
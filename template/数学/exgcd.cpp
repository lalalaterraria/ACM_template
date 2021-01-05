#define ll long long
void exgcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0)x = 1, y = 0;
	else {
		exgcd(b, a%b, y, x);
		y -= a / b * x;
	}
}
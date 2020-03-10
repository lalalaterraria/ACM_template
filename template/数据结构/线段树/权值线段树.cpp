#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

#define fo(i,a,b) for(int i=a;i<=b;i++)
#define setm int m=l+r>>1

const int minn = -1e7;
const int maxn = 1e7;

const int n = 200050 * 18;
int t[n], ls[n], rs[n], tag[n], tot, rt;

void php(int p) { t[p] = t[ls[p]] + t[rs[p]]; }
void phd(int p)//区间置0的下推函数
{
	if (tag[p])
	{
		tag[p] = 0;
		ls[p] = ls[p] ? ls[p] : ++tot;
		rs[p] = rs[p] ? rs[p] : ++tot;
		t[ls[p]] = t[rs[p]] = 0;
		tag[ls[p]] = tag[rs[p]] = 1;
	}
}
//改变，增加或者减少
void upd(int &p, int l, int r, int x, int c)
{
	p = p ? p : ++tot;
	if (l == r) { t[p] += c; return; }
	phd(p); setm;
	if (x <= m) upd(ls[p], l, m, x, c);
	else upd(rs[p], m + 1, r, x, c);
	php(p);
}
//区间置零
void del(int &p, int l, int r, int x, int y)
{
	p = p ? p : ++tot;
	if (x <= l && r <= y) { tag[p] = 1; t[p] = 0; return; }
	phd(p); setm;
	if (x <= m) del(ls[p], l, m, x, y);//若与左区间有重合
	if (y > m) del(rs[p], m + 1, r, x, y);//若与右区间有重合
	php(p);
}
//查询比x小的数的数量
int rk(int &p, int l, int r, int x)
{
	if (l == r) return 1;//如果改成0就是更小的
	phd(p); setm;
	if (x <= m)return rk(ls[p], l, m, x); //比x小的有多少
	else return t[ls[p]] + rk(rs[p], m + 1, r, x);
}
//查询排名为x的数
int kth(int &p, int l, int r, int x)
{
	if (l == r) return l;
	phd(p); setm;
	if (x <= t[ls[p]]) return kth(ls[p], l, m, x);//树上二分，如果x包含在左树内，则在左树内查询
	else return kth(rs[p], m + 1, r, x - t[ls[p]]);//不然则在右树查找第x-t[ls[p]]大的树
}
//查找前继
int pre(int &p, int l, int r, int x)
{
	if (!t[p])return 0;
	if (l == r) return l;
	phd(p); setm;
	if (x <= m + 1) return pre(ls[p], l, m, x);
	int ret = pre(rs[p], m + 1, r, x);
	if (ret)return ret;
	else return pre(ls[p], l, m, x);
}
//查找后驱
int nxt(int &p, int l, int r, int x)
{
	if (!t[p])return 0;
	if (l == r) return l;
	phd(p); setm;
	if (x >= m) return nxt(rs[p], m + 1, r, x);
	int ret = nxt(ls[p], l, m, x);
	if (ret)return ret;
	else return nxt(rs[p], m + 1, r, x);
}
//动开不用初始化
int main()
{
	int n; cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int tmp, num; cin >> tmp >> num;
		switch (tmp) {
		case 1:
			upd(rt, minn, maxn, num, 1);
			break;
		case 2:
			upd(rt, minn, maxn, num, -1);
			break;
		case 3:
			printf("%d\n", rk(rt, minn, maxn, num));
			break;
		case 4:
			printf("%d\n", kth(rt, minn, maxn, num));
			break;
		case 5:
			printf("%d\n", pre(rt, minn, maxn, num));
			break;
		case 6:
			printf("%d\n", nxt(rt, minn, maxn, num));
			break;
		default:
			break;
		}
	}
	return 0;
}
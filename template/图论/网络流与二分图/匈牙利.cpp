#include<bits/stdc++.h>
using namespace std;

const int N = 1010;
struct XYL{

	vector<int> e[N];
	int n,m,vis[N],match[N];
	void init(int nn,int mm){
		n=nn,m=mm;
	}
	bool find(int u){
		for(auto &v:e[u]){
			if(vis[v]) continue;
			vis[v] = 1;
			// 如果没有对象或者对象可以空出
			if(!match[v]||find(match[v])){
				match[v] = u;
				return 1;
			}
		}
		return 0;
	}
	int solve(){
		int ret=0;
		for(int i=1;i<=n;i++){
			for(int i=1;i<=m;i++) vis[i]=0;
			if(find(i)) ret++;
		}
		return ret;
	}
} xyl;

// 不明确左部点：加双向边，直接对全部点跑匈牙利，答案再除以2
int main(){
	int n,m,e;cin>>n>>m>>e;
	for(int i=1;i<=e;i++){
		// 右部点的序号加上左部点数
		int a,b;cin>>a>>b;
		xyl.e[a].push_back(b);
	}
	xyl.init(n,m);
	cout<<xyl.solve()<<endl;
}
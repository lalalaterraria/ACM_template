#include<bits/stdc++.h>
using namespace std;

const int maxn=1000010;
struct node {
	int a,b; node(){}
	node(int a,int b):a(a),b(b){}
	friend ostream& operator <<(ostream& out,node x){ return out<<"("<<x.a<<","<<x.b<<")"; }  
} base(131,137),Hmod(1e9+7,1e9+9);
bool operator==(node x, node y) { return x.a==y.a&&x.b==y.b; }
node operator*(node x, node y) { return node(1ll*x.a*y.a%Hmod.a,1ll*x.b*y.b%Hmod.b); }
node operator+(node x, char c) { return node((x.a+c)%Hmod.a,(x.b+c)%Hmod.b); }
node operator+(node x, node y) { return node((x.a+y.a)%Hmod.a,(x.b+y.b)%Hmod.b); }
node operator-(node x, node y) { return node((x.a+Hmod.a-y.a)%Hmod.a,(x.b+Hmod.b-y.b)%Hmod.b); }
struct mybase{
	node bas[maxn];
	mybase(){ 
		bas[0]={1,1};
		for(int i=1;i<maxn;i++) bas[i]=bas[i-1]*base;
	}
} B;
struct myhash{
	vector<node> has;
    // 注意哈希数组从1开始存，高位在左
    myhash(string &s){
		has.reserve(s.size()+1);
		has.push_back({0,0});
        for(int i=0;i<int(s.size());i++) has.push_back(has[i]*base+s[i]);
    }
	node str(int l,int r){
		return has[r]-has[l-1]*B.bas[r-l+1];
	}
};

// s在t中出现次数
int match(string &s,string &t){
	int n=s.size(),m=t.size(),ret=0;
	myhash h1(s),h2(t);
	for(int i=1;i<=m-n+1;i++){
		ret+=h1.str(1,n)==h2.str(i,n+i-1);
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);
    int t;cin>>t;
	while(t--){
		string s,t;cin>>s>>t;
		cout<<match(s,t)<<endl;
	}
}
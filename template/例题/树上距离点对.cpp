#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=200010;

vector<int> e_pre[maxn];
vector<pair<int,int> > e[maxn*2];
// 三度化后边也变成两倍
int e_vis[maxn*2];
int n,k;

// 记得初始化cnt=n, e_cnt=0
int u_cnt,e_cnt;
void dfs_pre(int u,int fa){
    // 负数为虚边, 大于cnt的点为虚点
    // abs(e_cnt)来标记访问过的边
    auto add=[&](int a,int b,int w){
        ++e_cnt;
        e[a].push_back({b,w*e_cnt});
        e[b].push_back({a,w*e_cnt});
    };
    int sz=int(e_pre[u].size()),pre=0;
    for(int i=0;i<sz;i++){
        int v=e_pre[u][i];
        if(v==fa) continue;
        if(pre==0) add(v,u,1), pre=u;
        else{
            add(++u_cnt,pre,-1);
            add(v,u_cnt,1);
            pre=u_cnt;
        }
        dfs_pre(v,u);
    }
}

const double pi = acos(-1);
struct cp {
	double x, y;
	cp operator+(cp a) { return { x + a.x,y + a.y }; }
	cp operator-(cp a) { return { x - a.x,y - a.y }; }
	cp operator*(cp a) { return { x*a.x - y * a.y,x*a.y + y * a.x }; }
};

int rev[maxn*4]; cp w[maxn*4];
void fft(cp x[], int len, int on) {

	for (int i = 0; i < len / 2; i++) {
		double alpha = 2 * pi*i / len;
		double c = cos(alpha), s = sin(alpha);
		w[i] = { c,s }; w[i + len / 2] = { -c,-s };
	}

	for (int i = 0; i < len; i++)rev[i] = (i & 1)*(len >> 1) + (rev[i >> 1] >> 1);
	for (int i = 0; i < len; i++)if (i < rev[i])swap(x[i], x[rev[i]]);
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
	if (on == -1) {
		reverse(x + 1, x + len);
		for (int i = 0; i < len; i++)x[i].x /= len;
	}
}

void work(cp x[], cp y[], int len) {
    fft(x, len, 1); fft(y, len, 1);
	for (int i = 0; i < len; i++)x[i] = x[i] * y[i];
	fft(x, len, -1);
}

// 记得初始化rt_find=0, -1表示找到虚边, 1表示找到实边
int sz[maxn*2],rt_tag;
pair<int,int> rt;
// rt连边是定向的，{子节点, 父节点}
void dfs_rt(int u,int fa,int e_tag,int tot){
    // cout<<"  dfs: "<<u<<" "<<fa<<" "<<tot<<endl;
    
    // 这里的v, tag在下面需要用到，所以顺序很重要!!!
    sz[u]=1;int maxn=0,v,tag;
    for(auto &it:e[u]){
        
        if(it.first==fa||e_vis[abs(it.second)]) continue;
        v=it.first,tag=it.second;
        dfs_rt(v,u,tag,tot);
        sz[u]+=sz[v];
        maxn=max(maxn,sz[v]);
    }
    maxn=max(maxn,tot-sz[u]);
    // 找到分治边并且打上删除标记
    if(!rt_tag&&maxn<=tot/2){
        
        // 父边可能是0, 此时需要特判, 且任需保持定向
        if(fa==0){
            rt={v,u};
            e_vis[abs(tag)]=1;
            rt_tag=tag<0?-1:1;
        }
        else{
            rt={u,fa};
            e_vis[abs(e_tag)]=1;
            rt_tag=e_tag<0?-1:1;
        }
    }
}

cp a[maxn*4],b[maxn*4];
void dfs_cal(int u,int fa,int dep,cp a[]){
    if(u<=n) a[dep].x++;
    for(auto &it:e[u]){
        int v=it.first;
        // 统计的时候需考虑边点虚实
        if(v==fa||e_vis[abs(it.second)]) continue;
        dfs_cal(v,u,dep+(it.second<0?0:1),a);
    }
}

// 边分治FFT求距离点对的计算结果
ll dis_cnt[maxn*4];
void dfs_div(int u,int fa,int tot=u_cnt){

    if(tot==1) return;

    rt_tag=0; dfs_rt(u,fa,0,tot);
    // dfs的结果保存下来，不然会被dfs子节点的时候覆盖
    pair<int,int> now_rt=rt,now_sz={sz[rt.first],tot-sz[rt.first]};

    int len=1<<(32-__builtin_clz(tot));
    for(int i=0;i<len;i++) a[i].x=a[i].y=b[i].x=b[i].y=0;
    dfs_cal(now_rt.first,0,0,a);dfs_cal(now_rt.second,0,0,b);

    // cout<<"sep: "<<rt.first<<","<<rt.second<<" "<<tot<<endl;
    // for(int i=0;i<len;i++) cout<<a[i].x<<" \n"[i==len-1];
    // for(int i=0;i<len;i++) cout<<b[i].x<<" \n"[i==len-1];

    work(a,b,len);
    for(int i=0;i<len;i++){
        dis_cnt[i+(rt_tag==-1?0:1)]+=round(a[i].x);
    }

    dfs_div(now_rt.first,0,now_sz.first);
    dfs_div(now_rt.second,0,now_sz.second);

}

const int mod=1e9+7;
ll mypow(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1)ret=ret*a%mod;
        a=a*a%mod;b>>=1;
    }
    return ret;
}

int f[maxn];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int t;cin>>t;
    for(int i=1;i<=t;i++){
        cin>>n>>k;
        
        for(int i=1;i<=n;i++) e_pre[i].clear();
        // 两倍的清空
        for(int i=1;i<=2*n;i++) e[i].clear(),e_vis[i]=0;
        for(int i=1;i<n;i++){
            int a,b;cin>>a>>b;
            e_pre[a].push_back(b);
            e_pre[b].push_back(a);
        }

        f[1]=0,f[2]=1ll*k*(k-1)%mod;
        for(int i=3;i<=n;i++){
            f[i]=(1ll*f[i-1]*(k-2)+1ll*f[i-2]*(k-1))%mod;
        }
        for(int i=2;i<=n;i++){
            f[i]=1ll*f[i]*mypow(k-1,n-i)%mod;
        }
        u_cnt=n; e_cnt=0;
        dfs_pre(1,0);

        // 输出三度化
        // for(int i=0;i<=u_cnt;i++){
        //     cout<<"now: "<<i<<endl;
        //     for(auto &it:e[i]){
        //         cout<<it.first<<" "<<it.second<<endl;
        //     }
        //     cout<<endl;
        // }

        for(int i=0;i<n;i++) dis_cnt[i]=0;
        dfs_div(1,0);

        // for(int i=1;i<=n;i++) cout<<f[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<n;i++) cout<<dis_cnt[i]<<" ";
        // cout<<endl;

        ll ans=0,tot=0;
        for(int i=2;i<n;i++){
            tot+=dis_cnt[i];
            dis_cnt[i]%=mod;
            ans+=dis_cnt[i]*f[i+1]%mod;
        }
        ans%=mod;
        ans=ans*mypow(tot%mod,mod-2)%mod;
 
        cout<<"Case #"<<i<<": "<<ans<<endl;
    } 
}
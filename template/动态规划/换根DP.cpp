#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=1e9+7;
vector<int> e[100010];
int sz[100010];
int n,k;

ll tot[20][6];      // 全部方向临时容斥数组
ll tmp[100010][6];  // 临时DP数组
ll dp[100010][20];  // 叶方向
ll to[100010][20]; // 根方向
ll ans[100010]; 
void pre_dfs(int u,int fa){
    for(auto &v:e[u]){
        if(v==fa) continue;
        pre_dfs(v,u);
    }

    // 注意边界
    dp[u][0]=1;
    for(int o=1;o<20;o++){
        for(int i=0;i<=sz[u];i++) tmp[i][0]=1;
        for(int i=1;i<=sz[u];i++){
            int v=e[u][i-1];
            for(int j=1;j<=k;j++){
                tmp[i][j]=(tmp[i-1][j]+(v==fa?0:tmp[i-1][j-1]*dp[v][o-1]))%mod;
            }
        }
        dp[u][o]=tmp[sz[u]][k];
    }
}

void dfs(int u,int fa){

    // 算出全部 注意边界
    ans[u]=1;
    for(int o=1;o<20;o++){
        for(int i=0;i<=sz[u];i++) tmp[i][0]=1;
        for(int i=1;i<=sz[u];i++){
            int v=e[u][i-1];
            for(int j=1;j<=k;j++){
                tmp[i][j]=(tmp[i-1][j]+(v==fa?to[u][o-1]:dp[v][o-1])*tmp[i-1][j-1])%mod;
                if(i==sz[u]) tot[o][j]=tmp[i][j];
            }
        }
        ans[u]=(ans[u]+tot[o][k])%mod;
    }

    // 容斥
    for(auto &v:e[u]){
        if(v==fa) continue;
        // 注意边界
        to[v][0]=1;
        for(int o=1;o<20;o++){
            ll now=1;
            for(int j=k,flg=1;j>=0;j--,flg=-flg){
                // 容斥注意边界
                // 写过一个傻逼BUg死活调不出来 FUCK 第一遍写的时候没写式子的锅
                // to[v][o]=(to[v][o]+mod+flg*(j==0?1:tot[o][j])*now%mod;

                to[v][o]=(to[v][o]+mod+flg*(j==0?1:tot[o][j])*now%mod)%mod;
                now=now*dp[v][o-1]%mod;
            }
        }
    }

    for(auto &v:e[u]){
        if(v==fa) continue;
        dfs(v,u);
    }

}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int a,b;cin>>a>>b;
        e[a].push_back(b);
        e[b].push_back(a);
        sz[a]++,sz[b]++;
    }

    pre_dfs(1,0);
    dfs(1,0);

    ll ANS=0;
    for(int i=1;i<=n;i++) ANS+=ans[i];
    cout<<ANS%mod<<endl;
}